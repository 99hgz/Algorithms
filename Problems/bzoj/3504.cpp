#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;
typedef long long ll;

int Q[11000], dep[11000];

int tot, Head[11000], cur[11000], Next[500010];
ll Val[500010], To[500010];
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
    //printf("%d->%d flow=%lld\n", u, v, flow);
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

int calc(int sorted, int i, int j)
{
    if (sorted && i > j)
        swap(i, j);
    return (i - 1) * n + j;
}

char mp[100][100];

int main()
{
    while (~scanf("%d", &n))
    {
        memset(Head, 0, sizeof Head);
        //memset(cur, 0, sizeof cur);
        tot = 1;

        int a2, a1, an, b1, b2, bn;
        scanf("%d%d%d%d%d%d", &a1, &a2, &an, &b1, &b2, &bn);
        a1++, a2++, b1++, b2++;
        S = n + 5;
        T = n + 6;
        for (int i = 1; i <= n; i++)
        {
            scanf("%s", mp[i] + 1);
        }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j < i; j++)
                addedge(i, j, mp[i][j] == 'O' ? 2 : (mp[i][j] == 'N' ? 0x3f3f3f3f : 0)),
                    addedge(j, i, mp[i][j] == 'O' ? 2 : (mp[i][j] == 'N' ? 0x3f3f3f3f : 0));
        addedge(S, a1, an * 2);
        addedge(S, b1, bn * 2);
        addedge(a2, T, an * 2);
        addedge(b2, T, bn * 2);
        int F1 = dinic();
        //printf("%d\n", F1);
        memset(Head, 0, sizeof Head);
        tot = 1;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j < i; j++)
                addedge(i, j, mp[i][j] == 'O' ? 2 : (mp[i][j] == 'N' ? 0x3f3f3f3f : 0)),
                    addedge(j, i, mp[i][j] == 'O' ? 2 : (mp[i][j] == 'N' ? 0x3f3f3f3f : 0));
        addedge(S, a1, an * 2);
        addedge(S, b2, bn * 2);
        addedge(a2, T, an * 2);
        addedge(b1, T, bn * 2);
        int F2 = dinic();
        puts((F1 < 2 * (an + bn) || F2 < 2 * (an + bn) ? "No" : "Yes"));
    }
    system("pause");
    return 0;
}