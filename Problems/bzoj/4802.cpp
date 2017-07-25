#include <cstdio>
#include <cstdlib>
#include <algorithm>
typedef long long ll;
ll n, ans;

ll euler(ll n) {
  ll res = n, a = n;
  for (int i = 2; i * i <= a; i++) {
    if (a % i == 0) {
      res = res / i * (i - 1);
      while (a % i == 0)
        a /= i;
    }
  }
  if (a > 1)
    res = res / a * (a - 1);
  return res;
}

int main() {
  ll t;
  scanf("%lld", &t);
  printf("%lld\n", euler(t));
  system("pause");
}
