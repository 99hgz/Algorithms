#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, a[1000001], c[1000001];
ll sum, avg, ans;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    sum += a[i];
  }
  avg = sum / n;
  for (int i = 1; i <= n; i++) {
    c[i] = c[i - 1] + a[i] - avg;
  }
  nth_element(c + 1, c + (n >> 1) + 1, c + 1 + n);
  int mid = c[(n >> 1) + 1];
  for (int i = 1; i <= n; i++) {
    ans += abs(c[i] - mid);
  }
  printf("%lld\n", ans);
  system("pause");
  return 0;
}