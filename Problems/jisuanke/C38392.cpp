#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <map>
using namespace std;
typedef long long ll;
struct Point {
  int sl, x, y;
};
map<ll, Point> hashtable1;
ll hashed(int x, int y) {
  int tmp = ((x * 23333) + y) % 99443271;
  hashtable1[tmp].x = x;
  hashtable1[tmp].y = y;
  return tmp;
}
int n;
int main() {
  int i, n, t1, t2, t3, t4;
  scanf("%d", &n);
  for (i = 1; i <= n; i++) {
    scanf("%d%d%d%d", &t1, &t2, &t3, &t4);
    hashtable1[hashed(t3 - t1, t4 - t2)].sl += 1;
  }
  bool flag = false;
  map<ll, Point>::iterator Itr;
  for (Itr = hashtable1.begin(); Itr != hashtable1.end(); ++Itr) {
    if ((Itr->second.sl) >= ((n + 1) / 2)) {
      flag = true;
      printf("%d %d\n", Itr->second.x, Itr->second.y);
      break;
    }
  }
  if (!flag) {
    printf("0 0\n");
  }
  // system("pause");
  return 0;
}