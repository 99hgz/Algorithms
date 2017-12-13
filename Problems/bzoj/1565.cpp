#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;
typedef long long ll;

int Q[1100], dep[1100], score[1000];

int tot, Head[1100], cur[1100], Next[21000];
ll Val[21000], To[21000];
int n, m, S, T, u, v;

int calc(int x, int y)
{
    return (x - 1) * m + y;
}

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

vector<int> vec[1000];
vector<int> revec[1000];
int indegree[1000];
bool chose[1000];
void addedge1(int u, int v)
{
    vec[u].push_back(v);
    revec[v].push_back(u);
    indegree[u]++;
}

void topsort()
{
    queue<int> Q;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (indegree[calc(i, j)] == 0)
                Q.push(calc(i, j));
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        chose[u] = true;
        for (int i = 0; i < revec[u].size(); i++)
        {
            int v = revec[u][i];
            indegree[v]--;
            if (indegree[v] == 0)
                Q.push(v);
        }
    }
}
int SUM;
void build()
{
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            int id = calc(i, j);
            if (!chose[id])
                continue;
            if (score[id] >= 0)
            {
                SUM += score[id];
                addedge(S, id, score[id]);
            }
            else
                addedge(id, T, -score[id]);
            for (int it = 0; it < vec[id].size(); it++)
                addedge(id, vec[id][it], 0x3f3f3f3f);
        }
}

int main()
{
    tot = 1;
    scanf("%d%d", &n, &m);
    S = n * m + 1;
    T = n * m + 2;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (j != m)
                addedge1(calc(i, j), calc(i, j + 1));
            scanf("%d", &score[calc(i, j)]);
            int nnum;
            scanf("%d", &nnum);
            for (int k = 1; k <= nnum; k++)
            {
                int x, y;
                scanf("%d%d", &x, &y);
                x++, y++;
                addedge1(calc(x, y), calc(i, j));
            }
        }
    }
    topsort();
    build();
    printf("%lld", SUM - dinic());
    system("pause");
    return 0;
}