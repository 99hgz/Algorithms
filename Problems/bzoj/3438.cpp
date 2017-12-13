#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;
typedef long long ll;

int Q[5000], dep[5000];

int tot, Head[5000], cur[5000], Next[210000];
ll Val[210000], To[210000];
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
int ai, c1i, c2i, ki, id, bi;
ll sum;
int main()
{
    tot = 1;
    scanf("%d", &n);
    S = 4001;
    T = 4002;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &ai);
        sum += ai;
        addedge(S, i, ai);
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &bi);
        sum += bi;
        addedge(i, T, bi);
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &ki);
        scanf("%d%d", &c1i, &c2i);
        sum += c1i + c2i;
        addedge(n + 2 * i - 1, T, c2i);
        addedge(S, n + 2 * i, c1i);
        for (int j = 1; j <= ki; j++)
        {
            scanf("%d", &id);
            addedge(id, n + 2 * i - 1, 0x3f3f3f3f);
            addedge(n + 2 * i, id, 0x3f3f3f3f);
        }
    }
    printf("%lld", sum - dinic());
    system("pause");
    return 0;
}