#include <cstdio>
#include <cmath>
#include <algorithm>
#define fo(i, a, b) for (int i = a; i <= b; i++)
using namespace std;
const int maxn = 300000 + 10;
int fa[maxn][30], d[maxn], f[maxn], a[maxn];
int i, j, k, l, t, n, m, tot, ans, x, y;
bool czy;
int lllg;
int get(int x, int y) {
  int j = lllg;
  while (j >= 0) {
    if (d[fa[x][j]] >= y)
      x = fa[x][j];
    j--;
  }
  return x;
}

int getans(int x, int y) {
  fa[++tot][0] = x;
  d[tot] = d[x] + 1;
  a[tot] = y;
  fo(j, 1, lllg) fa[tot][j] = fa[fa[tot][j - 1]][j - 1];
  if (d[tot] > 1) {
    int j = fa[tot][0];
    while (j) {
      k = get(tot, d[f[j]] + 1);
      if (a[k] == a[tot])
        break;
      k = 0;
      if (2 * d[f[j]] <= d[j])
        j = f[j];
      else
        j = get(tot, d[j] % (d[j] - d[f[j]]));
    }
    if (!k)
      if (a[get(tot, 1)] == a[tot])
        k = a[get(tot, 1)];
    f[tot] = k;
  }
  ans = d[tot] - d[f[tot]];
  return ans;
}

int main() {

  scanf("%d", &n);
  lllg = floor(log(n * 26) / log(2));

  m = 26;
  int tmp;
  int stack[10], per[10], lastcz[10];
  int i = 1;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &per[i]);
    stack[i] = 1;
  }
  lastcz[0] = 0;
  while (i <= n) {
    bool flag = false;
    for (int j = stack[i]; j <= 26; j++) {
      tmp = getans(lastcz[i - 1], j);
      if (tmp == per[i]) {
        lastcz[i] = tot;
        stack[i] = j + 1;
        i++;
        flag = true;
        break;
      }
    }
    if (!flag) {
      i--;
      stack[i] = 1;
    }
  }
  for (int i = 1; i <= n; i++) {
    printf("%c", stack[i] - 2 + 'a');
  }
  system("pause");
}