/*
 * @参考文章:反素数深度分析
 * http://blog.csdn.net/acdreamers/article/details/25049767
 * @Author: hgz
 * @Date: 2017-07-28 20:30:59
 * @Last Modified by: hgz
 * @Last Modified time: 2017-07-28 20:31:26
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef unsigned long long ll;
ll INF = ~0ULL;
int pri[16] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
ll ans, n, best;
void dfs(int dep, int limit, ll nownum, ll ys) {
  if (dep >= 16)
    return;
  if (nownum > n)
    return;
  if (ys > best) {
    best = ys;
    ans = nownum;
  } else if (ys == best) {
    if (nownum < ans)
      ans = nownum;
  }
  for (int i = 1; i <= limit; i++) {
    double cur = (double)nownum;
    if (n < cur * pri[dep])
      break;
    dfs(dep + 1, i, nownum *= pri[dep], ys * (i + 1));
  }
}

int main() {
  int t;
  scanf("%d\n", &t);
  while (t--) {
    scanf("%lld", &n);
    ans = INF;
    best = 0;
    dfs(0, 60, 1, 1);
    printf("%lld %lld\n", ans, best);
  }
  system("pause");
  return 0;
}