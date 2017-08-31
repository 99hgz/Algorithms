#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

struct edge
{
    int point, dis;
};
vector<edge> hmap[300005];
struct Node
{
    int u, v, w;
};
vector<Node> edges;
int parent[300005], ans, n, m, t, mid, u, v;
bool vis[300005];
int deep[300005], val[300005], tmp[300005];
int toroot[300005];
int p[300005][20];
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

void dfs(int p, int deep1, int dis)
{
    //printf("%d %d %d\n", p, deep1, dis);
    vector<edge>::iterator it;
    deep[p] = deep1;
    toroot[p] = dis;
    for (it = hmap[p].begin(); it != hmap[p].end(); it++)
    {
        if (!vis[(*it).point])
        {
            vis[(*it).point] = true;
            parent[(*it).point] = p;
            val[(*it).point] = (*it).dis;
            dfs((*it).point, deep1 + 1, dis + (*it).dis);
        }
    }
}

void dfs2(int p, int fa)
{
    vector<edge>::iterator it;
    for (it = hmap[p].begin(); it != hmap[p].end(); it++)
    {
        if ((*it).point != fa)
        {
            dfs2((*it).point, p);
            tmp[p] += tmp[(*it).point];
        }
    }
}

bool pd(int x)
{
    memset(tmp, 0, sizeof tmp);
    int tot = 0;
    int limit = 0;
    for (int i = 0; i < m; i++)
    {
        if (edges[i].w > x)
        {
            printf("%d %d %d\n", edges[i].u, edges[i].v, edges[i].w);
            tot++;
            tmp[edges[i].u]++;
            tmp[edges[i].v]++;
            tmp[lca(edges[i].u, edges[i].v)] -= 2;
            limit = max(limit, edges[i].w - x);
        }
    }
    if (tot == 0)
        return true;
    dfs2(1, 1);
    for (int i = 2; i <= n; i++)
    {
        if (tmp[i] == tot && limit <= val[i])
            return true;
    }
    return false;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d%d", &u, &v, &t);
        hmap[u].push_back((edge){v, t});
        hmap[v].push_back((edge){u, t});
    }
    dfs(1, 1, 0);
    init(n);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        edges.push_back((Node){u, v, toroot[u] + toroot[v] - 2 * toroot[lca(u, v)]});
    }

    int l = 0, r = 1000 * m, ans;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (pd(mid))
        {
            r = mid - 1;
            ans = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    printf("%d\n", ans);
    system("pause");
    return 0;
}