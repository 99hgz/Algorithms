#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

ll read() {
  ll x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
ll n, blo;
ll v[100010], bl[100010], atag[100010];
void add(ll a, ll b, ll c) {
  for (ll i = a; i <= min(bl[a] * blo, b); i++)
    v[i] += c;
  if (bl[a] != bl[b])
    for (ll i = (bl[b] - 1) * blo + 1; i <= b; i++)
      v[i] += c;
  for (ll i = bl[a] + 1; i <= bl[b] - 1; i++)
    atag[i] += c;
}
int main() {
  n = read();
  blo = sqrt(n);
  for (ll i = 1; i <= n; i++)
    v[i] = read();
  for (ll i = 1; i <= n; i++)
    bl[i] = (i - 1) / blo + 1;
  ll m = read();
  for (ll i = 1; i <= m; i++) {
    ll f = read();
    if (f == 1) {
      ll a = read(), b = read(), c = read();
      add(a, b, c);
    }
    if (f == 2) {
      ll b = read();
      printf("%lld\n", v[b] + atag[bl[b]]);
    }
  }
  // system("pause");
  return 0;
}