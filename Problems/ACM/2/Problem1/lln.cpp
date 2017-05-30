/*
 * @Author: lln
 * @Date: 2017-05-30 14:52:02
 * @Last Modified by:   hgz
 * @Last Modified time: 2017-05-30 14:52:02
 */
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>
typedef long long ll;
using namespace std;
vector<ll> vec[1004];
ll n, blo, v[30005], m, bl[30005], lazy[1004];
void reset(ll x) {
  vec[x].clear();

  for (ll i = (x - 1) * blo + 1; i <= min(x * blo, n); i++)
    vec[x].push_back(v[i]);
  sort(vec[x].begin(), vec[x].end());
}
void change(ll l, ll r, ll val) {
  for (ll i = l; i <= min(blo * bl[l], r); i++) {
    v[i] += val;
  }
  reset(bl[l]);
  if (bl[l] != bl[r]) {
    for (ll i = (bl[r] - 1) * blo + 1; i <= r; i++)
      v[i] += val;
    reset(bl[r]);
  }
  for (ll i = bl[l] + 1; i <= bl[r] - 1; i++)
    lazy[i] += val;
}
ll query(ll l, ll r, ll val) {
  ll ans = 0;
  for (ll i = l; i <= min(r, bl[l] * blo); i++)
    if (v[i] + lazy[bl[l]] < val)
      ans++;
  if (bl[l] != bl[r]) {
    for (ll i = blo * (bl[r] - 1) + 1; i <= r; i++)
      if (v[i] + lazy[bl[r]] < val)
        ans++;
  }
  for (ll i = bl[l] + 1; i <= bl[r] - 1; i++)
    ans += lower_bound(vec[i].begin(), vec[i].end(), val - lazy[i]) -
           vec[i].begin();
  return ans;
}
int main() {
  freopen("lln.in", "r", stdin);
  freopen("lln.out", "w", stdout);
  scanf("%lld %lld", &n, &m);
  blo = sqrt(n);
  for (ll i = 1; i <= n; i++) {
    scanf("%lld", &v[i]);
    bl[i] = (i - 1) / blo + 1;
    vec[bl[i]].push_back(v[i]);
  }
  for (ll i = 1; i <= bl[n]; i++)
    sort(vec[i].begin(), vec[i].end());
  char char_[2];
  for (ll i = 1; i <= m; i++) {
    ll x, y, z;
    scanf("%s %lld %lld %lld", char_, &x, &y, &z);
    if (char_[0] == 'C') {
      change(x, y, z);
    } else {
      ll l = 1, r = 1e20, mid, ans;
      while (l <= r) {
        mid = (l + r) >> 1;
        // cout<<l<<' '<<r<<' '<<mid<<endl;
        ll tt = query(x, y, mid);
        if (tt < z) {
          l = mid + 1;
          ans = mid;
        } else {
          r = mid - 1;
        }
      }
      printf("%lld\n", ans);
    }
  }
  fclose(stdin);
  fclose(stdout);
}