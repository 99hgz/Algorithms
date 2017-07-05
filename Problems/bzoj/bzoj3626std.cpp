#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define ll long long
#define inf 1000000000
#define mod 201314
using namespace std;
inline ll read() {
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
int n, m, cnt, place;
int bin[20];
int son[50005], last[50005], fa[50005], belong[50005], pl[50005], deep[50005];
struct edge {
  int to, next;
} e[50005];
struct que {
  int z, ans1, ans2;
} q[50005];
struct data {
  int num, p;
  bool flag;
} a[100005];
struct seg {
  int l, r, sum, tag, size;
} t[11 * 8];
inline bool operator<(data a, data b) { return a.p < b.p; }
inline void insert(int u, int v) {
  e[++cnt].to = v;
  e[cnt].next = last[u];
  last[u] = cnt;
}
void dfs1(int x) {
  son[x] = 1;
  for (int i = last[x]; i; i = e[i].next) {
    if (e[i].to == fa[x])
      continue;
    deep[e[i].to] = deep[x] + 1;
    fa[e[i].to] = x;
    dfs1(e[i].to);
    son[x] += son[e[i].to];
  }
}
void dfs2(int x, int chain) {
  belong[x] = chain;
  pl[x] = ++place;
  int k = n;
  for (int i = last[x]; i; i = e[i].next)
    if (e[i].to != fa[x] && son[e[i].to] > son[k])
      k = e[i].to;
  if (k != n)
    dfs2(k, chain);
  for (int i = last[x]; i; i = e[i].next)
    if (e[i].to != fa[x] && e[i].to != k)
      dfs2(e[i].to, e[i].to);
}
inline void pushdown(int k) {
  if (t[k].l == t[k].r || !t[k].tag)
    return;
  int tag = t[k].tag;
  t[k].tag = 0;
  t[k << 1].sum = t[k << 1].sum + t[k << 1].size * tag;
  t[k << 1 | 1].sum = t[k << 1 | 1].sum + t[k << 1 | 1].size * tag;
  t[k << 1].tag = t[k << 1].tag + tag;
  t[k << 1 | 1].tag = t[k << 1 | 1].tag + tag;
}
void build(int k, int l, int r) {
  t[k].l = l;
  t[k].r = r;
  t[k].size = r - l + 1;
  if (l == r)
    return;
  int mid = (l + r) >> 1;
  build(k << 1, l, mid);
  build(k << 1 | 1, mid + 1, r);
}
void update(int k, int x, int y) {
  pushdown(k);
  int l = t[k].l, r = t[k].r;
  if (l == x && y == r) {
    t[k].tag++;
    t[k].sum += t[k].size;
    return;
  }
  int mid = (l + r) >> 1;
  if (y <= mid)
    update(k << 1, x, y);
  else if (x > mid)
    update(k << 1 | 1, x, y);
  else {
    update(k << 1, x, mid);
    update(k << 1 | 1, mid + 1, y);
  }
  t[k].sum = t[k << 1].sum + t[k << 1 | 1].sum;
}
void solve_update(int x, int f) {
  while (belong[x] != belong[f]) {
    update(1, pl[belong[x]], pl[x]);
    x = fa[belong[x]];
  }
  update(1, pl[f], pl[x]);
}
int query(int k, int x, int y) {
  pushdown(k);
  int l = t[k].l, r = t[k].r;
  if (l == x && y == r)
    return t[k].sum;
  int mid = (l + r) >> 1;
  if (y <= mid)
    return query(k << 1, x, y);
  else if (x > mid)
    return query(k << 1 | 1, x, y);
  else
    return query(k << 1, x, mid) + query(k << 1 | 1, mid + 1, y);
}
int solve_query(int x, int f) {
  int sum = 0;
  while (belong[x] != belong[f]) {
    sum += query(1, pl[belong[x]], pl[x]);
    sum %= mod;
    x = fa[belong[x]];
  }
  sum += query(1, pl[f], pl[x]);
  sum %= mod;
  return sum;
}
int main() {
  // freopen("lca.in","r",stdin);
  // freopen("lca.out","w",stdout);
  bin[0] = 1;
  for (int i = 1; i < 20; i++)
    bin[i] = (bin[i - 1] << 1);
  n = read();
  m = read();
  for (int i = 1; i < n; i++) {
    int x = read();
    insert(x, i);
  }
  int tot = 0;
  for (int i = 1; i <= m; i++) {
    int l = read(), r = read();
    q[i].z = read();
    a[++tot].p = l - 1;
    a[tot].num = i;
    a[tot].flag = 0;
    a[++tot].p = r;
    a[tot].num = i;
    a[tot].flag = 1;
  }
  build(1, 1, n);
  sort(a + 1, a + tot + 1);
  dfs1(0);
  dfs2(0, 0);
  int now = -1;
  for (int i = 1; i <= tot; i++) {
    int t = a[i].num;
    while (now < a[i].p) {
      now++;
      solve_update(now, 0);
      printf("%d %d\n", now, solve_query(q[t].z, 0));
    }

    if (!a[i].flag)
      q[t].ans1 = solve_query(q[t].z, 0);
    else
      q[t].ans2 = solve_query(q[t].z, 0);
  }
  for (int i = 1; i <= m; i++)
    printf("%d\n", (q[i].ans2 - q[i].ans1 + mod) % mod);
  system("pause");
  return 0;
}