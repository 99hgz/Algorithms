#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

struct ITEMS {
  int id, val, time, flag;
} intitem[100010], b[100010];

int BIT[100010], ans[100010], a[100010], q[100010], pos[100010], n, m, k;
int ANS[100010];
bool cmpid(ITEMS a, ITEMS b) { return a.id < b.id; }
bool cmpid2(ITEMS a, ITEMS b) { return a.id > b.id; }
bool cmpval(ITEMS a, ITEMS b) { return a.val < b.val; }

int lowbit(int a) { return a & (-a); }
int add(int a, int v) {
  for (; a <= n; a += lowbit(a))
    BIT[a] += v;
}
int sum(int a) {
  if (a > n)
    a = n;
  int res = 0;
  for (; a > 0; a -= lowbit(a)) {
    res += BIT[a];
  }
  return res;
}

void solve(int l, int r) {
  if (l >= r)
    return;
  int mid = (l + r) >> 1;
  solve(l, mid);
  solve(mid + 1, r);
  int cnt = 0;
  for (int i = l; i <= mid; i++) {
    b[++cnt] = intitem[i];
    b[cnt].flag = 0; // left
  }
  for (int i = mid + 1; i <= r; i++) {
    b[++cnt] = intitem[i];
    b[cnt].flag = 1; // right
  }
  sort(b + 1, b + cnt + 1, cmpval);

  for (int i = cnt; i >= 1; i--) {
    if (b[i].flag)
      ans[b[i].id] += sum(b[i].time - k - 1) + sum(n + 1) - sum(b[i].time + k);
    else
      add(b[i].time, 1);
  }
  for (int i = 1; i <= cnt; i++) {
    if (b[i].flag == 0)
      add(b[i].time, -1);
  }
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    intitem[a[i]].id = i;
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    intitem[a[i]].val = i;
    intitem[a[i]].time = a[i];
  }

  sort(intitem + 1, intitem + n + 1, cmpid);
  solve(1, n);
  ll TOTAL = 0;

  for (int i = 1; i <= n; i++) {
    TOTAL += ans[i];
  }
  printf("%lld\n", TOTAL);

  system("pause");
  return 0;
}