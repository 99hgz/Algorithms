#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>
using namespace std;
typedef long long ll;
int low[100100], dfn[100100], ans[100100];
int n, m, a, b, root, time1, dcc, s, t, globalbh;
bool visited[100100];
struct EDGE
{
    int to, bh;
};
vector<EDGE> vec[100100];
struct BRIDGE
{
    int u, v;
};
vector<BRIDGE> bridge;
stack<int> pointstack;
void addedge(int a, int b)
{
    vec[a].push_back((EDGE){b, globalbh++});
}
bool cmp(BRIDGE a, BRIDGE b)
{
    if (a.u == b.u)
        return (a.v < b.v);
    else
        return (a.u < b.u);
}
void tarjan(int u, int fa, int lastbh)
{
    low[u] = dfn[u] = ++time1;
    visited[u] = true;
    int son = 0;
    pointstack.push(u);
    for (int i = 0; i < vec[u].size(); i++)
    {
        int v = vec[u][i].to;
        if (!visited[v])
        {
            son++;
            tarjan(v, u, vec[u][i].bh);
            low[u] = min(low[u], low[v]);
            if (dfn[u] < low[v])
            {
                int tu = u, tv = v;
                if (u > v)
                    swap(tu, tv);
                //printf("BRIDGE:%d %d\n", tu, tv);
                //bridge.push_back((BRIDGE){tu, tv});
            }
        }
        else if ((fa != v) || ((fa == v) && ((vec[u][i].bh ^ 1) != lastbh)))
        {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u])
    {
        dcc++;
        int tmp;
        while (!pointstack.empty())
        {
            tmp = pointstack.top();
            ans[tmp] = dcc;
            pointstack.pop();
            if (tmp == u)
            {
                break;
            }
        }
    }
}

int main()
{
    int t;
    scanf("%d\n", &t);
    while (~scanf("%d%d", &n, &m))
    {
        globalbh = 0;
        dcc = 0;
        time1 = 0;
        for (int i = 1; i <= n; i++)
        {
            vec[i].clear();
        }
        while (!pointstack.empty())
        {
            pointstack.pop();
        }
        memset(low, 0, sizeof(low));
        memset(dfn, 0, sizeof(dfn));
        memset(ans, 0, sizeof(ans));
        memset(visited, 0, sizeof(visited));
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d", &a, &b);
            addedge(a, b);
            addedge(b, a);
        }
        for (int i = 1; i <= n; i++)
        {
            if (!visited[i])
            {
                root = i;
                tarjan(i, i, 0);
            }
        }
        scanf("%d%d", &s, &t);
        if (ans[s] == ans[t])
            printf("YES\n");
        else
            printf("NO\n");
    }
    system("pause");
    return 0;
}