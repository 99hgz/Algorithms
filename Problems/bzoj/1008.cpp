#include <cstdio>
#include <cstdlib>
#define mod 100003
#define ll long long
using namespace std;
ll m, n;
ll mod_mul(ll a, ll b, ll p) {
  //来自http://blog.csdn.net/mengxiang000000/article/details/52073217
  a %= p;
  b %= p;
  return (a * b - (ll)(a / (long double)p * b + 1e-8) * p + p) % p;
}

ll power2(ll a, ll b, ll p) {
  // a^b mod p
  a %= p;
  ll ans = 1;
  while (b) {
    if (b % 2 == 1) {
      ans = mod_mul(ans, a, p);
      b -= 1;
    }
    a = mod_mul(a, a, p);
    b /= 2;
  }
  return ans;
}
int main() {
  scanf("%lld%lld", &m, &n);
  long long ans = power2(m, n, 100003);
  ans = ans - m * power2(m - 1, n - 1, 100003) % mod;
  if (ans < 0)
    ans += mod;
  printf("%lld", ans);
  return 0;
}