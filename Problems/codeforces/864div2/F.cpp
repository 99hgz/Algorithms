#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

bool visit[3010];
vector<int> vec[3010];
vector<int> revec[3010];
int ST[3010][20];
int n, m, q, x, y, s, t, k, ans[400010];
struct Node
{
    int u, k, i;
};
vector<Node> query[3010];

void addedge(int u, int v)
{
    vec[u].push_back(v);
    revec[v].push_back(u);
}

void dfs(int x)
{
    visit[x] = true;
    for (int i = 0; i < revec[x].size(); i++)
    {
        int v = revec[x][i];
        if (!visit[v])
        {
            dfs(v);
        }
    }
}

void init_st(int x)
{
    memset(ST, -1, sizeof ST);
    for (int i = 1; i <= n; i++)
    {
        if (x == i)
        {
            //ST[x][0] = x;
            continue;
        }
        int minp = n + 1;
        for (int j = 0; j < vec[i].size(); j++)
        {
            int v = vec[i][j];
            if (visit[v])
            {
                minp = min(minp, v);
            }
        }
        if (minp == n + 1)
        {
            ST[i][0] = -1;
        }
        else
        {
            ST[i][0] = minp;
            //printf("%d %d\n", i, ST[i][0]);
        }
    }
    for (int i = 1; i <= 15; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (ST[j][i - 1] != -1)
                ST[j][i] = ST[ST[j][i - 1]][i - 1];
        }
    }
}

int jump(int x, int steps)
{
    int now = x;
    for (int i = 15; i >= 0; i--)
    {
        if (steps >= (1 << i))
        {
            now = ST[now][i];
            if (now == -1)
                return now;
            steps -= (1 << i);
        }
    }
    return now;
}

int main()
{
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &x, &y);
        addedge(x, y);
    }
    for (int i = 1; i <= q; i++)
    {
        scanf("%d%d%d", &s, &t, &k);
        query[t].push_back((Node){s, k, i});
    }
    for (int i = 1; i <= n; i++)
    {
        if (query[i].size() == 0)
        {
            continue;
        }
        else
        {
            memset(visit, 0, sizeof visit);
            dfs(i);
            init_st(i);
            /*printf("t=%d-----\n", i);
            for (int i = 1; i <= n; i++)
            {
                printf("%d-%d\n", i, ST[i][0]);
            }
            printf("-----\n");*/
            for (int j = 0; j < query[i].size(); j++)
            {
                int u = query[i][j].u;
                if (!visit[u] || jump(u, 2 * n) != -1)
                {
                    ans[query[i][j].i] = -1;
                    continue;
                }
                else
                {
                    ans[query[i][j].i] = jump(u, query[i][j].k - 1);
                }
            }
        }
    }
    for (int i = 1; i <= q; i++)
    {
        printf("%d\n", ans[i]);
    }
    system("pause");
    return 0;
}