#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cmath>
#define N 100003
#define LL long long
using namespace std;
int n, m;
char s[N];
struct data {
  int a[N], p, height[N];
  int xx[N], yy[N], *x, *y, sa[N], rank[N], st[20][N], L[N], v[N];
  int cmp(int i, int j, int k) {
    return y[i] == y[j] &&
           (i + k > n ? -1 : y[i + k]) == (j + k > n ? -1 : y[j + k]);
  }
  void get_sa() {
    int m = 300;
    x = xx;
    y = yy;
    for (int i = 1; i <= n; i++)
      v[x[i] = a[i]]++;
    for (int i = 1; i <= m; i++)
      v[i] += v[i - 1];
    for (int i = n; i >= 1; i--)
      sa[v[x[i]]--] = i;
    for (int k = 1; k <= n; k <<= 1) {
      p = 0;
      for (int i = n - k + 1; i <= n; i++)
        y[++p] = i;
      for (int i = 1; i <= n; i++)
        if (sa[i] > k)
          y[++p] = sa[i] - k;
      for (int i = 1; i <= m; i++)
        v[i] = 0;
      for (int i = 1; i <= n; i++)
        v[x[y[i]]]++;
      for (int i = 1; i <= m; i++)
        v[i] += v[i - 1];
      for (int i = n; i >= 1; i--)
        sa[v[x[y[i]]]--] = y[i];
      swap(x, y);
      p = 2;
      x[sa[1]] = 1;
      for (int i = 2; i <= n; i++)
        x[sa[i]] = cmp(sa[i], sa[i - 1], k) ? p - 1 : p++;
      if (p > n)
        break;
      m = p + 1;
    }
    for (int i = 1; i <= n; i++)
      rank[sa[i]] = i;
    p = 0;
    for (int i = 1; i <= n; i++) {
      if (rank[i] == 1)
        continue;
      int j = sa[rank[i] - 1];
      while (j + p <= n && i + p <= n && a[j + p] == a[i + p])
        p++;
      height[rank[i]] = p;
      p = max(p - 1, 0);
    }
    for (int i = 1; i <= n; i++)
      st[0][i] = height[i];
    for (int j = 1; j <= 17; j++)
      for (int i = 1; i <= n; i++)
        if (i + (1 << j) - 1 <= n)
          st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << j - 1)]);
    int j = 0;
    for (int i = 1; i <= n; i++) {
      if ((1 << j + 1) <= i)
        j++;
      L[i] = j;
    }
  }
  int calc(int x, int y) {
    if (x > y)
      swap(x, y);
    int k = L[y - x];
    x++;
    return min(st[k][x], st[k][y - (1 << k) + 1]);
  }
} lcp, lcs;
int main() {
  /*freopen("a.in", "r", stdin);
  freopen("my.out", "w", stdout);*/
  scanf("%d", &m);
  scanf("%s", s + 1);
  n = strlen(s + 1);
  for (int i = 1; i <= n; i++)
    lcp.a[i] = s[i] + 1;
  for (int i = 1; i <= n; i++)
    lcs.a[i] = s[n - i + 1] + 1;
  lcp.get_sa();
  lcs.get_sa();
  LL ans = 0;
  for (int i = 1; i + i + m <= n; i++) {
    for (int l = 1; l <= n; l += i) {
      int r = l + i + m;
      printf("%d\n", r);
      int t = min(i, lcp.calc(lcp.rank[l], lcp.rank[r]));
      int t1 = min(i, lcs.calc(lcs.rank[n - l + 1], lcs.rank[n - r + 1]));
      printf("%d %d %d %d\n", i, l, t, t1);
      int len = t + t1;
      if (t && t1)
        len--;
      if (len >= i)
        ans += (LL)(len - i + 1);
    }
  }
  printf("%lld\n", ans);
  system("pause");
}
