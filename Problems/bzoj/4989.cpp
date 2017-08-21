#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll size = 100010;
ll tree[size];
ll a[size], b[size], A[size], B[size], n, move1, move2, ans, nowcross;

ll lowbit(ll x) { return x & -x; }
ll sum(ll end) {
  ll ans = 0;
  while (end > 0) {
    ans += tree[end];
    end -= lowbit(end);
  }
  return ans;
}
void update(ll pos, ll num) {
  while (pos < size) {
    tree[pos] += num;
    pos += lowbit(pos);
  }
}
int main() {
  scanf("%lld", &n);
  for (ll i = 1; i <= n; i++) {
    scanf("%lld", &a[i]);
    A[a[i]] = i;
  }
  for (ll i = 1; i <= n; i++) {
    scanf("%lld", &b[i]);
    B[b[i]] = i;
  }
  for (ll i = n; i >= 1; i--) {
    nowcross += sum(A[b[i]]);
    update(A[b[i]], 1);
  }
  ans = move1 = move2 = nowcross;
  for (ll i = 1; i <= n; i++) {
    move1 = move1 - A[b[i]] + n - A[b[i]] + 1;
    ans = min(ans, move1);
  }
  for (ll i = 1; i <= n; i++) {
    move2 = move2 - B[a[i]] + n - B[a[i]] + 1;
    ans = min(ans, move2);
  }
  printf("%lld\n", ans);
  system("pause");
  return 0;
}