#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
typedef long long ll;
stack<int> pointstack;
vector<int> DAG[20010];
vector<int> vec[20010];
int indu[20010], color[20010], u, v, n, m, dfn[20010], low[20010], scc[20010], f[20010], time1, sccnum;
bool instack[20010];
void tarjan(int u, int fa)
{
    low[u] = dfn[u] = ++time1;
    pointstack.push(u);
    instack[u] = true;
    for (int i = 0; i < vec[u].size(); i++)
    {
        int v = vec[u][i];
        if (dfn[v] == -1)
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
        sccnum++;
        int tmp;
        while (!pointstack.empty())
        {
            tmp = pointstack.top();
            instack[tmp] = false;
            pointstack.pop();
            scc[tmp] = sccnum;
            if (tmp == u)
            {
                break;
            }
        }
    }
}

void addedge2DAG(int u, int v)
{
    DAG[v].push_back(u);
    indu[u]++;
}

void addedge(int u, int v)
{
    vec[u].push_back(v);
}

void TopologicalSorting()
{
    queue<int> q;
    for (int i = 1; i <= sccnum; i++)
    {
        if (indu[i] == 0)
        {
            q.push(i);
        }
    }
    while (!q.empty())
    {
        int tmp = q.front();
        q.pop();
        if (!color[tmp])
            color[tmp] = 1, color[f[tmp]] = 2;
        for (int i = 0; i < DAG[tmp].size(); i++)
        {
            indu[DAG[tmp][i]]--;
            if (indu[DAG[tmp][i]] == 0)
                q.push(DAG[tmp][i]);
        }
    }
}

int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        memset(dfn, -1, sizeof(dfn));
        memset(color, 0, sizeof(color));
        memset(indu, 0, sizeof(indu));
        memset(f, 0, sizeof(f));
        memset(scc, 0, sizeof(scc));
        memset(instack, 0, sizeof(instack));
        memset(low, 0, sizeof(low));
        sccnum = 0;
        while (!pointstack.empty())
            pointstack.pop();
        time1 = 0;
        for (int i = 0; i <= 2 * n; i++)
        {
            DAG[i].clear();
            vec[i].clear();
        }
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d", &u, &v);
            u--, v--;
            addedge(u, v ^ 1);
            addedge(v, u ^ 1);
        }
        //缩点
        bool flag = false;
        for (int i = 0; i < 2 * n; i++)
        {
            if (dfn[i] == -1)
                tarjan(i, i);
        }
        //判断有解
        for (int i = 0; i < 2 * n; i += 2)
        {
            if (scc[i] == scc[i + 1])
            {
                printf("NIE\n");

                flag = true;
                break;
            }
            else
            {
                f[scc[i]] = scc[i + 1];
                f[scc[i + 1]] = scc[i];
            }
        }
        if (flag)
            continue;
        //缩点连边
        for (int i = 0; i < 2 * n; i++)
        {
            for (int j = 0; j < vec[i].size(); j++)
            {
                if (scc[i] != scc[vec[i][j]])
                {
                    addedge2DAG(scc[i], scc[vec[i][j]]);
                }
            }
        }
        //拓扑排序
        TopologicalSorting();

        for (int i = 0; i < 2 * n; i += 2)
        {
            if (color[scc[i]] == 1)
            {
                printf("%d\n", i + 1);
            }
            else
            {
                printf("%d\n", i + 2);
            }
        }
    }
    system("pause");
    return 0;
}