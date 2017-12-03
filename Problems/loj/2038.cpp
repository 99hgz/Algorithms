#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

ll fac[10010], inv[10010], sum[2340][2340];
ll n, k;

const ll MOD = 2333;

ll Lucas(ll n, ll m) {
  if (m > n)
    return 0;
  if (n < MOD && m < MOD)
    return fac[n] * inv[n - m] % MOD * inv[m] % MOD;
  return Lucas(n % MOD, m % MOD) * Lucas(n / MOD, m / MOD) % MOD;
}

void init(ll MOD) {
  fac[0] = 1;
  for (ll i = 1; i <= MOD; i++) {
    fac[i] = fac[i - 1] * i % MOD;
  }
  inv[1] = inv[0] = 1;
  for (ll i = 2; i < MOD; i++) {
    inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
  }
  for (ll i = 1; i < MOD; i++) {
    inv[i] = inv[i] * inv[i - 1] % MOD; //阶乘求逆
  }
  for (ll i = 0; i < MOD; i++) {
    for (ll j = 0; j <= i; j++)
      sum[j][i] = Lucas(i, j);
    for (ll j = 1; j <= MOD; j++)
      sum[j][i] = (sum[j][i] + sum[j - 1][i]) % MOD;
  }
}

ll calc(ll k, ll n) {
  printf("%lld %lld\n", n, k);
  if (k < MOD && n < MOD)
    return sum[k][n];
  ll res = 0;
  if ((k / MOD) >= 1)
    res += calc((k / MOD) - 1, n / MOD) * calc(MOD - 1, n % MOD);
  res %= MOD;
  res += calc(k % MOD, n % MOD) * Lucas(n / MOD, k / MOD);
  res %= MOD;
  return res;
}

int main() {
  init(2333);
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%lld%lld", &n, &k);
    printf("%lld\n", calc(k, n));
  }
  system("pause");
  return 0;
}