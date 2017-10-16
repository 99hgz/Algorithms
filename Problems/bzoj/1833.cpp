#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
 
ll f[100], k, bit[100], n, ans, last[100], bin[100];
 
ll dfs(ll tjnum, ll pos, bool limit) {
  // printf("%lld %lld %d\n", cd, pos, limit);
  if (pos == 0)
    return 1;
  if (!limit && f[pos] != -1)
    return f[pos];
  ll res = 0;
  ll maxx = (limit ? bit[pos] : 9);
  for (ll i = 0; i <= maxx; i++) {
    res += dfs(tjnum, pos - 1, limit && i == bit[pos]);
    if (i == tjnum) {
      res += ((limit && i == bit[pos]) ? last[pos - 1] : bin[pos - 1]);
    }
    // res %= (ll)10000007;
  }
  if (!limit)
    f[pos] = res;
  return res;
}
 
int main() {
  scanf("%lld", &n);
  ll nn = n;
  k = 0;
  bin[0] = 1;
  while (n) {
    bit[++k] = n % (ll)10;
    n /= (ll)10;
    last[k] = last[k - 1] * 10 + bit[k];
    bin[k] = bin[k - 1] * 10;
  }
  ans = 1;
 
  for (ll i = 0; i <= 9; i++) {
    memset(f, -1, sizeof f);
    printf("%lld\n", dfs(i, k, true));
  }
  // printf("%lld\n", ans);
  system("pause");
  return 0;
}