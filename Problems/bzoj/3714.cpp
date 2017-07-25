#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <climits>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;

#define N 2000 + 10

using namespace std;
int n, m;
struct node {
  int v, w;
  bool operator<(const node &dd) const { return w > dd.w; }
};
vector<node> q[N];
bool vis[N];
LL ans;
int well;

void queue_prim() {
  priority_queue<node> que;
  que.push((node){0, 0});
  ans = 0;
  memset(vis, false, sizeof(vis));
  int edge = n;
  node cur;
  while (!que.empty()) {
    cur = que.top();
    que.pop();

    if (vis[cur.v])
      continue;
    // printf("%d \n", cur.v);
    ans = ans + cur.w;
    vis[cur.v] = true;
    // printf("%d\n", cur.v);
    for (int i = 0; i < q[cur.v].size(); i++) {
      if (vis[q[cur.v][i].v] == false) {
        que.push(q[cur.v][i]);
        // vis[q[cur.v][i].v] = true;
      }
    }
  }
}

int main() {
  scanf("%d", &n);
  int i, j;
  int tmp;
  int u, v, w;
  for (i = 0; i <= n; i++)
    q[i].clear();
  for (i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      scanf("%d", &tmp);
      q[i - 1].push_back((node){j, tmp});
      q[j].push_back((node){i - 1, tmp});
    }
  }
  queue_prim();
  printf("%lld\n", ans);
  system("pause");
  return 0;
}