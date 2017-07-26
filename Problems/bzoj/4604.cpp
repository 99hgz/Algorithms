#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
int c;
struct Node {
  int x, y, v;
} did[50010];

vector<int> vec;
int n, q, cz, x, y, v, x1, x2, y1, y2, k;
bool cmp(int a, int b) { return a > b; }
int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= q; i++) {
    scanf("%d", &cz);
    if (cz == 1) {
      scanf("%d%d%d", &x, &y, &v);
      did[++c].x = x;
      did[c].y = y;
      did[c].v = v;
    } else {
      scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &k);
      vec.clear();
      for (int i = 1; i <= c; i++) {
        if (did[i].x >= x1 && did[i].y >= y1 && did[i].x <= x2 &&
            did[i].y <= y2) {
          vec.push_back(did[i].v);
        }
      }
      if (vec.size() < k) {
        printf("NAIVE!ORZzyz.\n");
      } else {
        nth_element(vec.begin(), vec.begin() + k - 1, vec.end(), cmp);
        printf("%d\n", vec[k - 1]);
      }
    }
  }
  system("pause");
  return 0;
}