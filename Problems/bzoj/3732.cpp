#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;
typedef long long ll;

struct Node
{
    int w, u, v;
    bool operator<(const Node &dd) const
    {
        return w > dd.w;
    }
};

struct GraphNode
{
    int v, w;
};

vector<GraphNode> vec[15100];
vector<GraphNode> vec2[15100];
bool vis[15100];

int deep[15100], father[15100][20], st[15100][20], n, m, k, u, v, w;

void addedgeTree(int u, int v, int w)
{
    vec2[u].push_back((GraphNode){v, w});
}
void addedge(int u, int v, int w)
{
    vec[u].push_back((GraphNode){v, w});
}
void queue_prim()
{
    priority_queue<Node> Q;
    Q.push((Node){0, 0, 1});
    while (!Q.empty())
    {
        Node tmp = Q.top();
        Q.pop();
        if (vis[tmp.v])
            continue;
        vis[tmp.v] = true;
        // printf("chosen:%d %d %d\n", tmp.u, tmp.v, tmp.w);
        if (tmp.u != 0)
        {
            addedgeTree(tmp.u, tmp.v, tmp.w);
            addedgeTree(tmp.v, tmp.u, tmp.w);
        }
        for (int i = 0; i < vec[tmp.v].size(); i++)
        {
            int v = vec[tmp.v][i].v;
            Q.push((Node){vec[tmp.v][i].w, tmp.v, v});
        }
    }
}

void dfs(int x, int fa, int w, int dep)
{
    deep[x] = dep;
    father[x][0] = fa;
    st[x][0] = w;
    for (int i = 0; i < vec2[x].size(); i++)
    {
        int v = vec2[x][i].v;
        if (fa != v)
        {
            dfs(v, x, vec2[x][i].w, dep + 1);
        }
    }
}

void init()
{
    for (int i = 1; i <= 15; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            father[j][i] = -1;
        }
    }
    for (int i = 1; i <= 15; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (father[j][i - 1] != -1)
            {
                father[j][i] = father[father[j][i - 1]][i - 1];
                st[j][i] = max(st[j][i - 1], st[father[j][i - 1]][i - 1]);
            }
        }
    }
}

int lca(int a, int b)
{
    int res = 0;
    if (deep[a] < deep[b])
        swap(a, b);
    int st2 = floor(log(deep[a] - 1) / log(2));
    for (int i = st2; i >= 0; i--)
        if (deep[a] - (1 << i) >= deep[b])
        {
            res = max(res, st[a][i]);
            a = father[a][i];
            //printf("jump to %d %d\n", a, b);
        }
    if (a == b)
        return res;
    for (int i = st2; i >= 0; i--)
        if ((father[a][i] != -1) && (father[a][i] != father[b][i]))
        {
            res = max(res, st[a][i]);
            res = max(res, st[b][i]);
            a = father[a][i];
            b = father[b][i];
            //printf("jump to %d %d\n", a, b);
        }
    return max(st[b][0], max(res, st[a][0]));
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        addedge(u, v, w);
        addedge(v, u, w);
    }
    queue_prim();
    dfs(1, 0, 0, 1);
    init();
    for (int i = 1; i <= k; i++)
    {
        scanf("%d%d", &u, &v);
        printf("%d\n", lca(u, v));
    }

    return 0;
}