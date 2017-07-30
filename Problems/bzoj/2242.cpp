#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <map>
#include <algorithm>
using namespace std;
typedef long long ll;
int T, K;
ll y, z, p;
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

void solve1() {
  while (T--) {
    scanf("%lld%lld%lld", &y, &z, &p);
    printf("%lld\n", power2(y, z, p));
  }
}

ll exgcd(ll a, ll b, ll &x, ll &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  ll r = exgcd(b, a % b, x, y);
  ll t = x;
  x = y;
  y = t - a / b * y;
  return r;
}

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

void solve2() {
  while (T--) {
    scanf("%lld%lld%lld", &y, &z, &p);
    p = -p;
    int t = gcd(y, p);
    if (z % t) {
      printf("Orz, I cannot find x!\n");
      continue;
    }
    y /= t;
    z /= t;
    p /= t;
    ll a, b;
    exgcd(y, p, a, b);
    a = a * z % p;
    while (a < 0)
      a += p;
    printf("%lld\n", a);
  }
}
map<int, int> mp;
void solve3() {
  while (T--) {
    scanf("%lld%lld%lld", &y, &z, &p);
    y %= p;
    if (!y && !z) {
      printf("1\n");
      continue;
    }
    if (!y) {
      printf("Orz, I cannot find x!\n");
      continue;
    }
    mp.clear();
    ll m = ceil(sqrt(p)), t = 1;
    mp[1] = m + 1;
    for (ll i = 1; i < m; i++) {
      t = t * y % p;
      if (!mp[t])
        mp[t] = i;
    }
    ll tmp = power2(y, p - m - 1, p), ine = 1;
    bool flag = false;
    for (ll k = 0; k < m; k++) {
      int i = mp[z * ine % p];
      if (i) {
        if (i == m + 1)
          i = 0;
        printf("%lld\n", k * m + i);
        flag = true;
        break;
      }
      ine = ine * tmp % p;
    }
    if (!flag)
      printf("Orz, I cannot find x!\n");
  }
}

int main() {

  scanf("%d%d", &T, &K);
  if (K == 1)
    solve1();
  else if (K == 2)
    solve2();
  else if (K == 3)
    solve3();
  system("pause");
  return 0;
}