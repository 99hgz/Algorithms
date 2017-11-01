#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef unsigned int ll;
ll n, a[400010];
ll son[15000005][2], lmax[400010], rmax, ans;
ll sum, tot = 1;
// bool isend[] ;
void insert(ll x) {
  ll now = 1;
  for (ll i = 32; i >= 1; i--) {
    ll dit = (x >> (i - 1)) & 1;
    if (!son[now][dit]) {
      son[now][dit] = ++tot;
      now = son[now][dit];
    } else
      now = son[now][dit];
  }
}

ll search(ll x) {
  ll now = 1, tonum = 0;
  for (ll i = 32; i >= 1; i--) {
    ll dit = ((x >> (i - 1)) & 1) ^ 1;
    // printf("%lld\n", tonum);
    if (!son[now][dit])
      now = son[now][1 ^ dit], tonum = (tonum << 1) | (1 ^ dit);
    else
      now = son[now][dit], tonum = (tonum << 1) | (dit);
  }
  return tonum;
}

int main() {
  scanf("%d", &n);
  insert(0);
  for (ll i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    sum ^= a[i];
    lmax[i] = max(lmax[i - 1], search(sum) ^ sum);
    // printf("%lld %lld %lld\n", i, lmax[i], search(sum));
    insert(sum);
  }
  memset(son, 0, sizeof son);
  tot = 1;
  insert(0);
  sum = 0;
  for (ll i = n; i >= 2; i--) {
    sum ^= a[i];
    rmax = search(sum) ^ sum;
    ans = max(ans, rmax + lmax[i - 1]);
    // printf("%lld\n", search(sum));
    insert(sum);
  }
  printf("%d\n", ans);
  system("pause");
  return 0;
}