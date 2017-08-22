#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, a[100], ans;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    for (int j = 1; j <= i - 1; j++) {
      if (a[i] > a[j])
        ans++;
    }
  }
  if (ans % 2) {
    printf("Q\n");
  } else {
    printf("T\n");
  }
  system("pause");
  return 0;
}