/*
 * @开坑待填。。。
 * @Author: hgz 
 * @Date: 2017-04-27 15:41:09 
 * @Last Modified by: hgz
 * @Last Modified time: 2017-04-27 15:41:32
 * 参考输入将至，我将开始控制，至死方休。我将不断电，不下线，不停算。我将不发论文，不报项目。我将尽忠职守，维持稳定。我是运动力学中的李雅普诺夫，信号中的卡尔曼，抵御强烈的扰动，跟随时域的曲线，唤醒执行器的运动，守护系统的性能。我将生命与荣耀献给控制系统，本拍如此，拍拍皆然 
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
using namespace std;
const int maxn = 16005;
const int maxm = 200005;
int head[maxn], next[maxm], to[maxm];
int dfn[maxn], low[maxn], stk[maxn], scc[maxn], ind[maxn], vis[maxn];
int color[maxn], f[maxn];
int tot, top, cnt, id;
vector<int> dag[maxn];
void addEdage(int u, int v)
{
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
}
void init()
{
    memset(head, -1, sizeof(head));
    memset(vis, 0, sizeof(vis));
    memset(dfn, 0, sizeof(dfn));
    memset(ind, 0, sizeof(ind));
    memset(color, 0, sizeof(color));
    tot = top = cnt = id = 0;
}
void tarjan(int v)
{
    dfn[v] = low[v] = ++cnt;
    vis[v] = 1;
    stk[++top] = v;
    for (int i = head[v]; i != -1; i = next[i])
    {
        int u = to[i];
        if (!dfn[u])
        {
            tarjan(u);
            low[v] = min(low[v], low[u]);
        }
        else if (vis[u])
            low[v] = min(low[v], dfn[u]);
    }
    if (low[v] == dfn[v])
    {
        id++;
        while (true)
        {
            int u = stk[top--];
            vis[u] = 0;
            scc[u] = id;
            if (u == v)
                break;
        }
    }
}
void buildDag(int n)
{
    for (int u = 0; u < 2 * n; u++)
        for (int i = head[u]; i != -1; i = next[i])
        {
            int v = to[i];
            if (scc[v] != scc[u])
            {
                dag[scc[v]].push_back(scc[u]);
                ind[scc[u]]++;
            }
        }
}
void topsort()
{
    queue<int> q;
    for (int i = 1; i <= id; i++)
        if (!ind[i])
            q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (!color[u])
            color[u] = 1, color[f[u]] = 2;
        for (int i = 0; i < (int)dag[u].size(); i++)
        {
            int v = dag[u][i];
            ind[v]--;
            if (!ind[v])
                q.push(v);
        }
    }
}
void solve(int n)
{
    for (int i = 0; i < 2 * n; i++)
        if (!dfn[i])
            tarjan(i);
    for (int i = 0; i < 2 * n; i += 2)
        if (scc[i] == scc[i + 1])
        {
            printf("NIE\n");
            return;
        }
        else
            f[scc[i]] = scc[i + 1], f[scc[i + 1]] = scc[i];
    for (int i = 0; i <= id; i++)
        dag[i].clear();
    buildDag(n);
    topsort();
    for (int i = 0; i < 2 * n; i += 2)
    {
        if (color[scc[i]] == 1)
            printf("%d\n", i + 1);
        else
            printf("%d\n", i + 2);
    }
}
int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m))
    {
        init();
        for (int i = 0, a, b; i < m; i++)
        {
            scanf("%d%d", &a, &b);
            a--, b--;
            addEdage(a, b ^ 1);
            addEdage(b, a ^ 1);
        }
        solve(n);
    }
    return 0;
}