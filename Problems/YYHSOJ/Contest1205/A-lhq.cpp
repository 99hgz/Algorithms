/*
 * @Author: lhq
 * @Date: 2017-07-09 20:57:23
 * @Last Modified by:   hgz
 * @Last Modified time: 2017-07-09 20:57:23
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
using namespace std;
const int MAXM = 101000, MAXN = 26 * 26 + 10;
int Head[MAXN], Next[MAXM], To[MAXM], cnt[MAXN];
double Key[MAXM], dis[MAXN];
bool inq[MAXN];
char str[1010];
int n, tot;

int getnum(int x, int y) { return (x - 97) * 26 + y - 97; }
void add(int x, int y, int w) {
  tot++;
  Next[tot] = Head[x];
  Head[x] = tot;
  To[tot] = y;
  Key[tot] = (double)w;
}
void ReadInfo() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    int m, x, y;
    scanf("%s", str + 1);
    m = strlen(str + 1);
    x = getnum(str[1], str[2]);
    y = getnum(str[m - 1], str[m]);
    add(x, y, m);
  }
}
bool spfa(int s, double avg) // true means there exist a positive weight circle;
{
  memset(inq, false, sizeof(inq));
  memset(dis, 0xc2, sizeof(dis));
  queue<int> Q;
  dis[s] = 0;
  inq[s] = true;
  cnt[s] = 1;
  Q.push(s);
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    inq[u] = false;
    for (int i = Head[u]; i; i = Next[i]) {
      int v = To[i];
      double w = Key[i] - avg;
      if (dis[u] + w > dis[v]) {
        dis[v] = dis[u] + w;
        if (!inq[v]) {
          inq[v] = true;
          Q.push(v);
          cnt[v]++;
          if (cnt[v] == 50)
            return true;
        }
      }
    }
  }
  return false;
}
bool positive_circle(
    double avg) // true means there exist a positive weight circle;
{
  memset(cnt, 0, sizeof(cnt));
  for (int i = 1; i < MAXN; i++)
    if (!cnt[i] && spfa(i, avg))
      return true;
  return false;
}
void solve() {
  double x = 0, y = 1001, mid;
  while (y - x > 1e-4) {
    mid = (x + y) / 2;
    if (positive_circle(mid))
      x = mid;
    else
      y = mid;
  }
  if (x < 0.1) {
    printf("No solution.\n");
  } else {
    printf("%.2lf\n", x);
  }
}

int main() {
  ReadInfo();
  solve();
  return 0;
}
