#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;
int n;
<<<<<<< HEAD
double d;
struct Edge {
  int u, v, cap;
  Edge() {}
  Edge(int u, int v, int cap) : u(u), v(v), cap(cap) {}
} es[209 * 209], es1[209 * 209];
int R, S, T;
vector<int> tab[209]; // 边集
int dis[209];
int current[209];
int x[109], y[109], n1[109], m[109];
void addedge(int u, int v, int cap) {
  tab[u].push_back(R);
  es1[R++] = Edge(u, v, cap); // 正向边
  tab[v].push_back(R);
  es1[R++] = Edge(v, u, 0); // 反向边容量为0
  // 正向边下标通过异或就得到反向边下标, 2 ^ 1 == 3 ; 3 ^ 1 == 2
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
  return dis[T] < 0x3f3f3f3f; // 返回是否能够到达汇点
}
int dinic(int x, int maxflow) {
  if (x == T)
    return maxflow;
  // i = current[x] 当前弧优化
  for (int i = current[x]; i < tab[x].size(); i++) {
    current[x] = i;
    Edge &e = es[tab[x][i]];
    if (dis[e.v] == dis[x] + 1 && e.cap > 0) {
      int flow = dinic(e.v, min(maxflow, e.cap));
      if (flow) {
        e.cap -= flow;                 // 正向边流量降低
        es[tab[x][i] ^ 1].cap += flow; // 反向边流量增加
        return flow;
      }
    }
  }
  return 0; // 找不到增广路 退出
}
int DINIC() {
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
double pos(int i, int j) {
  return sqrt((double)(x[i] - x[j]) * (double)(x[i] - x[j]) +
              (double)(y[i] - y[j]) * (double)(y[i] - y[j]));
}
void init() {
  R = 0;
  for (int i = 0; i <= T; i++)
    tab[i].clear();
}
int main() {
  scanf("%d%lf", &n, &d);
  R = 0;
  S = n + 1;
  int total = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%d%d%d%d", &x[i], &y[i], &n1[i], &m[i]);
    total += n1[i];
    addedge(S, i, n1[i]);
    addedge(i, n + i + 1, m[i]);
    for (int j = 1; j <= i - 1; j++) {
      // printf("%.4lf\n", pos(i, j));
      if (pos(i, j) <= d) {
        addedge(i + n + 1, j, 0x3f3f3f3f);
        addedge(j + n + 1, i, 0x3f3f3f3f);
      }
    }
  }
  bool flag = false;
  vector<int> ANS;
  for (int i = 1; i <= n; i++) {
    T = i;
    memcpy(es, es1, sizeof es);
    // printf("%d \n", DINIC());
    if (DINIC() >= total)
      ANS.push_back(i - 1), flag = true;
  }
  if (flag) {
    for (int i = 0; i < ANS.size() - 1; i++) {
      printf("%d ", ANS[i]);
    }
    printf("%d\n", ANS[ANS.size() - 1]);
  }
  if (!flag)
    printf("-1\n");
  system("pause");
  return 0;
=======
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
>>>>>>> 12d7aaa0a736d72ebd6c5434b2714963cf105792
}