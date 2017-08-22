#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, k, ans1, max1, f[160][(1 << 17) + 10], a[100010];

int main() {
  scanf("%d%d", &n, &k);
  ans1 = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    ans1 |= a[i];
    max1 = max(max1, a[i]);
  }
  if (n - k > (log(max1) / log(2))) {
    printf("%d\n", ans1);
  } else {
    memset(f, 0x7f7f7f7f, sizeof f);
    f[0][0] = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < 1 << 17; j++) {
        if (f[i][j] != 0x7f7f7f7f) {
          f[i + 1][j] = min(f[i + 1][j], f[i][j]);
          f[i + 1][j | a[i + 1]] = min(f[i + 1][j | a[i + 1]], f[i][j] + 1);
        }
      }
    }
    for (int i = (1 << 17) - 1; i >= 0; i--)
      if (f[n][i] <= n - k) {
        ans1 = i;
        break;
      }
    printf("%d\n", ans1);
  }
  system("pause");
  return 0;
}