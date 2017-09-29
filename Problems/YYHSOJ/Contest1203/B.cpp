#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;

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
ll n, blo, m;
ll v[30010], bl[30010], atag[30010];
vector<ll> ve[505];
void reset(ll x) {
  ve[x].clear();
  for (ll i = (x - 1) * blo + 1; i <= min(x * blo, n); i++)
    ve[x].push_back(v[i]);
  sort(ve[x].begin(), ve[x].end());
}
void add(ll a, ll b, ll c) {
  for (ll i = a; i <= min(bl[a] * blo, b); i++)
    v[i] += c;
  reset(bl[a]);
  if (bl[a] != bl[b]) {
    for (ll i = (bl[b] - 1) * blo + 1; i <= b; i++)
      v[i] += c;
    reset(bl[b]);
  }
  for (ll i = bl[a] + 1; i <= bl[b] - 1; i++)
    atag[i] += c;
}
ll query(ll a, ll b, ll c) {
  ll ans = 0;
  for (ll i = a; i <= min(bl[a] * blo, b); i++)
    if (v[i] + atag[bl[a]] < c)
      ans++;
  if (bl[a] != bl[b])
    for (ll i = (bl[b] - 1) * blo + 1; i <= b; i++)
      if (v[i] + atag[bl[b]] < c)
        ans++;
  for (ll i = bl[a] + 1; i <= bl[b] - 1; i++) {
    ll x = c - atag[i];
    ans += lower_bound(ve[i].begin(), ve[i].end(), x) - ve[i].begin();
  }
  return ans;
}
int main() {
  n = read();
  m = read();
  blo = sqrt(n);
  for (ll i = 1; i <= n; i++)
    v[i] = read();
  for (ll i = 1; i <= n; i++) {
    bl[i] = (i - 1) / blo + 1;
    ve[bl[i]].push_back(v[i]);
  }
  for (ll i = 1; i <= bl[n]; i++)
    sort(ve[i].begin(), ve[i].end());
  for (ll i = 1; i <= m; i++) {
    char f = getchar();
    ll a = read(), b = read(), c = read();
    if (f == 'C')
      add(a, b, c);
    if (f == 'Q')
      printf("%lld\n", query(a, b, c));
  }
  // system("pause");
  return 0;
}