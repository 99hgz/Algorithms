#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
int n, len, sta1, sta2;

struct NODE {
  int to, w;
} Node;

bool visited[680];
int val[680], cd[680], times[680];
double tdis[680];
bool inq[680];
vector<NODE> vec[680];
vector<int> point;
int dis[680][680];
bool exist[680];
void addedge(int a, int b, int w) {
  if (exist[a] == false) {
    point.push_back(a);
    exist[a] = true;
  }
  if (exist[b] == false) {
    point.push_back(b);
    exist[b] = true;
  }
  if (w > dis[a][b]) {
    dis[a][b] = w;
    Node.to = b;
    Node.w = w;
    vec[a].push_back(Node);
  }
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
      if (tdis[tmp] + (x - dis[tmp][v]) < tdis[v]) {
        tdis[v] = tdis[tmp] + (x - dis[tmp][v]);
        if (!inq[v]) {
          inq[v] = true;
          times[v]++;
          if (times[v] > 50) {
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
  for (int i = 0; i < point.size(); i++) {
    if (!visited[point[i]]) {
      if (spfa(point[i], x))
        return true;
    }
  }
  return false;
}

int main() {
  scanf("%d", &n);
  char st[1010];
  for (int i = 1; i <= n; i++) {
    scanf("%s", st);
    len = strlen(st);
    sta1 = ((int)(st[0]) - 97) * 26 + (int)(st[1]) - 97;
    sta2 = ((int)(st[len - 2]) - 97) * 26 + (int)(st[len - 1]) - 97;
    addedge(sta1, sta2, len);
  }
  double l = 0, r = 1001, eps = 0.0001, mid;
  while ((r - l) > eps) {
    mid = (l + r) / (double)2;
    if (pd(mid)) {
      l = mid;
    } else {
      r = mid;
    }
    // printf("%.4lf %.4lf %.4lf\n", l, r, mid);
  }

  if (mid < 0.1) {
    printf("No solution.\n");
  } else {
    printf("%.2lf\n", mid);
  }
  system("pause");
}