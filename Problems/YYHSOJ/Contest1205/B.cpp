#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
const int size = 100100;
int tree[size * 4], cancontrol[size], sorted[size], sortedq[size], ans[size];
struct Person {
  int rank, age;
} p[size];
struct Query {
  int x, y, rmin;
} query[size];
int n, k, i, q;
typedef long long ll;

// const int MAXN = 1010;

struct line {
  int l;
  int r;
  int cmax;
} Tree[size * 10];

void pushUp(int t) {
  int x = t << 1;
  Tree[t].cmax = max(Tree[x + 1].cmax, Tree[x + 2].cmax);
}

void buildTree(int l, int r, int t) {
  Tree[t].l = l;
  Tree[t].r = r;
  Tree[t].cmax = -1;
  if (l == r)
    return;
  int x = (l + r) >> 1;
  buildTree(l, x, t << 1 | 1);
  buildTree(x + 1, r, (t << 1) + 2);
  pushUp(t);
}

void updateTree(int v, int cn, int t) {
  if (Tree[t].l == v && Tree[t].r == v) {
    Tree[t].cmax = max(cn, Tree[t].cmax);
    return;
  }
  int m = (Tree[t].l + Tree[t].r) >> 1;
  if (v <= m) {
    updateTree(v, cn, t << 1 | 1);
  } else {
    updateTree(v, cn, (t << 1) + 2);
  }
  pushUp(t);
}

int queryTree(int l, int r, int t) {
  if (l > r)
    return -1;
  if (Tree[t].l == l && Tree[t].r == r) {
    return Tree[t].cmax;
  }
  int m = (Tree[t].l + Tree[t].r) >> 1;
  if (l > m) {
    return queryTree(l, r, (t << 1) + 2);
  } else if (r <= m) {
    return queryTree(l, r, t << 1 | 1);
  } else {
    int ret1 = queryTree(l, m, t << 1 | 1);
    int ret2 = queryTree(m + 1, r, (t << 1) + 2);
    return max(ret1, ret2);
  }
}

int lowbit(int x) { return x & -x; }

ll sum(int end) {
  end++;
  ll ans = 0;
  while (end > 0) {
    ans += tree[end];
    end -= lowbit(end);
  }
  return ans;
}
void update(int pos, int num) {
  pos++;
  while (pos < size) {
    tree[pos] += num;
    pos += lowbit(pos);
  }
}

bool cmp(int a, int b) { return p[a].rank > p[b].rank; }
bool cmp1(int a, int b) { return p[a].rank < p[b].rank; }
bool cmpforq(int a, int b) { return query[a].rmin > query[b].rmin; }
vector<int> age_vec;
map<int, bool> age_exist;
void age_disperse() {
  // age_vec.push_back(-1000000001);
  for (int i = 1; i <= n; i++) {
    if (!age_exist[p[i].age]) {
      age_exist[p[i].age] = true;
      age_vec.push_back(p[i].age);
    }
  }
  age_vec.push_back(1000000001);
  sort(age_vec.begin(), age_vec.end());
}

int age_getdispersedpos(int x, bool bigger) {
  // printf("%d\n", x);
  int location =
      lower_bound(age_vec.begin(), age_vec.end(), x) - age_vec.begin();
  // printf("%d\n", location);
  if (!bigger) {
    if (age_vec[location] != x) {
      location--;
    }
  }
  // printf("%d-->%d\n", location, x);
  return location;
}

int main() {
  scanf("%d%d", &n, &k);
  for (i = 1; i <= n; i++) {
    scanf("%d", &p[i].rank);
    sorted[i] = i;
  }
  for (i = 1; i <= n; i++) {
    scanf("%d", &p[i].age);
  }
  age_disperse();
  sort(sorted + 1, sorted + n + 1, cmp1);
  int pointa = 1;
  int pointb = 0;
  while ((pointb <= n) && (pointa <= n)) {
    while (p[sorted[pointa]].rank == p[sorted[pointa + 1]].rank) {
      update(age_getdispersedpos(p[sorted[pointa]].age, true), 1);
      // printf("inserted %d\n", p[sorted[pointa]].age);
      pointa++;
    }
    update(age_getdispersedpos(p[sorted[pointa]].age, true), 1);
    // printf("inserted %d\n", p[sorted[pointa]].age);
    // //printf("inserted total:%d\n", sum(max(5, 1)));
    for (int i = pointb + 1; i <= pointa; i++) {
      cancontrol[sorted[i]] =
          sum(age_getdispersedpos(p[sorted[i]].age + k, false)) -
          sum(age_getdispersedpos(p[sorted[i]].age - k - 1, false));
      // printf("cancontrol %d=%d\n", sorted[i], cancontrol[sorted[i]]);
    }
    pointb = pointa;
    pointa++;
  }
  sort(sorted + 1, sorted + n + 1, cmp);
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    scanf("%d%d", &query[i].x, &query[i].y);
    query[i].rmin = max(p[query[i].x].rank, p[query[i].y].rank);
    sortedq[i] = i;
  }
  sort(sortedq + 1, sortedq + q + 1, cmpforq);
  buildTree(0, n + 100, 0);
  int tail = 1;
  for (int i = 1; i <= q; i++) {
    while ((query[sortedq[i]].rmin <= p[sorted[tail]].rank)) {
      updateTree(age_getdispersedpos(p[sorted[tail]].age, true),
                 cancontrol[sorted[tail]], 0);
      // printf("update %d with %d\n",
      //       age_getdispersedpos(p[sorted[tail]].age, true),
      //       cancontrol[sorted[tail]]);
      tail++;
    }
    // printf("search from %d to %d\n",
    // max(age_getdispersedpos(p[query[sortedq[i]].x].age - k, true),
    //   age_getdispersedpos(p[query[sortedq[i]].y].age - k, true)),
    // min(age_getdispersedpos(p[query[sortedq[i]].x].age + k, false),
    //    age_getdispersedpos(p[query[sortedq[i]].y].age + k, false)));
    ans[sortedq[i]] = queryTree(
        max(age_getdispersedpos(p[query[sortedq[i]].x].age - k, true),
            age_getdispersedpos(p[query[sortedq[i]].y].age - k, true)),
        min(age_getdispersedpos(p[query[sortedq[i]].x].age + k, false),
            age_getdispersedpos(p[query[sortedq[i]].y].age + k, false)),
        0);
  }
  for (int i = 1; i <= q; i++) {
    printf("%d\n", ans[i]);
  }
  system("pause");
}
