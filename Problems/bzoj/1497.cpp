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
<<<<<<< HEAD
struct Edge {
  int u, v, cap;
  Edge() {}
  Edge(int u, int v, int cap) : u(u), v(v), cap(cap) {}
=======
struct Edge
{
    int u, v, cap;
    Edge() {}
    Edge(int u, int v, int cap) : u(u), v(v), cap(cap) {}
>>>>>>> b9cbcc628fdfdab79f07283f0996a0cf45478968
} es[500000];
int R, S, T;
int a, b, c, m;
vector<int> tab[60000]; // 边集
int dis[60000], p[5010];
int current[60000];
<<<<<<< HEAD
struct Node {
  int x, y, c;
} points[60000];

void addedge(int u, int v, int cap) {
  tab[u].push_back(R);
  es[R++] = Edge(u, v, cap);
  tab[v].push_back(R);
  es[R++] = Edge(v, u, 0);
}
int BFS() {
  queue<int> q;
  q.push(S);
  memset(dis, 0x3f, sizeof(dis));
  dis[S] = 0;
  while (!q.empty()) {
    int h = q.front();
    q.pop();
    for (int i = 0; i < tab[h].size(); i++) {
      Edge &e = es[tab[h][i]];
      if (e.cap > 0 && dis[e.v] == 0x3f3f3f3f) {
        dis[e.v] = dis[h] + 1;
        q.push(e.v);
      }
    }
  }
  return dis[T] < 0x3f3f3f3f;
}
int dinic(int x, int maxflow) {
  if (x == T)
    return maxflow;
  for (int i = current[x]; i < tab[x].size(); i++) {
    current[x] = i;
    Edge &e = es[tab[x][i]];
    if (dis[e.v] == dis[x] + 1 && e.cap > 0) {
      int flow = dinic(e.v, min(maxflow, e.cap));
      if (flow) {
        e.cap -= flow;
        es[tab[x][i] ^ 1].cap += flow;
        return flow;
      }
    }
  }
  return 0;
}
int DINIC() {
  int ans = 0;

  while (BFS()) {
    int flow;
    memset(current, 0, sizeof(current));
    while (flow = dinic(S, 0x3f3f3f3f))
      ans += flow;
  }
  return ans;
}

void init() {
  R = 0;
  for (int i = 0; i <= T; i++)
    tab[i].clear();
}

int main() {
  int total = 0;
  scanf("%d%d", &n, &m);
  T = n + m + 1;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &p[i]);
    addedge(i, T, p[i]);
  }
  S = 0;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d%d", &a, &b, &c);
    addedge(i + n, a, 0x3f3f33ff);
    addedge(i + n, b, 0x3f3f33ff);
    addedge(S, i + n, c);
    total += c;
  }

  printf("%d\n", total - DINIC());
  system("pause");
  return 0;
=======
struct Node
{
    int x, y, c;
} points[60000];

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

void init()
{
    R = 0;
    for (int i = 0; i <= T; i++)
        tab[i].clear();
}

int main()
{
    int total = 0;
    scanf("%d%d", &n, &m);
    T = n + m + 1;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
        addedge(i, T, p[i]);
    }
    S = 0;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        addedge(i + n, a, 0x3f3f33ff);
        addedge(i + n, b, 0x3f3f33ff);
        addedge(S, i + n, c);
        total += c;
    }

    printf("%d\n", total - DINIC());
    //system("pause");
    return 0;
>>>>>>> b9cbcc628fdfdab79f07283f0996a0cf45478968
}