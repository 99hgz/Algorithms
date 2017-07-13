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

int n, m, s, e, b, w, h, d0, d1, d2, d3, tot;
int c[4];
bool visited[10010];
int d[10010];
int a[32][32];
vector<vecNode> vec[10010];
priority_queue<queNode, vector<queNode>, cmp> q;

int calc_V(int i, int j, int fx) { return (((i - 1) * w + j - 1) * 4 + fx); }

void addedge(int u, int vi, int vj, int fx, int turn) {
  // if ((a[vi][vj] == 4) && ((vi != h) || (vj != w)))
  //  return;
  if ((vi > 0) && (vi <= h) && (vj > 0) && (vj <= w)) {
    int d = calc_V(vi, vj, fx);
    // printf("addedge:%d %d %d %d\n", u, d, vi, vj, fx);
    vec[u].push_back((vecNode){
        d, ((a[vi][vj] == turn) || ((vi == h) && (vj == w))) ? 0 : c[turn]});
  }
}

int dijkstra() {
  for (int i = 0; i <= n; i++) {
    d[i] = 2147483647;
    visited[i] = false;
  }

  quenode.d = a[1][1] == 3 ? 0 : c[3];
  quenode.n = 0;
  d[0] = a[1][1] == 3 ? 0 : c[3];
  q.push(quenode);
  quenode.d = a[1][1] == 0 ? 0 : c[0];
  quenode.n = 1;
  d[1] = a[1][1] == 0 ? 0 : c[0];
  q.push(quenode);
  quenode.d = a[1][1] == 1 ? 0 : c[1];
  quenode.n = 2;
  d[2] = a[1][1] == 1 ? 0 : c[1];
  q.push(quenode);
  quenode.d = a[1][1] == 2 ? 0 : c[2];
  quenode.n = 3;
  d[3] = a[1][1] == 2 ? 0 : c[2];
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
  scanf("%d%d", &w, &h);
  n = w * h * 4;
  tot = 0;
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      scanf("%d", &a[i][j]);
    }
  }
  scanf("%d%d%d%d", &c[0], &c[1], &c[2], &c[3]);
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      d0 = calc_V(i, j, 0);
      d1 = calc_V(i, j, 1);
      d2 = calc_V(i, j, 2);
      d3 = calc_V(i, j, 3);
      {
        addedge(d0, i - 1, j, 0, 0);
        addedge(d0, i - 1, j, 1, 1);
        addedge(d0, i - 1, j, 2, 2);
        addedge(d0, i - 1, j, 3, 3);

        addedge(d1, i, j + 1, 0, 3);
        addedge(d1, i, j + 1, 1, 0);
        addedge(d1, i, j + 1, 2, 1);
        addedge(d1, i, j + 1, 3, 2);

        addedge(d2, i + 1, j, 0, 2);
        addedge(d2, i + 1, j, 1, 3);
        addedge(d2, i + 1, j, 2, 0);
        addedge(d2, i + 1, j, 3, 1);

        addedge(d3, i, j - 1, 0, 1);
        addedge(d3, i, j - 1, 1, 2);
        addedge(d3, i, j - 1, 2, 3);
        addedge(d3, i, j - 1, 3, 0);
      }
    }
  }
  dijkstra();
  printf("%d\n", min(min(d[calc_V(h, w, 0)], d[calc_V(h, w, 1)]),
                     min(d[calc_V(h, w, 2)], d[calc_V(h, w, 3)])));
  system("pause");
  return 0;
}
