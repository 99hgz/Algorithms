#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <queue>

using namespace std;
typedef long long ll;

struct queNode {
  int n, d;
} quenode;
struct vecNode {
  int v, w;
} vecnode;
struct cmp {
  bool operator()(queNode a, queNode b) { return a.d > b.d; }
};

int n, m, s, e, a, b, c, x, S, T, w, y;
bool visited[1100100];
int d[1100100];
vector<vecNode> vec[1100100];
priority_queue<queNode, vector<queNode>, cmp> q;

void addedge(int u, int v, int w) {
  printf("addedge:%d %d\n", u, v);
  vecnode.v = v;
  vecnode.w = w;
  vec[u].push_back(vecnode);
  vecnode.v = u;
  vecnode.w = w;
  vec[v].push_back(vecnode);
}

int dijkstra(int s) {
  for (int i = 1; i <= n; i++) {
    d[i] = 2147483647;
    visited[i] = false;
  }
  quenode.d = 0;
  quenode.n = s;
  d[s] = 0;
  q.push(quenode);
  queNode tmp;
  while (!q.empty()) {
    tmp = q.top();
    q.pop();
    if (visited[tmp.n])
      continue;
    visited[tmp.n] = true;
    for (int i = 0; i < vec[tmp.n].size(); i++) {
      int u = tmp.n, v = vec[tmp.n][i].v;
      if ((!visited[v]) && (d[v] > d[u] + vec[u][i].w)) {
        d[v] = d[u] + vec[u][i].w;
        quenode.d = d[v];
        quenode.n = v;
        q.push(quenode);
      }
    }
  }
}

int main() {

  while (~scanf("%d%d", &n, &m)) {
    S = n * m * 4 + 1;
    T = n * m * 4 + 2;
    for (int i = 1; i <= T; i++) {
      vec[i].clear();
    }
    while (!q.empty()) {

      q.pop();
    }
    for (int i = 1; i <= n + 1; i++) {
      if (i == 1) {
        for (int j = 1; j <= m; j++) {
          scanf("%d", &w);
          addedge(T, (i - 1) * m * 4 + j * 4 - 2, w);
        }
      } else if (i > n) {
        for (int j = 1; j <= m; j++) {
          scanf("%d", &w);
          addedge((i - 2) * m * 4 + j * 4, S, w);
        }
      } else {
        for (int j = 1; j <= m; j++) {
          scanf("%d", &w);
          addedge((i - 1) * m * 4 + j * 4 - 2, (i - 2) * m * 4 + j * 4, w);
        }
      }
    }

    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m + 1; j++) {
        scanf("%d", &w);
        if (j == 1) {
          addedge((i - 1) * m * 4 + j * 4 - 3, S, w);
        } else if (j > m) {
          addedge((i - 1) * m * 4 + j * 4 - 5, T, w);
        } else {
          addedge((i - 1) * m * 4 + j * 4 - 5, (i - 1) * m * 4 + j * 4 - 3, w);
        }
      }
    }

    for (int i = 1; i <= 2 * n; i++) {
      for (int j = 1; j <= 2 * m; j++) {
        scanf("%d", &w);
        if ((j % 2 == 1) && (i % 2 == 1))
          addedge(((i - 1) / 2) * m * 4 + ((j + 1) / 2) * 4 - 3,
                  ((i - 1) / 2) * m * 4 + ((j + 1) / 2) * 4 - 2, w);
        else if ((j % 2 == 0) && (i % 2 == 1))
          addedge(((i - 1) / 2) * m * 4 + ((j + 1) / 2) * 4 - 1,
                  ((i - 1) / 2) * m * 4 + ((j + 1) / 2) * 4 - 2, w);
        else if ((j % 2 == 1) && (i % 2 == 0))
          addedge(((i - 1) / 2) * m * 4 + ((j + 1) / 2) * 4 - 3,
                  ((i - 1) / 2) * m * 4 + ((j + 1) / 2) * 4, w);
        else
          addedge(((i - 1) / 2) * m * 4 + ((j + 1) / 2) * 4 - 1,
                  ((i - 1) / 2) * m * 4 + ((j + 1) / 2) * 4, w);
      }
    }

    n = T;
    dijkstra(S);
    printf("%d\n", d[T]);
  }
  system("pause");
  return 0;
}