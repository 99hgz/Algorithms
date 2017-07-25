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

int n, m, s, a, b, c, D;
bool visited[30];
ll d[30];
vector<vecNode> vec[30];
priority_queue<queNode, vector<queNode>, cmp> q;
ll ans[110];
ll f[110][110];
int K, e;
bool block[30], flag[110][110];
void addedge(int u, int v, int w) {
  vecnode.v = v;
  vecnode.w = w;
  vec[u].push_back(vecnode);
}

int dijkstra(int s) {
  for (int i = 1; i <= m; i++) {
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
      if ((!block[v]) && (!visited[v]) && (d[v] > d[u] + vec[u][i].w)) {
        d[v] = d[u] + vec[u][i].w;
        quenode.d = d[v];
        quenode.n = v;
        q.push(quenode);
      }
    }
  }
}

int main() {
  scanf("%d%d%d%d", &n, &m, &K, &e);
  for (int i = 1; i <= e; i++) {
    scanf("%d%d%d", &a, &b, &c);
    addedge(a, b, c);
    addedge(b, a, c);
  }
  scanf("%d", &D);
  for (int i = 1; i <= D; i++) {
    scanf("%d%d%d", &a, &b, &c);
    for (int i = b; i <= c; i++) {
      flag[i][a] = true;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      memset(block, 0, sizeof block);
      for (int i1 = i; i1 <= j; i1++) {
        for (int j1 = 1; j1 <= m; j1++) {
          if (flag[i1][j1])
            block[j1] = true;
        }
      }
      dijkstra(1);
      f[i][j] = d[m];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      if (f[i][j] != 2147483647)
        f[i][j] *= (j - i + 1);
    }
  }
  memset(ans, 0x7f7f7f7f, sizeof ans);
  for (int i = 1; i <= n; i++) {
    ans[i] = f[1][i];
  }
  for (int i = 2; i <= n; i++) {
    for (int j = 1; j <= i - 1; j++) {
      ans[i] = min(ans[i], ans[j] + f[j + 1][i] + K);
    }
  }
  printf("%lld\n", ans[n]);
  system("pause");
  return 0;
}