/*
 * @Author: hekai
 * @Date: 2017-05-30 14:51:55
 * @Last Modified by:   hgz
 * @Last Modified time: 2017-05-30 14:51:55
 */
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
typedef long long ll;
using namespace std;
ll n, m, a[110000], bl[110000], b[110000], lazy[11000], Min[11000], Max[11000];
void reset(ll i) { sort(b + (i - 1) * m + 1, b + min(i * m + 1, n + 1)); }
void up(ll i) {
  Min[bl[i]] = min(Min[bl[i]], a[i] + lazy[bl[i]]);
  Max[bl[i]] = max(Max[bl[i]], a[i] + lazy[bl[i]]);
}
void change(ll x, ll y, ll d) {
  for (ll i = x; i <= min(bl[x] * m, y); i++)
    a[i] += d, up(i);
  for (ll i = (bl[x] - 1) * m + 1; i <= bl[x] * m; i++)
    b[i] = a[i];
  reset(bl[x]);
  if (bl[x] != bl[y]) {
    for (ll i = (bl[y] - 1) * m + 1; i <= y; i++)
      a[i] += d, up(i);
    for (ll i = (bl[y] - 1) * m + 1; i <= bl[y] * m; i++)
      b[i] = a[i];
    reset(bl[y]);
  }
  for (ll i = bl[x] + 1; i <= bl[y] - 1; i++) {
    lazy[i] += d;
    Max[i] += d;
    Min[i] += d;
  }
}
ll query(ll x, ll y, ll z) {
  ll ans = 0;
  for (ll i = x; i <= min(bl[x] * m, y); i++)
    if (lazy[bl[i]] + a[i] < z)
      ans++;
  if (bl[x] != bl[y]) {
    for (ll i = (bl[y] - 1) * m + 1; i <= y; i++)
      if (lazy[bl[i]] + a[i] < z)
        ans++;
  }
  for (ll i = bl[x] + 1; i <= bl[y] - 1; i++)
    ans += lower_bound(b + (i - 1) * m + 1, b + min(i * m + 1, n + 1),
                       z - lazy[i]) -
           b - (i - 1) * m - 1;
  return ans;
}
ll find(ll x, ll y, ll k) {
  ll l = 1 << 30, r = -(1 << 30);
  for (ll i = x; i <= min(bl[x] * m, y); i++) {
    l = min(l, lazy[bl[i]] + a[i]);
    r = max(r, lazy[bl[i]] + a[i]);
  }
  if (bl[x] != bl[y]) {
    for (ll i = (bl[y] - 1) * m + 1; i <= y; i++) {
      l = min(l, lazy[bl[i]] + a[i]);
      r = max(r, lazy[bl[i]] + a[i]);
    }
  }
  for (ll i = bl[x] + 1; i <= bl[y] - 1; i++) {
    l = min(l, Min[i]);
    r = max(r, Max[i]);
  }
  ll ans;
  while (l <= r) {
    ll mid = (l + r) / 2;
    ll t = query(x, y, mid);
    if (query(x, y, mid) >= k)
      r = mid - 1;
    else
      ans = mid, l = mid + 1;
  }
  return ans;
}
int main() {
  freopen("hk.in", "r", stdin);
  freopen("hk.out", "w", stdout);
  ll q;
  scanf("%lld%lld", &n, &q);
  m = sqrt(n);
  for (ll i = 1; i <= n; i++)
    bl[i] = (i - 1) / m + 1;
  for (ll i = 1; i <= n / m + 1; i++)
    Min[i] = 1 << 30, Max[i] = -(1 << 30);
  for (ll i = 1; i <= n; i++)
    scanf("%lld", &a[i]), up(i);
  for (ll i = 1; i <= n; i++)
    b[i] = a[i];
  for (ll i = 1; i <= n / m; i++)
    reset(i);
  if (n % m != 0)
    reset(n / m + 1);
  for (ll i = 1; i <= n / m + 1; i++)
    lazy[i] = 0;
  for (ll i = 1; i <= q; i++) {
    char s[10];
    scanf("%s", s);
    ll x, y, z;
    scanf("%lld%lld%lld", &x, &y, &z);
    if (s[0] == 'C')
      change(x, y, z);
    else
      printf("%lld\n", find(x, y, z));
  }
  // system("pause");
  return 0;
}
