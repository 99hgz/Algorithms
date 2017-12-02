#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;
typedef long long ll;

int Q[51000], dep[51000];

int tot, Head[51000], cur[51000], Next[401000];
ll Val[401000], To[401000];
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

int cx[9] = {0, 0, 0, 1, -1};
int cy[9] = {0, 1, -1, 0, 0};

int calc(int x, int y, int cases)
{
    return (((x - 1) * m + y - 1) * 3 + cases);
}
int science[110][110], art[110][110], s_science[110][110], s_art[110][110];
int main()
{
    tot = 1;
    scanf("%d%d", &n, &m);
    S = n * m * 3 + 1;
    T = n * m * 3 + 2;
    ll sum = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &art[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &science[i][j]);
            sum += art[i][j] + science[i][j];
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &s_art[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &s_science[i][j]);
            sum += s_art[i][j] + s_science[i][j];
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            addedge(S, calc(i, j, 1), art[i][j] + s_art[i][j]);
            addedge(calc(i, j, 1), T, science[i][j] + s_science[i][j]);
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            addedge(calc(i, j, 1), calc(i, j, 2), s_art[i][j]);
            for (int fx = 1; fx <= 4; fx++)
            {
                int tx = i + cx[fx], ty = j + cy[fx];
                if (tx < 1 || tx > n || ty < 1 || ty > m)
                    continue;
                addedge(calc(i, j, 2), calc(tx, ty, 1), 0x3f3f3f3f);
            }
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            addedge(calc(i, j, 3), calc(i, j, 1), s_science[i][j]);
            for (int fx = 1; fx <= 4; fx++)
            {
                int tx = i + cx[fx], ty = j + cy[fx];
                if (tx < 1 || tx > n || ty < 1 || ty > m)
                    continue;
                addedge(calc(tx, ty, 1), calc(i, j, 3), 0x3f3f3f3f);
            }
        }
    printf("%lld", sum - dinic());
    system("pause");
    return 0;
}