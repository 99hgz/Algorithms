#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
vector<ll> vec[100010];
struct Node
{
    ll val, fa, left, right;
} tree[100010];
ll dist[100010];
ll n, m, sj[100010], c[100010], l[100010], cases, x, y, sum[100010], num[100010], _root, root[100010], ans;

ll merge(ll A, ll B)
{
    if (!A || !B)
        return A + B;
    if ((tree[A].val < tree[B].val) || (tree[A].val == tree[B].val && A > B))
        swap(A, B);
    ll tmp;
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

ll erase(ll B)
{

    ll A = root[B];
    //printf("erase%lld\n", tree[A].val);
    sum[B] -= tree[A].val;
    num[B]--;
    tree[tree[A].left].fa = 0;
    tree[tree[A].right].fa = 0;
    tree[A].val = 0;
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
        sum[x] += sum[vec[x][i]];
        num[x] += num[vec[x][i]];
        while (sum[x] > m)
            root[x] = erase(x);
    }
    sum[x] += c[x];
    num[x]++;
    tree[x] = (Node){c[x], x, 0, 0};
    root[x] = merge(root[x], x);
    while (sum[x] > m)
        root[x] = erase(x);
    ans = max(ans, num[x] * l[x]);
    //printf("out%lld\n", x);
}

int main()
{
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld%lld%lld", &sj[i], &c[i], &l[i]);
        if (sj[i] == 0)
            _root = i;
        else
            addedge(sj[i], i);
    }
    dfs(_root);
    printf("%lld\n", ans);
    system("pause");
    return 0;
}