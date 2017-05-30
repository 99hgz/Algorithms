#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
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
ll n, blo;
ll v[100005], bl[100005], tag[100005];
void reset(ll x) {
  if (tag[x] == -1)
    return;
  for (ll i = (x - 1) * blo + 1; i <= blo * x; i++)
    v[i] = tag[x];
  tag[x] = -1;
}
ll solve(ll a, ll b, ll c) {
  ll ans = 0;
  reset(bl[a]);
  for (ll i = a; i <= min(bl[a] * blo, b); i++)
    if (v[i] != c)
      v[i] = c;
    else
      ans++;
  if (bl[a] != bl[b]) {
    reset(bl[b]);
    for (ll i = (bl[b] - 1) * blo + 1; i <= b; i++)
      if (v[i] != c)
        v[i] = c;
      else
        ans++;
  }
  for (ll i = bl[a] + 1; i <= bl[b] - 1; i++)
    if (tag[i] != -1) {
      if (tag[i] != c)
        tag[i] = c;
      else
        ans += blo;
    } else {
      for (ll j = (i - 1) * blo + 1; j <= i * blo; j++)
        if (v[j] != c)
          v[j] = c;
        else
          ans++;
      tag[i] = c;
    }
  return ans;
}
int main() {
  freopen("lln.in", "r", stdin);
  freopen("lln.out", "w", stdout);
  memset(tag, -1, sizeof(tag));
  n = read();
  blo = sqrt(n);
  for (ll i = 1; i <= n; i++)
    v[i] = read();
  for (ll i = 1; i <= n; i++)
    bl[i] = (i - 1) / blo + 1;
  for (ll i = 1; i <= n; i++) {
    ll a = read(), b = read(), c = read();
    printf("%lld\n", solve(a, b, c));
  }
  // system("pause");
  return 0;
}