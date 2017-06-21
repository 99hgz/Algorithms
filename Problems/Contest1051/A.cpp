#define maxn 2010
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <climits>
using namespace std;
int n, pathnum;
int time[maxn], lim[maxn];
bool used[maxn][maxn];
int best[maxn];
int dp[maxn][maxn];
bool visited[maxn], f_visited[maxn];
int ans = INT_MAX;
struct PATH
{
    int to, len;
} path[maxn * 2];

vector<int> son[maxn];

typedef long long ll;

void fetch(int s, int npoint, int ndeep, int tdeep)
{
    if (tdeep > ndeep)
    {
        return;
    }
    f_visited[npoint] = true;
    used[s][npoint] = true;
    for (int i = 0; i < son[npoint].size(); i++)
    {
        if (f_visited[path[son[npoint][i]].to] == false)
        {
            fetch(s, path[son[npoint][i]].to, ndeep, tdeep + path[son[npoint][i]].len);
        }
    }
    f_visited[npoint] = false;
}

void build_tree(int point)
{
    visited[point] = true;
    fetch(point, point, lim[point], 0);
    for (int i = 0; i < son[point].size(); i++)
    {
        if (visited[path[son[point][i]].to] == false)
            build_tree(path[son[point][i]].to);
    }
    visited[point] = false;
}

void dfs(int u)
{
    visited[u] = true;
    for (int i = 0; i < son[u].size(); i++)
    {
        if (visited[path[son[u][i]].to] == false)
            dfs(path[son[u][i]].to);
    }
    best[u] = INT_MAX;
    for (int w = 1; w <= n; w++)
    {
        if (used[u][w])
        {
            dp[u][w] = time[w];
            for (int i = 0; i < son[u].size(); i++)
                dp[u][w] += min(dp[path[son[u][i]].to][w] - time[w], best[path[son[u][i]].to]);
            best[u] = min(best[u], dp[u][w]);
        }
    }
    //printf("%d %d\n", u, best[u]);
    visited[u] = false;
}

int main()
{
    int t = 1;
    while (t--)
    {
        scanf("%d", &n);
        memset(dp, 127, sizeof(dp));
        memset(used, 0, sizeof(used));
        memset(best, 0, sizeof(best));
        for (int i = 1; i <= n; i++)
        {
            son[i].clear();
            scanf("%d", &time[i]);
        }
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &lim[i]);
        }
        int u, v, len;
        pathnum = 0;
        for (int i = 1; i <= n - 1; i++)
        {
            scanf("%d%d%d", &u, &v, &len);
            path[++pathnum].to = v;
            path[pathnum].len = len;
            son[u].push_back(pathnum);
            path[++pathnum].to = u;
            path[pathnum].len = len;
            son[v].push_back(pathnum);
        }
        build_tree(1);
        dfs(1);
        printf("%d\n", best[1]);
    }
    system("pause");
    return 0;
}