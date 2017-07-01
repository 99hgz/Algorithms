/*
 * @key word:LCA
 * @已测试:http://192.68.1.216/JudgeOnline/showsource.php?id=35671
 * @Author: hgz 
 * @Date: 2017-06-30 09:56:16 
 * @Last Modified by: hgz
 * @Last Modified time: 2017-06-30 09:57:16
 * 参考输入将至，我将开始控制，至死方休。我将不断电，不下线，不停算。我将不发论文，不报项目。我将尽忠职守，维持稳定。我是运动力学中的李雅普诺夫，信号中的卡尔曼，抵御强烈的扰动，跟随时域的曲线，唤醒执行器的运动，守护系统的性能。我将生命与荣耀献给控制系统，本拍如此，拍拍皆然 
 */
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
struct NODE
{
    int to, w;
} node;
struct aSK
{
    int to, bh;
} ASK;
struct tG_ASK
{
    int to, from;
} G_ask;
int n, m, c, a, b, cc;
int fa[10010], DEEP[10010], ancestor[10010];
vector<NODE> path[10010];
vector<aSK> ask[1000000];
vector<tG_ASK> g_ask;
int ans[1000000];
bool visited[10010], global_visited[10010];
void make_set(int a)
{
    fa[a] = a;
}

int find_set(int a)
{
    return fa[a] == a ? a : fa[a] = find_set(fa[a]);
}

void union_set(int a, int b)
{
    int ta = find_set(a);
    int tb = find_set(b);
    fa[ta] = tb;
}

void lca(int u, int deep)
{
    DEEP[u] = deep;
    make_set(u);
    int fa = find_set(u);
    ancestor[fa] = u;
    global_visited[u] = true;
    for (int i = 0; i < path[u].size(); i++)
    {
        if (!global_visited[path[u][i].to])
        {
            lca(path[u][i].to, deep + path[u][i].w);
            union_set(u, path[u][i].to);
            ancestor[find_set(u)] = u;
        }
    }
    visited[u] = true;
    for (int i = 0; i < ask[u].size(); i++)
    {
        if (visited[ask[u][i].to])
            ans[ask[u][i].bh] = ancestor[find_set(ask[u][i].to)];
    }
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        memset(global_visited, 0, sizeof(global_visited));
        memset(visited, 0, sizeof(visited));
        memset(fa, 0, sizeof(fa));
        g_ask.clear();
        scanf("%d%d%d", &n, &m, &c);
        for (int i = 1; i <= n; i++)
        {
            path[i].clear();
            ask[i].clear();
        }
        for (int i = 0; i < m; i++)
        {
            scanf("%d%d%d", &a, &b, &cc);
            node.to = b;
            node.w = cc;
            path[a].push_back(node);
            node.to = a;
            path[b].push_back(node);
        }
        for (int i = 0; i < c; i++)
        {
            scanf("%d%d", &a, &b);
            ASK.to = b;
            ASK.bh = i;
            ask[a].push_back(ASK);
            ASK.to = a;
            ask[b].push_back(ASK);
            G_ask.from = a;
            G_ask.to = b;
            g_ask.push_back(G_ask);
        }
        for (int i = 1; i <= n; i++)
        {
            memset(visited, 0, sizeof(visited));
            if (!global_visited[i])
                lca(i, 1);
        }
        //printf("%d",c);
        for (int i = 0; i < c; i++)
        {
            if (ans[i] == 0)
                printf("Not connected\n");
            else
                printf("%d\n", abs(DEEP[g_ask[i].to] - DEEP[ans[i]]) + abs(DEEP[g_ask[i].from] - DEEP[ans[i]]));
        }
    }
}