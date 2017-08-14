#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
#define inf 0x7fffffff
using namespace std;
int n;
double d;
struct Edge
{
    int u, v, cap;
    Edge() {}
    Edge(int u, int v, int cap) : u(u), v(v), cap(cap) {}
} es[509 * 509];
int R, S, T;
vector<int> tab[509]; // 边集
int dis[509];
char A[509][509];
int current[509];
int ans;
void addedge(int u, int v, int cap)
{
    //printf("%d %d\n", u, v);
    tab[u].push_back(R);
    es[R++] = Edge(u, v, cap); // 正向边
    tab[v].push_back(R);
    es[R++] = Edge(v, u, 0); // 反向边容量为0
                             // 正向边下标通过异或就得到反向边下标, 2 ^ 1 == 3 ; 3 ^ 1 == 2
}
int BFS()
{
    queue<int> q;
    q.push(S);
    memset(dis, 0x3f3f3f3f, sizeof(dis));
    dis[S] = 0;
    while (!q.empty())
    {
        int h = q.front();
        q.pop();
        for (int i = 0; i < tab[h].size(); i++)
        {
            Edge &e = es[tab[h][i]];
            if (e.cap > 0 && dis[e.v] == 0x3f3f3f3f)
            {
                dis[e.v] = dis[h] + 1;
                q.push(e.v);
            }
        }
    }
    return dis[T] < 0x3f3f3f3f; // 返回是否能够到达汇点
}
int dinic(int x, int maxflow)
{
    if (x == T)
        return maxflow;
    // i = current[x] 当前弧优化
    for (int i = current[x]; i < tab[x].size(); i++)
    {
        current[x] = i;
        Edge &e = es[tab[x][i]];
        if (dis[e.v] == dis[x] + 1 && e.cap > 0)
        {
            int flow = dinic(e.v, min(maxflow, e.cap));
            if (flow)
            {
                e.cap -= flow;                 // 正向边流量降低
                es[tab[x][i] ^ 1].cap += flow; // 反向边流量增加
                return flow;
            }
        }
    }
    return 0; // 找不到增广路 退出
}
int DINIC()
{
    int ans = 0;

    while (BFS()) // 建立分层图
    {
        int flow;
        memset(current, 0, sizeof(current)); // BFS后应当清空当前弧数组
        while (flow = dinic(S, 0x3f3f3f3f))  // 一次BFS可以进行多次增广
            ans += flow;
    }
    return ans;
}

void init()
{
    R = 0;
    for (int i = 0; i <= T; i++)
        tab[i].clear();
}
int main()
{
    int k;
    scanf("%d%d\n", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", A[i] + 1);
    }

    int l = 0, r = 50;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        S = n * 4 + 1;
        T = n * 4 + 2;
        R = 0;
        for (int i = 1; i <= n * 4 + 2; i++)
        {
            tab[i].clear();
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (A[i][j] == 'Y')
                {
                    addedge(i, j + n, 1);
                }
                else
                {
                    addedge(i + 2 * n, j + 3 * n, 1);
                }
            }
        }
        for (int i = 1; i <= n; i++)
        {
            addedge(i, i + 2 * n, k);
        }
        for (int i = 1; i <= n; i++)
        {
            addedge(i + 3 * n, i + n, k);
        }
        for (int i = 1; i <= n; i++)
        {
            addedge(S, i, mid);
        }
        for (int i = n + 1; i <= n * 2; i++)
        {
            addedge(i, T, mid);
        }
        int tmp = DINIC();
        //printf("%d %d %d\n", l, r, tmp);
        if (tmp >= n * mid)
        {
            ans = mid;
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    printf("%d\n", ans);
    system("pause");
    return 0;
}