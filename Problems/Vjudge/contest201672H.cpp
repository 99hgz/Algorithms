#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;

ll Q[10010], dep[10010];

ll tot, Head[10010], cur[10010], Next[201000];
ll Val[201000], To[201000];
ll n, m, S, T, u, v;
ll ans1;
bool bfs()
{
    memset(dep, -1, sizeof dep);
    ll t = 0, w = 1;
    Q[w] = S;
    dep[S] = 0;
    while (t != w)
    {
        t++;
        ll u = Q[t];
        //printf("bfs:%d\n", u);
        for (ll it = Head[u]; it; it = Next[it])
        {
            ll v = To[it];
            if (Val[it] > 0 && dep[v] == -1)
            {
                dep[v] = dep[u] + 1;
                w++;
                Q[w] = v;
            }
        }
    }
    return dep[T] != -1;
}

ll dfs(ll x, ll flow)
{
    //printf("%lld\n", flow);
    if (x == T)
        return flow;
    ll used = 0;
    for (ll it = cur[x]; it; it = Next[it])
    {
        ll v = To[it];
        if (dep[v] == dep[x] + 1)
        {
            ll tmp = dfs(v, min(Val[it], flow - used));
            used += tmp;
            Val[it] -= tmp;
            Val[it ^ 1] += tmp;
            cur[x] = it;
            if (used == flow)
                return flow;
        }
    }
    if (used == 0)
        dep[x] = -1;
    return used;
}

ll dinic()
{
    ll ans = 0;
    while (bfs())
    {
        for (ll i = 1; i <= n + 2; i++)
            cur[i] = Head[i];
        ans += dfs(S, 1LL << 60);
        //printf("%lld\n", ans);
    }
    return ans;
}

void addedge(ll u, ll v, ll flow)
{
    //printf("%d->%d\n", u, v);
    tot++;
    Next[tot] = Head[u];
    Head[u] = tot;
    Val[tot] = flow;
    To[tot] = v;
    tot++;
    Next[tot] = Head[v];
    Head[v] = tot;
    Val[tot] = 0;
    To[tot] = u;
}

bool vis[10010];

void ana()
{
    queue<ll> Q;
    Q.push(S);
    vis[S] = true;
    while (!Q.empty())
    {
        ll u = Q.front();
        Q.pop();
        //printf("%d\n", u);
        for (ll it = Head[u]; it; it = Next[it])
        {
            ll v = To[it];
            if (Val[it] > 0 && (!vis[v]))
            {

                Q.push(v);
                vis[v] = true;
                ans1++;
            }
        }
    }
}

int main()
{
    tot = 1;
    scanf("%lld%lld", &n, &m);
    S = n + 1;
    T = n + 2;
    ll sum = 0;
    ll cost;
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld", &cost);
        if (cost >= 0)
        {
            sum += cost;
            addedge(S, i, cost);
        }
        else
        {
            addedge(i, T, -cost);
        }
    }
    for (ll i = 1; i <= m; i++)
    {
        scanf("%lld%lld", &u, &v);
        addedge(u, v, 0x3f3f3f3f3f3f3f3f);
    }

    ll tmp = dinic();
    ana();
    printf("%lld %lld", ans1, sum - tmp);

    return 0;
}