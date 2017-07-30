#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <climits>
using namespace std;
typedef long long ll;
ll inf = 922337203000000000;
ll n, m, r[260], p[260], change[260][260], f[260][260][260];

ll dfs(ll x, ll cost, ll color) {
  // printf("%d %d %d\n", x, cost, color);
  if (x > n)
    return 0;
  if ((n - x + 1) < cost)
    return inf;
  if (f[x][cost][color] != -1) {
    return f[x][cost][color];
  }
  ll val = inf;
  if (color != -1)
    val = min(val, dfs(x + 1, cost, color) + change[x][color]);
  // printf("%d %d %d\n", x, cost, val);
  if (cost > 0) {
    for (ll i = color + 1; i <= 255; i++) {
      val = min(val, dfs(x + 1, cost - 1, i) + change[x][i]);
    }
  }
  f[x][cost][color] = val;
  return val;
}
main() {
  // printf("%lld\n", inf);
  memset(f, -1, sizeof f);
  scanf("%lld%lld", &n, &m);
  for (ll i = 1; i <= n; i++) {
    scanf("%lld%lld", &r[i], &p[i]);
  }
  for (ll i = 1; i <= n; i++) {
    for (ll j = 0; j <= 255; j++) {
      change[i][j] = (r[i] - j) * (r[i] - j) * p[i];
    }
  }
  printf("%lld\n", dfs(1, m, -1));
  system("pause");
  return 0;
}