#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;
typedef long long ll;

int Q[1100], dep[1100];

int tot, Head[1100], cur[1100], To[100100], Next[100100], Id[100100];
ll Val[100100];
int n, m, S, T, u, v;

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
        for (int i = 1; i <= T; i++)
            cur[i] = Head[i];
        ans += dfs(S, 1LL << 60);
        //printf("%lld\n", ans);
    }
    return ans;
}

void _addedge(int u, int v, ll flow, int id)
{
    //printf("%d->%d\n", u, v);
    tot++;
    Id[tot] = id;
    Next[tot] = Head[u];
    Head[u] = tot;
    Val[tot] = flow;
    To[tot] = v;
    tot++;
    Id[tot] = id;
    Next[tot] = Head[v];
    Head[v] = tot;
    Val[tot] = 0;
    To[tot] = u;
}

void addedge(int u, int v, ll lower, ll upper, int id)
{
    _addedge(S, v, lower, id);
    _addedge(u, v, upper - lower, id);
    _addedge(u, T, lower, 0);
}
struct EDGE
{
    int u, v;
    ll lower, upper;
} edge[100100];
ll ans[100100];
int main()
{
    tot = 1;
    int s, t;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    S = n + 1;
    T = n + 2;
    ll sum = 0;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%lld%lld", &edge[i].u, &edge[i].v, &edge[i].lower, &edge[i].upper);
        addedge(edge[i].u, edge[i].v, edge[i].lower, edge[i].upper, i);
        sum += edge[i].lower;
    }
    _addedge(t, s, 0x3f3f3f3f, 1);
    ll flow1 = dinic();
    if (sum == flow1)
    {
        S = s;
        T = t;
        flow1 = 0;
        flow1 += dinic();
        printf("%lld\n", flow1);
    }
    else
    {
        printf("please go home to sleep\n");
    }

    return 0;
}