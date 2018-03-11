#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;
typedef long long ll;

struct GraphNode
{
    ll v, w;
};

vector<GraphNode> vec2[100010];
bool vis[100010], used[300010];

ll deep[100010], father[100010][20], n, m, k, u, v, w, tot, fa[100010];
typedef pair<ll, ll> pr;
pr st[100010][20];
pr operator+(pr a, pr b)
{
    pr tmp;
    ll k = tmp.first = max(a.first, b.first);
    tmp.second = -1;
    if (a.first != k)
        tmp.second = max(tmp.second, a.first);
    if (a.second != k)
        tmp.second = max(tmp.second, a.second);
    if (b.first != k)
        tmp.second = max(tmp.second, b.first);
    if (b.second != k)
        tmp.second = max(tmp.second, b.second);
    return tmp;
}

struct EDGE
{
    ll u, v, w;
} edge[300010];
bool cmp(EDGE a, EDGE b)
{
    return a.w < b.w;
}

void addedgeTree(ll u, ll v, ll w)
{
    vec2[u].push_back((GraphNode){v, w});
    swap(u, v);
    vec2[u].push_back((GraphNode){v, w});
}

ll gf(ll x)
{
    return fa[x] == 0 ? x : fa[x] = gf(fa[x]);
}

ll kruskal()
{
    ll num = 0;
    sort(edge + 1, edge + 1 + m, cmp);
    for (ll i = 1; i <= m; i++)
    {
        ll fx = gf(edge[i].u), fy = gf(edge[i].v);
        if (fx != fy)
        {
            used[i] = true;
            fa[fx] = fy;
            addedgeTree(edge[i].u, edge[i].v, edge[i].w);
            num++;
            tot += edge[i].w;
        }
        if (num == n - 1)
            return i;
    }
    return 1;
}

void dfs(ll x, ll fa, ll w, ll dep)
{
    deep[x] = dep;
    father[x][0] = fa;
    st[x][0] = make_pair(w, -1);
    for (ll i = 0; i < vec2[x].size(); i++)
    {
        ll v = vec2[x][i].v;
        if (fa != v)
            dfs(v, x, vec2[x][i].w, dep + 1);
    }
}

void init()
{
    for (ll i = 1; i <= 18; i++)
        for (ll j = 1; j <= n; j++)
            father[j][i] = -1;
    for (ll i = 1; i <= 18; i++)
        for (ll j = 1; j <= n; j++)
            if (father[j][i - 1] != -1)
            {
                father[j][i] = father[father[j][i - 1]][i - 1];
                st[j][i] = st[j][i - 1] + st[father[j][i - 1]][i - 1];
            }
}

pr lca(ll a, ll b)
{
    pr res = make_pair(-1, -1);
    if (deep[a] < deep[b])
        swap(a, b);
    ll st2 = floor(log(deep[a] - 1) / log(2));
    for (ll i = st2; i >= 0; i--)
        if (deep[a] - (1 << i) >= deep[b])
        {
            res = res + st[a][i];
            a = father[a][i];
        }
    if (a == b)
        return res;
    for (ll i = st2; i >= 0; i--)
        if ((father[a][i] != -1) && (father[a][i] != father[b][i]))
        {
            res = res + st[a][i];
            res = res + st[b][i];
            a = father[a][i];
            b = father[b][i];
            //printf("jump to %lld %lld\n", a, b);
        }
    return st[b][0] + res + st[a][0];
}

int main()
{
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= m; i++)
    {
        scanf("%lld%lld%lld", &u, &v, &w);
        edge[i] = (EDGE){u, v, w};
    }
    kruskal();
    dfs(1, 0, -1, 1);
    init();
    ll ans = 0x3f3f3f3f3f3f3f3f;
    for (ll i = 1; i <= m; i++)
    {
        if (used[i])
            continue;
        pr mx = lca(edge[i].u, edge[i].v);
        ll k = mx.first;
        if (edge[i].w == k)
            k = mx.second;
        if (k == -1)
            continue;
        ans = min(ans, edge[i].w - k);
    }
    printf("%lld\n", ans + tot);
    system("pause");
    return 0;
}