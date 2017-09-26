#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;
int n;
struct Edge
{
    int u, v, cap;
    Edge() {}
    Edge(int u, int v, int cap) : u(u), v(v), cap(cap) {}
} es[1000 * 1000];
int R, S, T;
int inf = 0x3f3f3f3f;
vector<int> tab[1000];
int dis[1000];
int current[1000];
int r, c, d, A[30][30];
char STR[30];
void addedge(int u, int v, int cap)
{
    //printf("%d %d %d\n", u, v, cap);
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
double get_dis(int i, int j, int i2, int j2)
{
    return (abs(i - i2) + abs(j - j2));
}
void init()
{
    R = 0;
    for (int i = 0; i <= T; i++)
        tab[i].clear();
}

int calc(int i, int j, int cases)
{
    return ((i - 1) * c + j) * 2 + cases;
}

int main()
{
    S = 1;
    scanf("%d%d%d", &r, &c, &d);
    T = calc(r + 1, 1, 1);
    for (int i = 1; i <= r; i++)
    {
        scanf("%s", STR + 1);
        for (int j = 1; j <= c; j++)
        {
            //scanf("%1d", &A[i][j]);
            addedge(calc(i, j, 1), calc(i, j, 2), STR[j] - '0');
        }
    }
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c; j++)
        {
            if (i <= d || (r - i + 1) <= d || j <= d || (c - j + 1) <= d)
                addedge(calc(i, j, 2), T, inf);
            for (int k = 1; k <= r; k++)
                for (int k2 = 1; k2 <= c; k2++)
                {
                    if (i == k && j == k2)
                        continue;
                    if (get_dis(i, j, k, k2) <= d)
                        addedge(calc(i, j, 2), calc(k, k2, 1), inf);
                }
        }
    int total = 0;
    for (int i = 1; i <= r; i++)
    {
        scanf("%s", STR + 1);
        for (int j = 1; j <= c; j++)
        {
            if (STR[j] == 'L')
            {
                total += 1;
                addedge(S, calc(i, j, 1), 1);
            }
        }
    }
    printf("%d\n", total - DINIC());
    system("pause");
    return 0;
}