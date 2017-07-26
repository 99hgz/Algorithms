#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, max1;
int ans[1000005], cnt[1000005];
int a[1000005];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    cnt[a[i]]++;
    if (a[i] > max1)
      max1 = a[i];
  }
  for (int i = 1; i <= max1; i++) {
    if (cnt[i] != 0) {
      for (int j = 1; j <= max1; j++) {
        if (i * j > max1)
          break;
        ans[i * j] += cnt[i];
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    printf("%d\n", ans[a[i]] - 1);
  }
  system("pause");
  return 0;
}