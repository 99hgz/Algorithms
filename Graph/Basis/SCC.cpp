/*
 * @key word:强联通分量
 * @已测试:http://acm.hdu.edu.cn/showproblem.php?pid=1269
 * @Author: hgz
 * @Date: 2017-07-10 21:14:01
 * @Last Modified by: hgz
 * @Last Modified time: 2017-07-10 22:08:33
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>
using namespace std;
typedef long long ll;
int low[100100], dfn[100100];
int n, m, a, b, root, time1, scc;
bool instack[100100];
vector<int> vec[100100];
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
        if (dfn[v] == -1)
        {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
        }
        else if (instack[u])
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
            instack[tmp] = false;
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
    while ((~scanf("%d%d", &n, &m)) && ((n != 0) || (m != 0)))
    {
        for (int i = 1; i <= n; i++)
            vec[i].clear();
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d", &a, &b);
            addedge(a, b);
            //addedge(b, a);
        }
        memset(dfn, -1, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(instack, false, sizeof(instack));
        scc = 0;
        time1 = 0;
        while (!pointstack.empty())
            pointstack.pop();

        for (int i = 1; i <= n; i++)
        {
            if (dfn[i] == -1)
            {
                root = i;
                tarjan(i, i);
            }
        }
        if (scc == 1)
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
    }
    system("pause");
    return 0;
}