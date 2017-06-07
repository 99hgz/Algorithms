#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

struct queNode {
  int v, d;
} quenode;
struct vecNode {
  int v, w;
  bool operator<(const vecNode &dd) const { return w > vecNode.w; }
} vecnode;

int main() {
  scanf("%d %d %d %d", &n, &m, &s, &e);
  for (i = 1; i <= m; i++) {
    scanf("%d %d &d", &a, &b, &c);
    vecnode.v = b;
    vecnode.w = c;
    vec[a].push(vecnode);
  }

  quenode.d = 0;
  quenode.n = s;
  priority_queue<queNode> q;
  q.push(quenode);
  queNode tmp;
  while (!q.empty()) {
    tmp = q.top();
    q.pop();
    if (visited[tmp.n])
      continue;
    visited[tmp.n] = true;
    for (i = 0; i < vec[tmp.n].size(); i++) {
      if (d[vec[tmp.n][i].v] > d[tmp.n] + vec[tmp.n][i].w) {
        d[vec[tmp.n][i].v] = d[tmp.n] + vec[tmp.n][i].w;
        quenode.v = d[vec[tmp.n][i].v];
        quenode.d = vec[tmp.n][i].v;
        q.push(quenode);
      }
    }
  }
  printf("%d\n", d[e]);
  system("pause");
  return 0;
}