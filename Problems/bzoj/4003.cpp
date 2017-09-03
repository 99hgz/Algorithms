#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
vector<ll> vec[300010];
struct Node
{
    ll val, fa, left, right, times, add, suc;
} tree[300010];
ll dist[300010];
ll n, m, sj[300010], success[300010], firstcc[300010], attack[300010], killed[300010], fy[300010], a[300010], v[300010], cases, x, y, root[300010], ans;

ll push_down(ll x)
{
    if (tree[x].right)
    {
        ll rt = tree[x].right;
        tree[rt].val *= tree[x].times;
        tree[rt].val += tree[x].add;
        tree[rt].times *= tree[x].times;
        tree[rt].add += tree[x].add;
        tree[rt].suc += tree[x].suc;
        success[rt] += tree[x].suc;
    }
    if (tree[x].left)
    {
        ll rt = tree[x].left;
        tree[rt].val *= tree[x].times;
        tree[rt].val += tree[x].add;
        tree[rt].times *= tree[x].times;
        tree[rt].add += tree[x].add;
        tree[rt].suc += tree[x].suc;
        success[rt] += tree[x].suc;
    }
    tree[x].times = 1;
    tree[x].add = 0;
    tree[x].suc = 0;
}

ll merge(ll A, ll B)
{
    if (!A || !B)
        return A + B;
    if ((tree[A].val > tree[B].val) || (tree[A].val == tree[B].val && A > B))
        swap(A, B);
    ll tmp;
    push_down(A);
    tree[A].right = tmp = merge(tree[A].right, B);
    tree[tmp].fa = A;
    if (dist[tree[A].right] > dist[tree[A].left])
        swap(tree[A].right, tree[A].left);
    dist[A] = dist[tree[A].right] + 1;
    return A;
}

ll get_father(ll A)
{
    return tree[A].fa ? get_father(tree[A].fa) : A;
}

ll erase(ll A)
{

    tree[tree[A].left].fa = 0;
    tree[tree[A].right].fa = 0;
    tree[A].val = 0;
    push_down(A);
    return merge(tree[A].left, tree[A].right);
}

void addedge(ll u, ll v)
{
    vec[u].push_back(v);
}

void dfs(ll x)
{
    //printf("in%lld\n", x);
    for (ll i = 0; i < vec[x].size(); i++)
    {
        dfs(vec[x][i]);
        root[x] = merge(root[x], root[vec[x][i]]);
    }
    /*printf("merged:%lld\n", x);
    for (ll i = 1; i <= m; i++)
    {
        printf("%lld %lld %lld %lld %lld\n", i, tree[i].val, tree[i].times, tree[i].add, tree[i].suc);
    }*/
    while (root[x] && tree[root[x]].val < fy[x])
    {
        root[x] = erase(root[x]);
        killed[x]++;
    }
    if (a[x])
    {
        tree[root[x]].times *= v[x];
        tree[root[x]].val *= v[x];
    }
    else
    {
        tree[root[x]].add += v[x];
        tree[root[x]].val += v[x];
    }
    tree[root[x]].suc++;
    success[root[x]]++;
}

int main()
{
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld", &fy[i]);
    }
    for (ll i = 2; i <= n; i++)
    {
        scanf("%lld%lld%lld", &sj[i], &a[i], &v[i]);
        addedge(sj[i], i);
    }
    for (ll i = 1; i <= m; i++)
    {
        scanf("%lld%lld", &attack[i], &firstcc[i]);
        tree[i].val = attack[i];
        tree[i].times = 1;
        tree[i].add = 0;
        root[firstcc[i]] = merge(root[firstcc[i]], i);
    }
    dfs(1);
    for (ll i = 1; i <= n; i++)
    {
        printf("%lld\n", killed[i]);
    }
    for (ll i = 1; i <= m; i++)
    {
        printf("%lld\n", success[i]);
    }
    //printf("%lld\n", ans);
    system("pause");
    return 0;
}