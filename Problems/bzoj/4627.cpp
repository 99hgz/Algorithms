#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

ll n, L, R, a[100010], pre[100010], Hash[100010];
ll ans;
ll tree[100010];

void add(ll x) {
  for (; x <= n; x += x & -x)
    tree[x]++;
}

ll sum(ll x) {
  ll res = 0;
  for (; x; x -= x & -x)
    res += tree[x];
  return res;
}

int main() {
  scanf("%lld%lld%lld", &n, &L, &R);
  for (ll i = 1; i <= n; i++) {
    scanf("%lld", &a[i]);
    Hash[i] = pre[i] = pre[i - 1] + a[i];
  }
  sort(Hash + 1, Hash + 1 + n);
  for (ll i = 1; i <= n; i++) {
    ll l = lower_bound(Hash + 1, Hash + 1 + n, L + pre[i - 1]) - Hash;
    ll r = upper_bound(Hash + 1, Hash + 1 + n, R + pre[i - 1]) - Hash;
    ans += r - sum(r - 1) + sum(l - 1) - l;
    add(lower_bound(Hash + 1, Hash + 1 + n, pre[i]) - Hash);
  }
  printf("%lld\n", ans);
  // system("pause");
  return 0;
}