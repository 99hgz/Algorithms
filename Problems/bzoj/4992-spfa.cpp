#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
int n, m, S, tot, Next[120000], head[41000], tree[120000], val[120000],
    dis[41000], a[110][110], flag[41000], x[1100000];
bool visit[41000];
int cost, cx[5] = {0, 1, -1, 0, 0}, cy[5] = {0, 0, 0, 1, -1};
bool reg = false, regg = false;
void add(int x, int y, int z) {
  tot++;
  Next[tot] = head[x];
  head[x] = tot;
  tree[tot] = y;
  val[tot] = z;
}
int spfa(int s) {
  for (int i = 1; i <= n * n * 3; i++)
    dis[i] = 1 << 30, visit[i] = false, flag[i] = 0;
  int t = 0, w = 1;
  x[1] = s;
  dis[s] = 0;
  visit[s] = true;
  flag[s] = 1;
  while (t < w) {
    t++;
    int u = x[t];
    visit[u] = false;
    if (dis[s] < 0) {
      reg = true;
      return 0;
    }
    for (int i = head[u]; i; i = Next[i]) {
      int v = tree[i];
      if (dis[u] + val[i] < dis[v]) {
        dis[v] = dis[u] + val[i];
        if (!visit[v]) {
          x[++w] = v, visit[v] = true;
          flag[v]++;
          if (flag[v] > n) {
            reg = true;
            return 0;
          }
        }
      }
    }
  }
}

int get_id(int x, int y, int k) { return ((x - 1) * n + y - 1) * 3 + k; }

int main() {
  scanf("%d%d", &n, &cost);
  tot = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      scanf("%d", &a[i][j]);
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      for (int k = 1; k <= 3; k++) {
        for (int fx = 1; fx <= 4; fx++) {
          int gx = i + cx[fx], gy = j + cy[fx];
          if (gx < 1 || gy < 1 || gx > n || gy > n)
            continue;
          if (k == 2)
            add(get_id(i, j, k), get_id(gx, gy, k + 1), cost + a[gx][gy]);
          else
            add(get_id(i, j, k), get_id(gx, gy, k == 3 ? 1 : 2), cost);
        }
      }
    }
  }
  spfa(get_id(1, 1, 3));
  printf("%d\n", min(dis[get_id(n, n, 1)],
                     min(dis[get_id(n, n, 2)], dis[get_id(n, n, 3)])));
  system("pause");
  return 0;
}
