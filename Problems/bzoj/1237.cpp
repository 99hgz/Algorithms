#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

ll abs1(ll a, ll b) {
  if (a == b)
    return 21000000000000000ll;
  else
    return abs(a - b);
}

ll n, f[100005], a[100005], b[100005];

int main() {
  scanf("%lld", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%lld%lld", &a[i], &b[i]);
    f[i] = 21000000000000000ll;
  }
  sort(a + 1, a + n + 1);
  sort(b + 1, b + 1 + n);
  if (n == 1 & a[1] == b[1]) {
    printf("-1\n");
    return 0;
  }

  f[0] = 0;
  f[1] = abs1(a[1], b[1]);
  f[2] = min(f[1] + abs1(a[2], b[2]), abs1(a[1], b[2]) + abs1(a[2], b[1]));
  for (int i = 3; i <= n; i++) {
    f[i] = min(f[i - 1] + abs1(a[i], b[i]), f[i]);
    f[i] = min(f[i], f[i - 2] + abs1(a[i - 1], b[i]) + abs1(a[i], b[i - 1]));
    f[i] = min(f[i], f[i - 3] + abs1(a[i], b[i - 1]) +
                         abs1(a[i - 1], b[i - 2]) + abs1(a[i - 2], b[i]));
    f[i] = min(f[i], f[i - 3] + abs1(a[i], b[i - 2]) + abs1(a[i - 1], b[i]) +
                         abs1(a[i - 2], b[i - 1]));
    f[i] = min(f[i], f[i - 3] + abs1(a[i], b[i - 2]) +
                         abs1(a[i - 1], b[i - 1]) + abs1(a[i - 2], b[i]));
  }
  printf("%lld\n", f[n]);
  system("pause");
  return 0;
}