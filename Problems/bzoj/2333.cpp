#include <cstdio>
#include <cstring>
#include <queue>
#include <stack>
#include <vector>
#include <set>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
vector<ll> vec[300010];
struct Node
{
    ll val, fa, left, right, add;
} tree[300010];
ll dist[300010];
ll n, m, a[300010], x, y, ans;
ll cnt, totaladd, q;
char A[10];
#define GT greater<ll>
multiset<ll> MS;

void nownode(ll x, ll y)
{
    tree[x].val = y;
    tree[x].fa = tree[x].left = tree[x].right = tree[x].add = 0;
}

ll push_down(ll x)
{
    if (tree[x].right)
    {
        ll rt = tree[x].right;
        //tree[rt].val *= tree[x].times;
        tree[rt].val += tree[x].add;
        //tree[rt].times *= tree[x].times;
        //tree[rt].add *= tree[x].times;
        tree[rt].add += tree[x].add;
        //tree[rt].suc += tree[x].suc;
        //success[rt] += tree[x].suc;
    }
    if (tree[x].left)
    {
        ll rt = tree[x].left;
        //tree[rt].val *= tree[x].times;
        tree[rt].val += tree[x].add;
        //tree[rt].times *= tree[x].times;
        //tree[rt].add *= tree[x].times;
        tree[rt].add += tree[x].add;
        //tree[rt].suc += tree[x].suc;
        //success[rt] += tree[x].suc;
    }
    //tree[x].times = 1;
    tree[x].add = 0;
    //tree[x].suc = 0;
}

ll merge(ll A, ll B)
{
    if (!A || !B)
        return A + B;
    if ((tree[A].val < tree[B].val) || (tree[A].val == tree[B].val && A > B))
        swap(A, B);
    ll tmp;
    push_down(A);
    push_down(B);
    tree[A].right = tmp = merge(tree[A].right, B);
    tree[tmp].fa = A;
    if (dist[tree[A].right] > dist[tree[A].left])
        swap(tree[A].right, tree[A].left);
    dist[A] = dist[tree[A].right] + 1;
    return A;
}

ll get_father(ll A)
{
    //printf("%lld\n", A);
    return tree[A].fa ? get_father(tree[A].fa) : A;
}

ll erase(ll A)
{
    push_down(A);
    ll fa = tree[A].fa, tmp = merge(tree[A].left, tree[A].right);
    if (fa && tree[fa].left == A)
        tree[fa].left = tmp;
    if (fa && tree[fa].right == A)
        tree[fa].right = tmp;
    tree[tmp].fa = fa;
    while (fa)
    {
        if (dist[tree[fa].right] > dist[tree[fa].left])
            swap(tree[fa].right, tree[fa].left);
        if ((tree[fa].right && dist[fa] == dist[tree[fa].right] + 1) || (!tree[fa].right && !dist[fa]))
            break;
        if (!tree[fa].right)
            dist[fa] = 0;
        else
            dist[fa] = dist[tree[fa].right] + 1;
        fa = tree[fa].fa;
    }
    return get_father(tmp);
}

void addedge(ll u, ll v)
{
    vec[u].push_back(v);
}
void push_down_all(ll x)
{
    if (x == 0)
        return;
    push_down(x);
    push_down_all(tree[x].left);
    push_down_all(tree[x].right);
}
void push_down_deep(ll x)
{
    ll fa = x;
    stack<ll> Q;
    while (fa)
    {
        Q.push(fa);
        fa = tree[fa].fa;
    }
    while (!Q.empty())
    {
        ll tmp = Q.top();
        push_down(tmp);
        Q.pop();
    }
}

void MS_erase(ll x)
{
    /*printf("delete:%lld\n", x);
    multiset<ll>::iterator ii, iend;
    iend = MS.end();
    for (ii = MS.begin(); ii != iend; ++ii)
        printf("%lld ", *ii);
    printf("\n");*/
    MS.erase(MS.find(x));
    /*iend = MS.end();
    for (ii = MS.begin(); ii != iend; ++ii)
        printf("%lld ", *ii);
    printf("\n");*/
}

void MS_insert(ll x)
{
    /*printf("insert:%lld\n", x);
    multiset<ll>::iterator ii, iend;
    iend = MS.end();
    for (ii = MS.begin(); ii != iend; ++ii)
        printf("%lld ", *ii);
    printf("\n");*/
    MS.insert(x);
    /*iend = MS.end();
    for (ii = MS.begin(); ii != iend; ++ii)
        printf("%lld ", *ii);
    printf("\n");*/
}

int main()
{
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld", &tree[i].val);
        MS_insert(tree[i].val);
    }
    scanf("%lld", &q);
    for (ll i = 1; i <= q; i++)
    {
        scanf("%s", A);
        if (A[0] == 'U')
        {
            scanf("%lld%lld", &x, &y);
            ll fx = get_father(x);
            ll fy = get_father(y);
            MS_erase(min(tree[fx].val, tree[fy].val));
            if (fx != fy)
            {
                merge(fx, fy);
            }
        }
        else if (A[0] == 'A' && A[1] == '1')
        {
            scanf("%lld%lld", &x, &y);
            ll fx = get_father(x);
            ll tmp = tree[fx].val;
            MS_erase(tree[fx].val);
            erase(x);
            nownode(x, tmp + y);
            fx = get_father(fx);
            if (fx != x)
                merge(fx, x);
            fx = get_father(x);
            MS_insert(tree[fx].val);
        }
        else if (A[0] == 'A' && A[1] == '2')
        {
            scanf("%lld%lld", &x, &y);
            ll fx = get_father(x);
            //printf("father:%lld\n", fx);
            MS_erase(tree[fx].val);
            tree[fx].add += y;
            tree[fx].val += y;
            MS_insert(tree[fx].val);
        }
        else if (A[0] == 'A' && A[1] == '3')
        {
            scanf("%lld", &x);
            totaladd += x;
        }
        else if (A[0] == 'F' && A[1] == '1')
        {
            scanf("%lld", &x);
            //printf("%lld\n", tree[x].fa);
            push_down_deep(x);

            printf("%lld\n", tree[x].val + totaladd);
        }
        else if (A[0] == 'F' && A[1] == '2')
        {
            scanf("%lld", &x);
            ll fx = get_father(x);
            printf("%lld\n", tree[fx].val + totaladd);
        }
        else if (A[0] == 'F' && A[1] == '3')
        {
            push_down_deep(x);
            printf("%lld\n", *--MS.find((ll)0x7f7f7f7f) + totaladd);
        }
        /*multiset<ll>::iterator ii, iend;
        iend = MS.end();
        for (ii = MS.begin(); ii != iend; ++ii)
            printf("%lld ", *ii);
        printf("\n");*/
    }

    system("pause");
    return 0;
}