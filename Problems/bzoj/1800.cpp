#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, sum, ans, a[30], pre[30];
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    pre[i] = pre[i - 1] + a[i];
    sum += a[i];
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      for (int k = j + 1; k <= n; k++) {
        for (int l = k + 1; l <= n; l++) {
          if ((pre[j] - pre[i]) == (pre[l] - pre[k]) &&
              (pre[k] - pre[j]) == (sum - pre[l] + pre[i]))
            ans++;
        }
      }
    }
  }
  printf("%d\n", ans);
  system("pause");
  return 0;
}