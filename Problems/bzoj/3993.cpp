#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;
int n;
struct Edge {
  int u, v, cap;
  Edge() {}
  Edge(int u, int v, int cap) : u(u), v(v), cap(cap) {}
} es[510 * 510 * 10];
int R, S, T;
int inf = 0x3f3f3f3f;
vector<int> tab[510 * 510];
int dis[510 * 510];
int current[510 * 510];
int r, c, d, B[510][510];
char STR[30];
int C[510];
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

int calc(int i, int j) { return (i * n + j); }

int main() {
  S = 1;
  scanf("%d", &n);
  T = calc(n + 1, 1);
  int total = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      scanf("%d", &B[i][j]);
      addedge(S, calc(i, j), B[i][j]);
      addedge(calc(i, j), i, inf);
      addedge(calc(i, j), j, inf);
      total += B[i][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &C[i]);
    addedge(i, T, C[i]);
  }
  printf("%d\n", total - DINIC());
  system("pause");
}