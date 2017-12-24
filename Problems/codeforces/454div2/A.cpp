#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int v1, v2, v3, v4, flag, a[5];

bool check(int i) { return i >= v4 && 2 * v4 >= i; }

bool check2(int i) { return i >= v4 && 2 * v4 < i; }

int main() {
  scanf("%d%d%d%d", &v1, &v2, &v3, &v4);
  for (int i = v3; i <= v3 * 2; i++)
    if (check(i)) {
      a[3] = i;
      flag = true;
      break;
    }
  if (!flag) {
    printf("-1\n");
    return 0;
  }
  flag = 0;
  for (int i = max(v2, a[3] + 1); i <= v2 * 2; i++)
    if (check2(i)) {
      a[2] = i;
      flag = true;
      break;
    }
  if (!flag) {
    printf("-1\n");
    return 0;
  }
  flag = 0;
  for (int i = max(v1, a[2] + 1); i <= v1 * 2; i++)
    if (check2(i)) {
      a[1] = i;
      flag = true;
      break;
    }
  if (!flag) {
    printf("-1\n");
    return 0;
  }
  for (int i = 1; i <= 3; i++) {
    printf("%d\n", a[i]);
  }
  // system("pause");
  return 0;
}