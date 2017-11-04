#include <cmath>
#include <vector>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#define maxn 500010
typedef long long ll;
using namespace std;
struct edge
{
    ll point, dis;
};
vector<edge> hmap[maxn];
ll parent[maxn];
bool vis[maxn];
ll deep[maxn];
ll p[maxn][40];
ll cnt, tot, stacktop, stack[maxn], dfn[maxn], Tree[maxn * 2], Head[maxn * 2], Next[maxn * 2], keypoint[maxn], stamp, k;
ll Head2[maxn * 2], Next2[maxn * 2], Tree2[maxn * 2], Tree3[maxn * 2];
ll f[maxn], minedge[maxn];
void init(ll n)
{
    ll st;
    st = floor(log(n) / log(2));
    for (ll i = 1; i <= n; i++)
        for (ll j = 0; j <= st; j++)
            p[i][j] = -1;
    for (ll i = 1; i <= n; i++)
        p[i][0] = parent[i];
    for (ll j = 1; j <= st; j++)
        for (ll i = 1; i <= n; i++)
            if (p[i][j - 1] != -1)
                p[i][j] = p[p[i][j - 1]][j - 1];
}
ll lca(ll a, ll b)
{
    //printf("%d %d\n", a, b);
    if (deep[a] < deep[b])
        swap(a, b);
    ll st = floor(log(deep[a] - 1) / log(2));
    for (ll i = st; i >= 0; i--)
        if (deep[a] - (1 << i) >= deep[b])
            a = p[a][i];
    if (a == b)
        return a;
    for (ll i = st; i >= 0; i--)
        if ((p[a][i] != -1) && (p[a][i] != p[b][i]))
        {
            a = p[a][i];
            b = p[b][i];
        }
    return parent[a];
}

void dfs(ll p, ll deep1)
{
    dfn[p] = ++stamp;
    deep[p] = deep1;
    //printf("dfs:%d %d\n", p, deep1);
    for (ll it = Head2[p]; it; it = Next2[it])
    {
        ll v = Tree2[it];
        if (!vis[v])
        {
            vis[v] = true;
            parent[v] = p;
            minedge[v] = min((ll)Tree3[it], minedge[p]);
            dfs(v, deep1 + 1);
        }
    }
}

void addedge2(ll u, ll v)
{
    //printf("%d %d\n", u, v);
    if (u == v)
        return;
    cnt++;
    Tree[cnt] = v;
    Next[cnt] = Head[u];
    Head[u] = cnt;
}

bool cmp(ll a, ll b)
{
    return dfn[a] < dfn[b];
}

void build_vtree()
{
    stacktop = 0;
    stack[++stacktop] = 1;
    tot = 0;
    cnt = 0;
    sort(keypoint + 1, keypoint + 1 + k, cmp);
    keypoint[++tot] = keypoint[1];
    for (ll i = 2; i <= k; i++)
        if (lca(keypoint[tot], keypoint[i]) != keypoint[tot])
            keypoint[++tot] = keypoint[i];

    for (ll i = 1; i <= tot; i++)
    {
        ll now = keypoint[i];
        ll lcanow = lca(now, stack[stacktop]);
        //printf("%d\n", lcanow);
        while (1)
        {
            if (deep[lcanow] >= deep[stack[stacktop - 1]])
            {
                addedge2(lcanow, stack[stacktop--]);
                if (stack[stacktop] != lcanow)
                    stack[++stacktop] = lcanow;
                break;
            }
            addedge2(stack[stacktop - 1], stack[stacktop]);
            stacktop--;
        }
        if (stack[stacktop] != now)
            stack[++stacktop] = now;
    }
    while (--stacktop)
    {
        addedge2(stack[stacktop], stack[stacktop + 1]);
    }
}

void dp(ll x)
{
    f[x] = minedge[x];
    ll xg = 0;
    for (ll i = Head[x]; i; i = Next[i])
    {
        dp(Tree[i]);
        xg += f[Tree[i]];
    }
    Head[x] = 0;
    if (xg == 0)
        f[x] = minedge[x];
    else if (xg <= f[x])
        f[x] = xg;
    //printf("%lld %lld\n", x, f[x]);
}

int main()
{
    ll n, m, a, b;
    edge tmp;
    ll gg = 0;
    scanf("%lld", &n);
    for (ll i = 1; i < n; i++)
    {
        scanf("%lld%lld%lld", &a, &b, &k);
        /*tmp.point = b;
        tmp.dis = k;
        hmap[a].push_back(tmp);
        tmp.point = a;
        hmap[b].push_back(tmp);*/
        gg++;
        Tree2[gg] = b;
        Tree3[gg] = k;
        Next2[gg] = Head2[a];
        Head2[a] = gg;
        gg++;
        Tree2[gg] = a;
        Tree3[gg] = k;
        Next2[gg] = Head2[b];
        Head2[b] = gg;
    }
    vis[1] = true;
    //memset(minedge, 0x7f7f7f7f, sizeof minedge);
    minedge[1] = 1e60;
    dfs(1, 1);
    init(n);
    scanf("%lld", &m);
    for (ll i = 1; i <= m; i++)
    {
        scanf("%lld", &k);
        for (ll j = 1; j <= k; j++)
            scanf("%lld", &keypoint[j]);
        build_vtree();
        //memset(f, 0x7f7f7f7f, sizeof f);
        dp(1);
        printf("%lld\n", f[1]);
    }
    system("pause");
}