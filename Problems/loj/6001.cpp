#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
typedef long long ll;

int Q[110], dep[110];

int tot, Head[110], cur[110], Next[21000];
ll Val[21000], To[21000], Trueflow[21000];
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

void addedge(int u, int v, ll flow, ll t_flow)
{
    //printf("%d->%d %lld\n", u, v, flow);
    tot++;
    Next[tot] = Head[u];
    Head[u] = tot;
    Val[tot] = flow;
    To[tot] = v;
    Trueflow[tot] = t_flow;
    tot++;
    Next[tot] = Head[v];
    Head[v] = tot;
    Val[tot] = 0;
    To[tot] = u;
    Trueflow[tot] = t_flow;
}

ll sum;
char data[500];
int main()
{
    tot = 1;
    cin.getline(data, 300);

    char *tokenPtr = strtok(data, " ");

    m = atoi(tokenPtr);
    tokenPtr = strtok(NULL, " ");
    n = atoi(tokenPtr);
    S = m + n + 1;
    T = m + n + 2;
    for (int i = 1; i <= m; i++)
    {
        cin.getline(data, 300);

        char *tokenPtr = strtok(data, " ");
        int cost = atoi(tokenPtr);
        sum += cost;
        addedge(S, i, cost, cost);
        tokenPtr = strtok(NULL, " ");
        while (tokenPtr != NULL)
        {
            int v = atoi(tokenPtr);
            addedge(i, m + v, 0x3f3f3f3f, 0x3f3f3f3f);
            tokenPtr = strtok(NULL, " ");
        }
    }
    for (int i = 1; i <= n; i++)
    {
        int cost;
        cin >> cost;
        //printf("%d\n", cost);
        addedge(m + i, T, cost, cost);
    }
    ll tmp = dinic();

    printf("%lld\n", sum - tmp);

    system("pause");
    return 0;
}