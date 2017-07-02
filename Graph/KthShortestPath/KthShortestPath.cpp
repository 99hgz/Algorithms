#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>

using namespace std;
typedef long long ll;

struct PATH {
  int dis, to;
};
struct a_star_node {
  int point, g, f;
  bool operator<(const a_star_node &r) const {
    if (r.f == f)
      return r.g < g;
    return r.f < f;
  }
};

vector<PATH> path[1010];
vector<PATH> path2[1010];

int vis[1010], dis[1010];
bool inq[1010];
int cnt, s, t, k, a, b, c, n, m, i;

void spfa() {
  memset(vis, 0, sizeof(vis));
  memset(inq, 0, sizeof(inq));
  memset(dis, 0x7f7f7f7f, sizeof(dis));
  queue<int> Q1;
  Q1.push(t);
  inq[t] = true;
  dis[t] = 0;
  while (!Q1.empty()) {
    int tmp = Q1.front();
    Q1.pop();
    inq[tmp] = false;
    vis[tmp]++;
    if (vis[tmp] > n)
      return;
    for (int i = 0; i < path2[tmp].size(); i++) {
      int goton = path2[tmp][i].to;
      if (dis[goton] > dis[tmp] + path2[tmp][i].dis) {
        dis[goton] = dis[tmp] + path2[tmp][i].dis;
        if (!inq[goton]) {
          Q1.push(goton);
          inq[goton] = true;
        }
      }
    }
  }
}

int a_star() {
  priority_queue<a_star_node> Q2;
  a_star_node TMP, thispoint;
  int found_path = 0;
  if (s == t)
    found_path++;
  if (dis[s] == 2139062143)
    return -1;
  TMP.point = s;
  TMP.g = 0;
  TMP.f = TMP.g + dis[s];
  Q2.push(TMP);
  while (!Q2.empty()) {
    thispoint = Q2.top();
    Q2.pop();
    if (thispoint.point == t)
      found_path++;
    if (found_path == k)
      return thispoint.g;
    for (int i = 0; i < path[thispoint.point].size(); i++) {
      TMP.point = path[thispoint.point][i].to;
      TMP.g = path[thispoint.point][i].dis + thispoint.g;
      TMP.f = TMP.g + dis[TMP.point];
      Q2.push(TMP);
    }
  }
  return -1;
}

void addpath(int a, int b, int c) {
  PATH tmp;
  tmp.to = b;
  tmp.dis = c;
  path[a].push_back(tmp);
}

void addinversepath(int a, int b, int c) {
  PATH tmp;
  tmp.to = b;
  tmp.dis = c;
  path2[a].push_back(tmp);
}

int main() {
  scanf("%d%d", &n, &m);
  for (i = 1; i <= m; i++) {
    scanf("%d%d%d", &a, &b, &c);
    addpath(a, b, c);
    addinversepath(b, a, c);
  }
  scanf("%d%d%d", &s, &t, &k);
  spfa();
  printf("%d\n", a_star());
  system("pause");
  return 0;
}