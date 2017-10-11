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
vector<int> DAG[300010];
vector<int> vec[300010];
int indu[300010], color[300010], d, tot, u, v, n, m, dfn[300010], low[300010], scc[300010], f[300010], time1, sccnum;
bool instack[300010];
char C[300010], A[300010];
int mp[300010][4];
char hi[100010][5], hj[100010][5];
int ii[100010], j[100010], X[100010], xnum;

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
    //printf("addedge:%d %d\n", u, v);
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

void init()
{
    memset(dfn, -1, sizeof(dfn));
    memset(color, 0, sizeof(color));
    memset(indu, 0, sizeof(indu));
    memset(f, 0, sizeof(f));
    memset(scc, 0, sizeof(scc));
    memset(instack, 0, sizeof(instack));
    memset(low, 0, sizeof(low));
    memset(mp, 0, sizeof(mp));
    sccnum = 0;
    while (!pointstack.empty())
        pointstack.pop();
    time1 = 0;
    tot = 0;
    for (int i = 0; i <= 300010; i++)
    {
        DAG[i].clear();
        vec[i].clear();
    }
}

int check()
{
    init();
    /*printf("check:");
    for (int i = 1; i <= n; i++)
    {
        printf("%c", A[i]);
    }
    printf("\n");*/
    for (int i = 1; i <= n; i++)
    {
        C[tot] = C[tot + 1] = 'A';
        C[tot + 2] = C[tot + 3] = 'B';
        C[tot + 4] = C[tot + 5] = 'C';
        mp[i][0] = tot++;
        tot++;
        mp[i][1] = tot++;
        tot++;
        mp[i][2] = tot++;
        tot++;
        if (A[i] == 'a')
        {
            addedge(mp[i][0], mp[i][0] ^ 1);
            addedge(mp[i][1], mp[i][2] ^ 1);
            addedge(mp[i][2], mp[i][1] ^ 1);
            addedge(mp[i][1] ^ 1, mp[i][2]);
            addedge(mp[i][2] ^ 1, mp[i][1]);
        }
        else if (A[i] == 'b')
        {
            addedge(mp[i][1], mp[i][1] ^ 1);
            addedge(mp[i][0], mp[i][2] ^ 1);
            addedge(mp[i][2], mp[i][0] ^ 1);
            addedge(mp[i][0] ^ 1, mp[i][2]);
            addedge(mp[i][2] ^ 1, mp[i][0]);
        }
        else if (A[i] == 'c')
        {
            addedge(mp[i][2], mp[i][2] ^ 1);
            addedge(mp[i][0], mp[i][1] ^ 1);
            addedge(mp[i][1], mp[i][0] ^ 1);
            addedge(mp[i][0] ^ 1, mp[i][1]);
            addedge(mp[i][1] ^ 1, mp[i][0]);
        }
    }
    for (int i = 1; i <= m; i++)
    {
        if ((hi[i][0] - 'A') == (A[ii[i]] - 'a'))
            continue;
        if ((hj[i][0] - 'A') == (A[j[i]] - 'a'))
        {
            addedge(mp[ii[i]][hi[i][0] - 'A'], mp[ii[i]][hi[i][0] - 'A'] ^ 1);
            continue;
        }
        addedge(mp[ii[i]][hi[i][0] - 'A'], mp[j[i]][hj[i][0] - 'A']);
        addedge(mp[j[i]][hj[i][0] - 'A'] ^ 1, mp[ii[i]][hi[i][0] - 'A'] ^ 1);
    }
    //缩点
    bool flag = false;
    for (int i = 0; i < tot; i++)
    {
        if (dfn[i] == -1)
            tarjan(i, i);
    }
    //判断有解
    for (int i = 0; i < tot; i += 2)
    {
        if (scc[i] == scc[i + 1])
            return -1;
        else
        {
            f[scc[i]] = scc[i + 1];
            f[scc[i + 1]] = scc[i];
        }
    }

    //缩点连边
    for (int i = 0; i < tot; i++)
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

    for (int i = 0; i < tot; i += 2)
    {
        if (color[scc[i]] == 1)
        {
            printf("%c", C[i]);
        }
    }
    return 0;
}

void dfs(int x)
{
    if (x > xnum)
    {
        int tmp = check();
        if (tmp != -1)
        {
            //system("pause");
            exit(0);
        }
        return;
    }
    for (int i = 0; i <= 2; i++)
    {
        A[X[x]] = i + 'a';
        dfs(x + 1);
    }
}

int main()
{
    scanf("%d%d", &n, &d);
    scanf("%s", A + 1);
    for (int i = 1; i <= n; i++)
    {
        if (A[i] == 'x')
        {
            xnum++;
            X[xnum] = i;
        }
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%s%d%s", &ii[i], hi[i], &j[i], hj[i]);

    dfs(1);
    printf("-1\n");
    //system("pause");
    return 0;
}