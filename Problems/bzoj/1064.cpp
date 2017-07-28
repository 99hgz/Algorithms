#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

struct PATH {
  int to, w, bh;
};

vector<PATH> vec[100100];

bool visited[100100], pathisvisited[2001000];
int times[100100], n, m, a, b, edgenum;
int minx, maxx, ans;

void addedge(int u, int v, int w) { vec[u].push_back((PATH){v, w, edgenum++}); }

int gcd(int a, int b) {
  if (a == 0)
    return b;
  if (b == 0)
    return a;
  int m = a % b;
  while (m != 0) {
    a = b;
    b = m;
    m = a % b;
  }
  return b;
}

void dfs(int x, int nowtime) {
  visited[x] = true;
  times[x] = nowtime;
  for (int i = 0; i < vec[x].size(); i++) {
    if (!visited[vec[x][i].to]) {
      dfs(vec[x][i].to, nowtime + vec[x][i].w);
    } else {
      ans = gcd(ans, abs(times[x] + vec[x][i].w - times[vec[x][i].to]));
    }
  }
}

void dfs2(int x, int nowtime) {
  // printf("%d\n", x);
  minx = min(minx, nowtime);
  maxx = max(maxx, nowtime);
  visited[x] = true;
  for (int i = 0; i < vec[x].size(); i++) {
    if (!pathisvisited[vec[x][i].bh]) {
      pathisvisited[vec[x][i].bh] = true;
      pathisvisited[vec[x][i].bh ^ 1] = true;
      dfs2(vec[x][i].to, nowtime + vec[x][i].w);
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &a, &b);
    addedge(a, b, 1);
    addedge(b, a, -1);
  }
  for (int i = 1; i <= n; i++) {
    if (!visited[i]) {
      dfs(i, 0);
    }
  }
  int finalans = 0;
  if (ans != 0) {
    if (ans >= 3) {
      printf("%d ", ans);
      for (int i = 3; i <= ans; i++) {
        if (ans % i == 0) {
          printf("%d\n", i);
          break;
          // system("pause");
          // return 0;
        }
      }
    } else {
      printf("-1 -1\n");
    }
  } else {
    ans = 0;
    memset(visited, 0, sizeof visited);
    for (int i = 1; i <= n; i++) {
      if (!visited[i]) {
        minx = 0;
        maxx = 0;
        dfs2(i, 0);
        ans += maxx - minx + 1;
      }
    }
    if (ans < 3)
      printf("-1 -1\n");
    else
      printf("%d %d\n", ans, 3);
  }
  system("pause");
  return 0;
}