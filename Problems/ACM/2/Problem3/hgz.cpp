#include <map>
#include <set>
#include <cmath>
#include <stack>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define mod 10007
#define pi acos(-1)
#define inf 0x7fffffff
#define ll long long
using namespace std;
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
ll n, blo, id;
ll v[50005], bl[50005];
ll f[505][505];
map<ll, ll> mp;
ll val[50005], cnt[50005];
vector<ll> ve[50005];
void pre(ll x) {
  memset(cnt, 0, sizeof(cnt));
  ll mx = 0, ans = 0;
  for (ll i = (x - 1) * blo + 1; i <= n; i++) {
    cnt[v[i]]++;
    ll t = bl[i];
    if (cnt[v[i]] > mx || (cnt[v[i]] == mx && val[v[i]] < val[ans]))
      ans = v[i], mx = cnt[v[i]];
    f[x][t] = ans;
  }
}
ll query(ll l, ll r, ll x) {
  ll t = upper_bound(ve[x].begin(), ve[x].end(), r) -
         lower_bound(ve[x].begin(), ve[x].end(), l);
  return t;
}
ll query(ll a, ll b) {
  ll ans, mx;
  ans = f[bl[a] + 1][bl[b] - 1];
  mx = query(a, b, ans);
  for (ll i = a; i <= min(bl[a] * blo, b); i++) {
    ll t = query(a, b, v[i]);
    if (t > mx || (t == mx && val[v[i]] < val[ans]))
      ans = v[i], mx = t;
  }
  if (bl[a] != bl[b])
    for (ll i = (bl[b] - 1) * blo + 1; i <= b; i++) {
      ll t = query(a, b, v[i]);
      if (t > mx || (t == mx && val[v[i]] < val[ans]))
        ans = v[i], mx = t;
    }
  return ans;
}
int main() {
  freopen("lln.in", "r", stdin);
  freopen("lln.out", "w", stdout);
  n = read();
  blo = sqrt(n);
  for (ll i = 1; i <= n; i++) {
    v[i] = read();
    if (!mp[v[i]]) {
      mp[v[i]] = ++id;
      val[id] = v[i];
    }
    v[i] = mp[v[i]];
    ve[v[i]].push_back(i);
  }
  for (ll i = 1; i <= n; i++)
    bl[i] = (i - 1) / blo + 1;
  for (ll i = 1; i <= bl[n]; i++)
    pre(i);
  for (ll i = 1; i <= n; i++) {
    ll a = read(), b = read();
    if (a > b)
      swap(a, b);
    printf("%lld\n", val[query(a, b)]);
  }
  // system("pause");
  return 0;
}