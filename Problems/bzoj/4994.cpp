#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

const int size = 100010;
int tree[size], a[100010], n, ans;
struct Node {
  int s, f;
} sta[100010];

typedef long long ll;
int lowbit(int x) {
  // return x&(x^(x-1));
  return x & -x;
}
int sum(int end) {
  int ans = 0;
  while (end > 0) {
    ans += tree[end];
    end -= lowbit(end);
  }
  return ans;
}
void update(int pos, int num) {
  while (pos < size) {
    tree[pos] += num;
    pos += lowbit(pos);
  }
}

bool cmp(Node a, Node b) { return a.f < b.f; }

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= 2 * n; i++) {
    scanf("%d", &a[i]);
    if (sta[a[i]].f == 0) {
      sta[a[i]].f = i;
    } else {
      sta[a[i]].s = i;
    }
  }
  sort(sta + 1, sta + 1 + n, cmp);
  for (int i = 1; i <= n; i++) {
    ans += sum(sta[i].s - 1) - sum(sta[i].f);
    update(sta[i].s, 1);
  }
  printf("%d\n", ans);
  system("pause");
  return 0;
}