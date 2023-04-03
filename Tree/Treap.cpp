#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
typedef long long ll;

typedef pair<int, int> Rootpair;
#define mp make_pair
int tot, opt, x, Root, n;
struct TREENODE {
  int val, fix, size, ch[2];
} Tree[100010];

int newnode(int x) {
  tot++;
  Tree[tot] = (TREENODE){x, rand(), 1};
  Tree[tot].ch[0] = Tree[tot].ch[1] = 0;
  return tot;
}

void up(int rt) {
  Tree[rt].size = Tree[Tree[rt].ch[0]].size + Tree[Tree[rt].ch[1]].size + 1;
}

void merge(int &rt, int L, int R) {
  if (!L || !R) {
    rt = L + R;
    return;
  }
  if (Tree[L].fix < Tree[R].fix)
    rt = L, merge(Tree[rt].ch[1], Tree[rt].ch[1], R);
  else
    rt = R, merge(Tree[rt].ch[0], L, Tree[rt].ch[0]);
  up(rt);
}

Rootpair split(int rt, int kth) {
  if (!kth)
    return mp(0, rt);
  int ls = Tree[rt].ch[0], rs = Tree[rt].ch[1];
  if (kth == Tree[ls].size) {
    Tree[rt].ch[0] = 0;
    up(rt);
    return mp(ls, rt);
  }
  if (kth == Tree[ls].size + 1) {
    Tree[rt].ch[1] = 0;
    up(rt);
    return mp(rt, rs);
  }
  if (kth < Tree[ls].size) {
    Rootpair tmp = split(ls, kth);
    Tree[rt].ch[0] = tmp.second;
    up(rt);
    return mp(tmp.first, rt);
  }
  Rootpair tmp = split(rs, kth - Tree[ls].size - 1);
  Tree[rt].ch[1] = tmp.first;
  up(rt);
  return mp(rt, tmp.second);
}

int getrank(int val) {
  int res = 0, tmp = 0x7f7f7f7f, rt = Root;
  while (rt) {
    if (val == Tree[rt].val)
      tmp = min(tmp, res + Tree[Tree[rt].ch[0]].size + 1);
    if (val > Tree[rt].val)
      res += Tree[Tree[rt].ch[0]].size + 1, rt = Tree[rt].ch[1];
    else
      rt = Tree[rt].ch[0];
  }
  return tmp == 0x7f7f7f7f ? res : tmp;
}

int findkth(int val) {
  int rt = Root;
  while (1) {
    if (Tree[Tree[rt].ch[0]].size + 1 == val)
      return rt;
    if (Tree[Tree[rt].ch[0]].size > val - 1)
      rt = Tree[rt].ch[0];
    else
      val -= Tree[Tree[rt].ch[0]].size + 1, rt = Tree[rt].ch[1];
  }
}

int pre(int val) {
  int rt = Root, res = 0x3f3f3f3f;
  while (rt) {
    if (Tree[rt].val > val)
      res = min(res, Tree[rt].val), rt = Tree[rt].ch[0];
    else
      rt = Tree[rt].ch[1];
  }
  return res;
}

int suc(int val) {
  int rt = Root, res = -0x3f3f3f3f;
  while (rt) {
    if (Tree[rt].val < val)
      res = max(res, Tree[rt].val), rt = Tree[rt].ch[1];
    else
      rt = Tree[rt].ch[0];
  }
  return res;
}

void insert(int val) {
  int rt = newnode(val);
  int Rank = getrank(val);
  Rootpair tmp = split(Root, Rank);
  merge(Root, tmp.first, rt);
  merge(Root, Root, tmp.second);
}

void del(int val) {
  int Rank = getrank(val);
  Rootpair tmp1 = split(Root, Rank);
  Rootpair tmp2 = split(tmp1.first, Rank - 1);
  merge(Root, tmp2.first, tmp1.second);
}

void debug(int rt) {
  if (rt == 0)
    return;
  debug(Tree[rt].ch[0]);
  printf("%d\n", Tree[rt].val);
  debug(Tree[rt].ch[1]);
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &opt, &x);
    if (opt == 1)
      insert(x);
    else if (opt == 2)
      del(x);
    else if (opt == 3)
      printf("%d\n", getrank(x));
    else if (opt == 4)
      printf("%d\n", Tree[findkth(x)].val);
    else if (opt == 5)
      printf("%d\n", suc(x));
    else
      printf("%d\n", pre(x));
  }
  system("pause");
  return 0;
}