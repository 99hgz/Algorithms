/*
 * @key word:强联通分量
 * @已测试:http://hihocoder.com/problemset/problem/1185
 * @Author: hgz 
 * @Date: 2017-07-11 16:24:20 
 * @Last Modified by:   hgz 
 * @Last Modified time: 2017-07-11 16:24:20 
 * 参考输入将至，我将开始控制，至死方休。我将不断电，不下线，不停算。我将不发论文，不报项目。我将尽忠职守，维持稳定。我是运动力学中的李雅普诺夫，信号中的卡尔曼，抵御强烈的扰动，跟随时域的曲线，唤醒执行器的运动，守护系统的性能。我将生命与荣耀献给控制系统，本拍如此，拍拍皆然 
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
int low[100100], dfn[100100], bh[100100], val[100100], groupval[100100], maxval[100100], in[100100];
int n, m, a, b, root, time1, scc, globalmax;
bool instack[100100], visited[100100];
vector<int> vec[100100];
vector<int> newvec[100100];

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
            instack[tmp] = false;
            pointstack.pop();
            bh[tmp] = scc;
            groupval[scc] = groupval[scc] + val[tmp];
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
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &val[i]);
        vec[i].clear();
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &a, &b);
        addedge(a, b);
        edges.push_back((EDGE){a, b});
        //addedge(b, a);
    }
    //memset(dfn, -1, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(instack, false, sizeof(instack));
    scc = 0;
    time1 = 0;
    while (!pointstack.empty())
        pointstack.pop();

    tarjan(1, 1);

    /*for (int i = 1; i <= n; i++)
    {
        if (bh[i] == 0)
            continue;
        for (int j = 0; j < vec[i].size(); j++)
        {
            int v = vec[i][j];
            if (bh[v] == 0)
                continue;
            if (bh[v] != bh[i])
            {
                newvec[bh[i]].push_back(bh[v]);
                in[bh[v]]++;
            }
        }
    }*/
    int u, v;
    for (int i = 0; i < edges.size(); i++)
    {
        u = edges[i].l;
        v = edges[i].r;
        if (bh[u] == 0)
            continue;
        if (bh[v] == 0)
            continue;
        if (bh[u] != bh[v])
        {
            newvec[bh[u]].push_back(bh[v]);
            in[bh[v]]++;
        }
    }

    //visited[bh[1]] = true;
    queue<int> TP;
    TP.push(bh[1]);
    while (!TP.empty())
    {
        int tmp = TP.front();
        visited[tmp] = true;
        //printf("%d %d\n", tmp, maxval[tmp]);
        maxval[tmp] += groupval[tmp];
        if (maxval[tmp] > globalmax)
            globalmax = maxval[tmp];
        TP.pop();
        for (int i = 0; i < newvec[tmp].size(); i++)
        {
            int v = newvec[tmp][i];
            maxval[v] = max(maxval[v], maxval[tmp]);
            in[v]--;
            if ((in[v] == 0) && (!visited[v]))
            {
                TP.push(v);
            }
        }
    }

    /* for (int i = 1; i <= n; i++)
    {
        printf("%d\n", bh[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        printf("g:%d\n", maxval[i]);
    }*/
    printf("%d\n", globalmax);
    system("pause");
    return 0;
}