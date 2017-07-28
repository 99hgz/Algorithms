#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

ll n, m, ans, maxans;
ll a[510][510], f[510][510];

int main() {
  scanf("%lld%lld", &m, &n); // CNM居然是反的
  for (ll i = 1; i <= n; i++) {
    for (ll j = 1; j <= m; j++) {
      scanf("%lld", &a[i][j]);
    }
  }
  for (ll i = 1; i <= m; i++) {
    for (ll j = 1; j <= n; j++) {
      f[i][j] = f[i][j - 1] + a[j][i];
    }
  }
  for (ll i = 1; i <= n; i++) {
    for (ll j = i; j <= n; j++) {
      ans = 0;
      for (ll k = 1; k <= m; k++) {
        ll tmp = f[k][j] - f[k][i - 1];
        ans += tmp;
        if (ans > maxans)
          maxans = ans;
        if (ans < 0)
          ans = 0;
      }
    }
  }
  printf("%lld\n", maxans);
  system("pause");
  return 0;
}
