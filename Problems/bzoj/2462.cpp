#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef unsigned int ll;

ll n, m, a, b, f[1010][1010], pow1[1010], pow2[1010], HASH, Q, c[1010][1010];
bool hash[100000000];
ll BASE1 = 101;
ll BASE2 = 121;
ll P = 99999971;
int main() {
  scanf("%d%d%d%d", &m, &n, &a, &b);
  for (ll i = 1; i <= m; i++) {
    for (ll j = 1; j <= n; j++) {
      scanf("%1d", &f[i][j]);
    }
  }
  for (ll i = 1; i <= m; i++)
    for (ll j = 1; j <= n; j++)
      f[i][j] += f[i - 1][j] * BASE1;
  for (ll i = 1; i <= m; i++)
    for (ll j = 1; j <= n; j++)
      f[i][j] += f[i][j - 1] * BASE2;
  pow1[0] = 1;
  pow2[0] = 1;
  for (ll i = 1; i <= m; i++)
    pow1[i] = pow1[i - 1] * BASE1;
  for (ll i = 1; i <= n; i++)
    pow2[i] = pow2[i - 1] * BASE2;
  for (ll i = a; i <= m; i++)
    for (ll j = b; j <= n; j++) {
      HASH = f[i][j];
      HASH -= f[i - a][j] * pow1[a];
      HASH -= f[i][j - b] * pow2[b];
      HASH += f[i - a][j - b] * pow1[a] * pow2[b];
      HASH %= P;
      hash[HASH] = true;
    }
  scanf("%d", &Q);
  while (Q--) {
    for (ll i = 1; i <= a; i++) {
      for (ll j = 1; j <= b; j++) {
        scanf("%1d", &c[i][j]);
      }
    }
    for (ll i = 1; i <= a; i++) {
      for (ll j = 1; j <= b; j++) {
        c[i][j] += c[i - 1][j] * BASE1;
      }
    }
    for (ll i = 1; i <= a; i++) {
      for (ll j = 1; j <= b; j++) {
        c[i][j] += c[i][j - 1] * BASE2;
      }
    }
    printf("%d\n", (hash[c[a][b] % P]) ? 1 : 0);
  }
  system("pause");
  return 0;
}