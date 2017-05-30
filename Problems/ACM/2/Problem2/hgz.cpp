#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
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
int n, blo;
int v[100005], bl[100005], tag[100005];
void reset(int x) {
  if (tag[x] == -1)
    return;
  for (int i = (x - 1) * blo + 1; i <= blo * x; i++)
    v[i] = tag[x];
  tag[x] = -1;
}
int solve(int a, int b, int c) {
  int ans = 0;
  reset(bl[a]);
  for (int i = a; i <= min(bl[a] * blo, b); i++)
    if (v[i] != c)
      v[i] = c;
    else
      ans++;
  if (bl[a] != bl[b]) {
    reset(bl[b]);
    for (int i = (bl[b] - 1) * blo + 1; i <= b; i++)
      if (v[i] != c)
        v[i] = c;
      else
        ans++;
  }
  for (int i = bl[a] + 1; i <= bl[b] - 1; i++)
    if (tag[i] != -1) {
      if (tag[i] != c)
        tag[i] = c;
      else
        ans += blo;
    } else {
      for (int j = (i - 1) * blo + 1; j <= i * blo; j++)
        if (v[j] != c)
          v[j] = c;
        else
          ans++;
      tag[i] = c;
    }
  return ans;
}
int main() {
  freopen("hgz.in", "r", stdin);
  freopen("hgz.out", "w", stdout);
  memset(tag, -1, sizeof(tag));
  n = read();
  blo = sqrt(n);
  for (int i = 1; i <= n; i++)
    v[i] = read();
  for (int i = 1; i <= n; i++)
    bl[i] = (i - 1) / blo + 1;
  for (int i = 1; i <= n; i++) {
    int a = read(), b = read(), c = read();
    printf("%d\n", solve(a, b, c));
  }
  system("pause");
  return 0;
}