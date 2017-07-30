#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
int n, len, sta1, sta2, a, b, m;
double w;
struct NODE {
  int to;
  double w;
} Node;

bool visited[3010];
int val[3010], cd[3010], times[3010];
double tdis[3010];
bool inq[3010];
vector<NODE> vec[3010];
void addedge(int a, int b, double w) {
  Node.to = b;
  Node.w = w;
  vec[a].push_back(Node);
}

bool spfa(int s, double x) {
  memset(tdis, 0x7f7f7f7f, sizeof(tdis));
  memset(inq, 0, sizeof(inq));
  memset(times, 0, sizeof(times));
  queue<int> Q;
  visited[s] = true;
  tdis[s] = 0;
  Q.push(s);
  inq[s] = true;
  times[s] = 1;
  int tmp;
  while (!Q.empty()) {
    tmp = Q.front();
    Q.pop();
    inq[tmp] = false;
    for (int i = 0; i < vec[tmp].size(); i++) {
      int v = vec[tmp][i].to;
      if (tdis[tmp] + (vec[tmp][i].w - x) < tdis[v]) {
        tdis[v] = tdis[tmp] + (vec[tmp][i].w - x);
        if (!inq[v]) {
          inq[v] = true;
          times[v]++;
          if (times[v] > 20) {
            return true;
          }
          Q.push(v);
          visited[v] = true;
        }
      }
    }
  }
  return false;
}

bool pd(double x) {
  memset(visited, 0, sizeof(visited));
  for (int i = 1; i <= n; i++) {
    if (!visited[i]) {
      if (spfa(i, x))
        return true;
    }
  }
  return false;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    scanf("%d%d%lf", &a, &b, &w);
    addedge(a, b, w);
  }
  double l = -10000000, r = 10000000, mid, t = 60;
  while (t--) {
    mid = (l + r) / (double)2;
    // printf("%d\n", pd(mid));
    if (!pd(mid)) {
      l = mid;
    } else {
      r = mid;
    }
    // printf("%.4lf %.4lf %.4lf\n", l, r, mid);
  }

  printf("%.8lf\n", mid);
  system("pause");
}