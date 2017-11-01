#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <vector>
#include <cmath>
#define maxn 800000
using namespace std;
typedef long long ll;

int n, m, len, k;
int range_min[maxn];
set<int> st[maxn];
int inf = 0x3f3f3f3f;
int res, c[maxn];
<<<<<<< HEAD
struct Node {
=======
struct Node
{
>>>>>>> 12d7aaa0a736d72ebd6c5434b2714963cf105792
  int l, r;
} que[maxn];
vector<int> qry[maxn];
int ans[maxn];

<<<<<<< HEAD
void build(int id, int l, int r) {
  // printf("%d %d %d\n", id, l, r);
  range_min[id] = inf;
  for (int i = l; i <= r; i++) {
=======
void build(int id, int l, int r)
{
  // printf("%d %d %d\n", id, l, r);
  range_min[id] = inf;
  for (int i = l; i <= r; i++)
  {
>>>>>>> 12d7aaa0a736d72ebd6c5434b2714963cf105792
    st[id].insert(c[i]);
  }
  if (l == r)
    return;
  int mid = (l + r) >> 1;
  build(id * 2, l, mid);
  build(id * 2 + 1, mid + 1, r);
}

<<<<<<< HEAD
int query(int id, int L, int R, int l, int r) {
=======
int query(int id, int L, int R, int l, int r)
{
>>>>>>> 12d7aaa0a736d72ebd6c5434b2714963cf105792

  if (l <= L && R <= r)
    return range_min[id];
  int mid = (L + R) >> 1;
  int res = inf;
  if (l <= mid)
    res = min(res, query(id * 2, L, mid, l, r));
  if (r > mid)
    res = min(res, query(id * 2 + 1, mid + 1, R, l, r));
  return res;
}

<<<<<<< HEAD
void push_up(int id) {
  range_min[id] = min(range_min[id * 2], range_min[id * 2 + 1]);
}

void modify(int id, int L, int R, int l, int r, int x, int &res) {

  set<int>::iterator right = st[id].lower_bound(x), left;
  if (right != st[id].begin()) {
=======
void push_up(int id)
{
  range_min[id] = min(range_min[id * 2], range_min[id * 2 + 1]);
}

void modify(int id, int L, int R, int l, int r, int x, int &res)
{
  set<int>::iterator right = st[id].lower_bound(x), left;
  if (right != st[id].begin())
  {
>>>>>>> 12d7aaa0a736d72ebd6c5434b2714963cf105792
    left = right;
    left--;
  }
  if ((right == st[id].end() || x + res <= *right) &&
<<<<<<< HEAD
      ((right == st[id].begin()) || (*left + res <= x))) {
    res = min(res, query(id, L, R, l, r));
    return;
  }
  if (L == R) {
=======
      ((right == st[id].begin()) || (*left + res <= x)))
  {
    res = min(res, query(id, L, R, l, r));
    return;
  }
  if (L == R)
  {
>>>>>>> 12d7aaa0a736d72ebd6c5434b2714963cf105792
    int tmp = abs(x - c[L]);
    range_min[id] = min(range_min[id], tmp == 0 ? range_min[id] : tmp);
    res = min(res, range_min[id]);
    return;
  }
  int mid = (L + R) >> 1;
  if (l <= mid)
    modify(id * 2, L, mid, l, r, x, res);
  if (r > mid)
    modify(id * 2 + 1, mid + 1, R, l, r, x, res);
  push_up(id);
}

<<<<<<< HEAD
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &c[i]);
  }
  for (int i = 1; i <= m; i++) {
=======
int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++)
  {
    scanf("%d", &c[i]);
  }
  for (int i = 1; i <= m; i++)
  {
>>>>>>> 12d7aaa0a736d72ebd6c5434b2714963cf105792
    scanf("%d%d", &que[i].l, &que[i].r);
    qry[que[i].l].push_back(i);
  }
  build(1, 1, n);
<<<<<<< HEAD
  for (int i = n - 1; i; i--) {
    res = inf;
    modify(1, 1, n, i + 1, n, c[i], res);
    for (int j = 0; j < qry[i].size(); j++) {
      ans[qry[i][j]] = query(1, 1, n, i + 1, que[qry[i][j]].r);
    }
  }
  for (int i = 1; i <= m; i++) {
    printf("%d\n", ans[i]);
  }
  system("pause");
=======
  for (int i = n - 1; i; i--)
  {
    res = inf;
    modify(1, 1, n, i + 1, n, c[i], res);
    for (int j = 0; j < qry[i].size(); j++)
    {
      ans[qry[i][j]] = query(1, 1, n, i + 1, que[qry[i][j]].r);
    }
  }
  for (int i = 1; i <= m; i++)
  {
    printf("%d\n", ans[i]);
  }

>>>>>>> 12d7aaa0a736d72ebd6c5434b2714963cf105792
  return 0;
}