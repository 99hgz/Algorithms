/*
 * @key word:强联通分量
 * @已测试:http://acm.hdu.edu.cn/showproblem.php?pid=1269
 * @Author: hgz
 * @Date: 2017-07-10 21:14:01
 * @Last Modified by: hgz
 * @Last Modified time: 2017-07-11 22:51:01
 */
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
int low[10100], dfn[10100], bh[100100], in[10100], size[10100];
int n, m, a, b, root, time1, scc;
bool instack[10100];
vector<int> vec[100100];
vector<int> newvec[10100];

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
            size[scc]++;
            tmp = pointstack.top();
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

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &a, &b);
        addedge(a, b);
        edges.push_back((EDGE){a, b});
    }
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
            newvec[bh[u]].push_back(bh[v]);
            in[bh[u]]++;
        }
    }
    int ans = 0;
    for (int i = 1; i <= scc; i++)
    {
        if (in[i] == 0)
        {
            if (ans)
            {
                printf("0\n");
                return 0;
            }
            ans = i;
        }
    }
    printf("%d\n", size[ans]);
    system("pause");
    return 0;
}