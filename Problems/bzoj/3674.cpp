#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

int bh, n, tn, m, l, r, G, a, b, cases;
int root[200010];
int Hash[200010];
struct NODe {
  int lson, rson, val;
} tree[200010 * 50];

int build(int l, int r) {
  bh++;
  int tbh = bh;
  if (l == r) {
    tree[bh].val = 0;
    return bh;
  }
  tree[tbh].lson = build(l, (l + r) >> 1);
  tree[tbh].rson = build(((l + r) >> 1) + 1, r);
  return tbh;
}

int update(int i, int l, int r, int old, int val) {
  if (l == r) {
    bh++;
    tree[bh].val = val;
    return bh;
  }
  int tbh;
  int mid = (l + r) >> 1;
  if (i > mid) {
    bh++;
    tbh = bh;
    tree[bh].lson = tree[old].lson;
    tree[tbh].rson = update(i, mid + 1, r, tree[old].rson, val);
  } else {
    bh++;
    tbh = bh;
    tree[bh].rson = tree[old].rson;
    tree[tbh].lson = update(i, l, mid, tree[old].lson, val);
  }
  // printf("%d %d %d %d", i, l, r, old);
  // printf(" change->%d\n", tbh);
  // printf("lson=%d rson=%d\n", tree[tbh].lson, tree[tbh].rson);
  return tbh;
}

int query(int rt, int wz, int l, int r) {
  if (l == r) {
    return tree[rt].val;
  }
  int mid = (l + r) / 2;
  if (wz <= mid) {
    return query(tree[rt].lson, wz, l, mid);
  } else {
    return query(tree[rt].rson, wz, mid + 1, r);
  }
}

int get_father(int rt, int x, int i) {
  int tmp = query(rt, x, 1, n);
  if (tmp == 0)
    return x;
  int fa = get_father(rt, tmp, i);
  root[i] = update(x, 1, n, root[i], fa);
  return fa;
}

int main() {
  scanf("%d%d", &n, &m);
  root[0] = build(1, n);
  int lastans = 0;
  for (int i = 1; i <= m; i++) {
    scanf("%d", &cases);
    if (cases == 1) {
      scanf("%d%d", &a, &b);
      // a = a ^ lastans;
      // b = b ^ lastans;
      root[i] = root[i - 1];
      int fax = get_father(root[i], a, i);
      int fay = get_father(root[i], b, i);
      if (fax != fay) {
        root[i] = update(fax, 1, n, root[i], fay);
      }
    } else if (cases == 2) {
      scanf("%d", &a);
      // a = a ^ lastans;
      root[i] = root[a];
    } else {
      scanf("%d%d", &a, &b);
      // a = a ^ lastans;
      // b = b ^ lastans;
      root[i] = root[i - 1];
      int fax = get_father(root[i], a, i);
      int fay = get_father(root[i], b, i);
      // printf("%d %d %d %d\n", a, fax, b, fay);
      if (fax == fay) {
        lastans = 1;
      } else {
        lastans = 0;
      }
      printf("%d\n", lastans);
    }
  }
  system("pause");
  return 0;
}