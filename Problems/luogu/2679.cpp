#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
char a[1010], b[1010];
int f[2][1010][210][2];
int gd;
int n, m, k, prematched;
int main() {
  int mo = 1000000007;
  scanf("%d %d %d", &n, &m, &k);
  scanf("%s", a + 1);
  scanf("%s", b + 1);
  gd = 0;
  for (int i = 1; i <= n; i++) {
    gd = 1 - gd;
    memset(f[gd], 0, sizeof(f[gd]));

    f[gd][1][1][0] = prematched;
    if (a[i] == b[1]) {
      f[gd][1][1][1] = 1;
      prematched++;
    }
    for (int j = 2; j <= m; j++) {
      for (int t = 1; t <= k; t++) {
        if (a[i] == b[j]) {
          f[gd][j][t][1] =
              ((f[1 - gd][j - 1][t - 1][1] + f[1 - gd][j - 1][t - 1][0]) % mo +
               f[1 - gd][j - 1][t][1]) %
              mo;
        }
        f[gd][j][t][0] = (f[1 - gd][j][t][0] + f[1 - gd][j][t][1]) % mo;
      }
    }
  }
  printf("%d\n", (f[gd][m][k][1] + f[gd][m][k][0]) % mo);
  // system("pause");
  return 0;
}