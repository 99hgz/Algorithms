#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;
typedef int ll;

int Q[1010], dep[1010];

int tot, Head[1010], cur[1010], Next[300000];
ll Val[300000], To[300000];
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
        ans += dfs(S, 0x3f3f3f3f);
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
int val[100010];
int main()
{
    tot = 1;
    scanf("%d%d", &n, &m);
    S = n + 1;
    T = n + 2;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &val[i]);
        if (val[i] == 1)
            addedge(S, i, 1), addedge(i, T, 0);
        else
            addedge(i, T, 1), addedge(S, i, 0);
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        addedge(u, v, 1);
        addedge(v, u, 1);
    }
    printf("%d", dinic());
    system("pause");
    return 0;
}