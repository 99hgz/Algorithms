#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;
typedef long long ll;

int Q[20010], dep[20010];

int tot, Head[20010], cur[20010], Next[800010];
ll Val[800010], To[800010];
int n, m, S, T, u, v, w;

bool bfs()
{
    memset(dep, -1, sizeof dep);
    int t = 0, w = 1;
    Q[w] = S;
    dep[S] = 0;
    while (t != w)
    {
        t++;
        int u = Q[t];
        //printf("bfs:%d\n", u);
        for (int it = Head[u]; it; it = Next[it])
        {
            int v = To[it];
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

ll dfs(int x, ll flow)
{
    //printf("%lld\n", flow);
    if (x == T)
        return flow;
    ll used = 0;
    for (int it = cur[x]; it; it = Next[it])
    {
        int v = To[it];
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
        for (int i = 1; i <= n; i++)
            cur[i] = Head[i];
        ans += dfs(S, 1LL << 60);
        //printf("%lld\n", ans);
    }
    return ans;
}

void addedge(int u, int v, ll flow)
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
struct EDGE
{
    int u, v, w;
} edge[200010];

int main()
{
    tot = 1;
    scanf("%d%d", &n, &m);
    /*S = n + 1;
    T = n + 2;*/
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].w);
    scanf("%d%d%d", &S, &T, &w);
    for (int i = 1; i <= m; i++)
        if (edge[i].w < w)
            addedge(edge[i].u, edge[i].v, 1), addedge(edge[i].v, edge[i].u, 1);
    ll ans = dinic();
    memset(Head, 0, sizeof Head);
    tot = 1;
    for (int i = 1; i <= m; i++)
        if (edge[i].w > w)
            addedge(edge[i].u, edge[i].v, 1), addedge(edge[i].v, edge[i].u, 1);
    printf("%lld", ans + dinic());
    system("pause");
    return 0;
}