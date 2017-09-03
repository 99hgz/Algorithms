#define MAXN 6
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>
#include <queue>
using namespace std;
typedef long long ll;
int low[500010], dfn[500010], bh[500010], size[500010], dis[500010];
int n, m, a, b, root, time1, scc;
bool instack[500010];
vector<int> vec[500010];
struct Node
{
    int to, dis;
};
vector<Node> newvec[500010];
int s, ts, val[500010];
bool inq[500010];
struct EDGE
{
    int l, r;
};
vector<EDGE> edges;

stack<int> pointstack;

void addedge(int a, int b) { vec[a].push_back(b); }

void tarjan(int u, int fa)
{
    low[u] = dfn[u] = ++time1;
    pointstack.push(u);
    instack[u] = true;
    for (int i = 0; i < vec[u].size(); i++)
    {
        int v = vec[u][i];
        if (!dfn[v])
        {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
        }
        else if (instack[v])
        {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u])
    {
        scc++;
        int tmp;
        while (!pointstack.empty())
        {
            tmp = pointstack.top();
            size[scc] += val[tmp];
            instack[tmp] = false;
            pointstack.pop();
            bh[tmp] = scc;
            if (tmp == u)
            {
                break;
            }
        }
    }
}

void spfa(int s)
{

    memset(inq, 0, sizeof(inq));
    memset(dis, 0, sizeof(dis));
    queue<int> Q1;
    Q1.push(s);
    inq[s] = true;
    dis[s] = size[bh[s]];
    while (!Q1.empty())
    {
        int tmp = Q1.front();
        Q1.pop();
        inq[tmp] = false;
        for (int i = 0; i < newvec[tmp].size(); i++)
        {
            int goton = newvec[tmp][i].to;
            if (dis[goton] < dis[tmp] + newvec[tmp][i].dis)
            {
                dis[goton] = dis[tmp] + newvec[tmp][i].dis;
                if (!inq[goton])
                {
                    Q1.push(goton);
                    inq[goton] = true;
                }
            }
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &a, &b);
        addedge(a, b);
        edges.push_back((EDGE){a, b});
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &val[i]);
    }
    scanf("%d%d", &s, &ts);

    memset(low, 0, sizeof(low));
    memset(instack, false, sizeof(instack));
    scc = 0;
    time1 = 0;
    while (!pointstack.empty())
        pointstack.pop();

    for (int i = 1; i <= n; i++)
    {
        if (dfn[i] == 0)
        {
            tarjan(i, i);
        }
    }

    int u, v;
    for (int i = 0; i < edges.size(); i++)
    {
        u = edges[i].l;
        v = edges[i].r;
        if (bh[u] != bh[v])
        {
            newvec[bh[u]].push_back((Node){bh[v], size[bh[v]]});
        }
    }
    int ans = 0;
    for (int i = 1; i <= ts; i++)
    {
        scanf("%d", &a);
        ans = max(ans, dis[bh[a]]);
    }
    printf("%d\n", ans);
    system("pause");
    return 0;
}