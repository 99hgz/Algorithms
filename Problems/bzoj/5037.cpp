#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;
int n;
double d;
struct Edge
{
    int u, v, cap;
    Edge() {}
    Edge(int u, int v, int cap) : u(u), v(v), cap(cap) {}
} es[510 * 510];
int R, S, T;
vector<int> tab[510]; // 边集
int dis[510];
int current[510];
struct Node
{
    int x, y, r, s;
} points[510];

void addedge(int u, int v, int cap)
{
    tab[u].push_back(R);
    es[R++] = Edge(u, v, cap);
    tab[v].push_back(R);
    es[R++] = Edge(v, u, 0);
}
int BFS()
{
    queue<int> q;
    q.push(S);
    memset(dis, 0x3f, sizeof(dis));
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
    return dis[T] < 0x3f3f3f3f;
}
int dinic(int x, int maxflow)
{
    if (x == T)
        return maxflow;
    for (int i = current[x]; i < tab[x].size(); i++)
    {
        current[x] = i;
        Edge &e = es[tab[x][i]];
        if (dis[e.v] == dis[x] + 1 && e.cap > 0)
        {
            int flow = dinic(e.v, min(maxflow, e.cap));
            if (flow)
            {
                e.cap -= flow;
                es[tab[x][i] ^ 1].cap += flow;
                return flow;
            }
        }
    }
    return 0;
}
int DINIC()
{
    int ans = 0;

    while (BFS())
    {
        int flow;
        memset(current, 0, sizeof(current));
        while (flow = dinic(S, 0x3f3f3f3f))
            ans += flow;
    }
    return ans;
}
int get_dis(int i, int j)
{
    return (points[i].x - points[j].x) * (points[i].x - points[j].x) + (points[i].y - points[j].y) * (points[i].y - points[j].y);
}
void init()
{
    R = 0;
    for (int i = 0; i <= T; i++)
        tab[i].clear();
}

int main()
{
    int total = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d%d%d", &points[i].x, &points[i].y, &points[i].r, &points[i].s);
        if (points[i].s > 0)
        {
            total += points[i].s;
            addedge(0, i, points[i].s);
        }
        else if (points[i].s < 0)
        {
            addedge(i, n + 1, -points[i].s);
        }
    }
    S = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
                continue;
            if (get_dis(i, j) <= points[i].r * points[i].r)
            {
                addedge(i, j, 0x3f3f3f3f);
            }
        }
    }
    T = n + 1;
    printf("%d\n", total - DINIC());
    system("pause");
    return 0;
}