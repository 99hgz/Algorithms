#include <cmath>
#include <vector>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
using namespace std;
vector<int> hmap[300010];
int parent[300010];
bool vis[300010];
int deep[300010];
int toroot[300010], ans[300010], val[300010], to[300010];
int p[300010][20], n, m, a, b, k;
void init(int n)
{
    int st;
    st = floor(log(n) / log(2));
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= st; j++)
            p[i][j] = -1;
    for (int i = 1; i <= n; i++)
        p[i][0] = parent[i];
    for (int j = 1; j <= st; j++)
        for (int i = 1; i <= n; i++)
            if (p[i][j - 1] != -1)
                p[i][j] = p[p[i][j - 1]][j - 1];
}
int lca(int a, int b)
{
    if (deep[a] < deep[b])
        swap(a, b);
    int st = floor(log(deep[a] - 1) / log(2));
    for (int i = st; i >= 0; i--)
        if (deep[a] - (1 << i) >= deep[b])
        {
            a = p[a][i];
        }
    if (a == b)
        return a;
    for (int i = st; i >= 0; i--)
        if ((p[a][i] != -1) && (p[a][i] != p[b][i]))
        {
            a = p[a][i];
            b = p[b][i];
        }
    return parent[a];
}

void dfs(int p, int deep1)
{
    vector<int>::iterator it;
    deep[p] = deep1;
    for (it = hmap[p].begin(); it != hmap[p].end(); it++)
    {
        if (!vis[(*it)])
        {
            vis[(*it)] = true;
            parent[(*it)] = p;
            dfs((*it), deep1 + 1);
        }
    }
}

void dfs2(int x, int fa)
{
    for (int i = 0; i < hmap[x].size(); i++)
    {
        int v = hmap[x][i];
        if (fa != v)
        {
            dfs2(v, x);
            ans[x] += ans[v];
        }
    }
    ans[x] += val[x];
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &to[i]);
    }
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &a, &b);
        hmap[a].push_back(b);
        hmap[b].push_back(a);
    }
    vis[1] = true;
    dfs(1, 1);
    init(n);
    for (int i = 2; i <= n; i++)
    {
        int u = to[i - 1], v = to[i];
        val[u]++;
        val[v]++;
        val[lca(u, v)]--;
        val[parent[lca(u, v)]]--;
    }
    dfs2(1, 1);
    for (int i = 2; i <= n; i++)
    {
        ans[to[i]]--;
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%d\n", ans[i]);
    }
    system("pause");
}