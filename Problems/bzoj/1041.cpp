#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
int father[510];
int n, m, x, y, v, s, t, ansi, ansi1;
struct PATH {
  int x, y, v;
};
vector<PATH> path;

inline int gcd(int a, int b) // a>b
{
  if (b == 0)
    return a;
  return gcd(b, a % b);
}
int cmp(PATH a, PATH b) { return a.v < b.v; }
int get_father(int x) {
  return father[x] == -1 ? x : father[x] = get_father(father[x]);
}
int unionset(int a, int b) {
  int fa = get_father(a), fb = get_father(b);
  if (fa == fb)
    return 1;
  else
    father[fa] = fb;
  return 0;
}
int main() {
  memset(father, -1, sizeof father);
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    scanf("%d%d%d", &x, &y, &v);
    path.push_back((PATH){x, y, v});
    unionset(x, y);
  }
  bool noans = true;
  scanf("%d%d", &s, &t);
  if (unionset(s, t) == 0) {
    printf("IMPOSSIBLE\n");
    // system("pause");
    return 0;
  } else {
    sort(path.begin(), path.end(), cmp);
    for (int i1 = 0; i1 < path.size(); i1++) {
      memset(father, -1, sizeof father);
      bool flag = false;
      int last = 0;
      for (int i = i1; i < path.size(); i++) {
        unionset(path[i].x, path[i].y);
        if (get_father(s) == get_father(t)) {
          flag = true;
          last = i;
          break;
        }
      }
      if (flag) {
        if ((noans) ||
            (path[last].v * path[ansi1].v < path[i1].v * path[ansi].v)) {
          ansi1 = i1, ansi = last, noans = false;
        }
      }
    }
  }
  int zdg = gcd(path[ansi1].v, path[ansi].v);
  // printf("%d %d\n", ansi1, path[ansi].v);
  if (path[ansi1].v != zdg)
    printf("%d/%d\n", path[ansi].v / zdg, path[ansi1].v / zdg);
  else
    printf("%d\n", path[ansi].v / path[ansi1].v);
  // system("pause");
  return 0;
}