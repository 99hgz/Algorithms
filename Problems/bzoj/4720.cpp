#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, m, v, e;
int c[2011], d[2011], dis[2011][2011], u, tv, t;
double ans, k[2011], f[2011][2011][2];

int main() {
  scanf("%d%d%d%d", &n, &m, &v, &e);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &c[i]);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &d[i]);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%lf", &k[i]);
  }
  for (int i = 1; i <= v; i++) {
    for (int j = 1; j <= v; j++) {
      if (i == j)
        dis[i][j] = 0;
      else
        dis[i][j] = 0x7ffff;
    }
  }
  for (int i = 1; i <= e; i++) {
    scanf("%d%d%d", &u, &tv, &t);
    dis[u][tv] = min(dis[u][tv], t);
    dis[tv][u] = min(dis[tv][u], t);
  }
  for (int k = 1; k <= v; k++) {
    for (int i = 1; i <= v; i++) {
      for (int j = 1; j <= v; j++) {
        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      f[i][j][0] = f[i][j][1] = 0x7ffff;
    }
  }
  f[1][0][0] = 0;
  f[1][1][1] = 0;
  for (int i = 2; i <= n; i++) {
    for (int j = 0; j <= min(i, m); j++) {
      f[i][j][0] = min(f[i - 1][j][0] + dis[c[i]][c[i - 1]],
                       f[i - 1][j][1] + dis[c[i]][c[i - 1]] * (1.0 - k[i - 1]) +
                           dis[c[i]][d[i - 1]] * (k[i - 1]));
      if (j > 0)
        f[i][j][1] =
            min(f[i - 1][j - 1][0] + dis[c[i - 1]][d[i]] * k[i] +
                    dis[c[i - 1]][c[i]] * (1.0 - k[i]),
                f[i - 1][j - 1][1] +
                    dis[c[i - 1]][c[i]] * (1.0 - k[i]) * (1.0 - k[i - 1]) +
                    dis[c[i - 1]][d[i]] * (k[i]) * (1.0 - k[i - 1]) +
                    dis[d[i - 1]][c[i]] * (1.0 - k[i]) * (k[i - 1]) +
                    dis[d[i - 1]][d[i]] * (k[i]) * (k[i - 1]));
    }
  }
  double ans = 1e30;
  for (int i = 0; i <= m; i++) {
    ans = min(ans, min(f[n][i][0], f[n][i][1]));
  }
  printf("%.2lf\n", ans);
  system("pause");
  return 0;
}