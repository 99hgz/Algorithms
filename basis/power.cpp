/*
 * @key word: 快速幕,阶乘,power
 * @已测试:FZU-1752
 * @Author: hgz
 * @Date: 2017-04-22 11:17:30
 * @Last Modified by: hgz
 * @Last Modified time: 2017-04-22 12:41:47
 */

#include <cstdio>
#include <iostream>
typedef long long ll;
using namespace std;

ll power(ll a, ll b, ll p) {
  // a^b mod p
  //辣鸡😓
  ll ans = 1;
  while (b > 0) {
    if (b & 1)
      ans = (ans * a) % p;
    a = (a * a) % p;
    b >>= 1;
  }
  return ans;
}

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

// test
int main() {
  ll a, b, c;
  while (~scanf("%lld%lld%lld", &a, &b, &c)) {
    printf("%lld\n", power2(a, b, c));
  }
  //system("pause");
  return 0;
}
