#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n;
struct POINT {
  double x, y, w;
} ans, a[10100];

double dis(POINT a, POINT b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%lf%lf%lf", &a[i].x, &a[i].y, &a[i].w);
    ans.x += a[i].x;
    ans.y += a[i].y;
  }
  ans.x /= n;
  ans.y /= n;
  double T = 1000;
  while (T > 1e-8) {
    POINT tmp;
    tmp.x = 0;
    tmp.y = 0;
    for (int i = 1; i <= n; i++) {
      tmp.x += (a[i].x - ans.x) * a[i].w / dis(a[i], ans);
      tmp.y += (a[i].y - ans.y) * a[i].w / dis(a[i], ans);
    }
    ans.x += tmp.x * T;
    ans.y += tmp.y * T;
    if (T > 0.5)
      T *= 0.5;
    else
      T *= 0.97;
  }
  printf("%.3lf %.3lf\n", ans.x, ans.y);
  system("pause");
  return 0;
}