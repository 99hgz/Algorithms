
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
typedef long long ll;
stack<int> pointstack;
vector<int> vec[20010];
int indu[20010], color[20010], u[20010], v[20010], pos[20010], c[20010], n, m,
    dfn[20010], low[20010], scc[20010], f[20010], time1, sccnum;
bool instack[20010];
void tarjan(int u, int fa) {
  low[u] = dfn[u] = ++time1;
  pointstack.push(u);
  instack[u] = true;
  for (int i = 0; i < vec[u].size(); i++) {
    int v = vec[u][i];
    if (dfn[v] == -1) {
      tarjan(v, u);
      low[u] = min(low[u], low[v]);
    } else if (instack[v]) {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if (low[u] == dfn[u]) {
    sccnum++;
    int tmp;
    while (!pointstack.empty()) {
      tmp = pointstack.top();
      instack[tmp] = false;
      pointstack.pop();
      scc[tmp] = sccnum;
      if (tmp == u) {
        break;
      }
    }
  }
}

void addedge(int u, int v) {
  u--, v--;
  vec[u].push_back(v);
}

int main() {
  int t;
  scanf("%d", &t);
  while (~scanf("%d%d", &m, &n)) {

    for (int i = 1; i <= n; i++) {
      scanf("%d%d", &u[i], &v[i]);
      // printf("%d %d\n", u[i], v[i]);
    }
    for (int i = 1; i <= m; i++) {
      scanf("%d", &c[i]);
      pos[c[i]] = i;
    }
    if (n > 3 * m - 6) {
      printf("NO\n");
      continue;
    }
    int inedge = 0;
    for (int i = 1; i <= n; i++) {
      u[i] = pos[u[i]], v[i] = pos[v[i]];
      if (u[i] > v[i])
        swap(u[i], v[i]);
      if (v[i] - u[i] == 1 || (u[i] == 1 && v[i] == m))
        continue;
      u[++inedge] = u[i];
      v[inedge] = v[i];
    }
    n = inedge;

    memset(dfn, -1, sizeof(dfn));
    memset(color, 0, sizeof(color));
    memset(indu, 0, sizeof(indu));
    memset(f, 0, sizeof(f));
    memset(scc, 0, sizeof(scc));
    memset(instack, 0, sizeof(instack));
    memset(low, 0, sizeof(low));
    sccnum = 0;
    while (!pointstack.empty())
      pointstack.pop();
    time1 = 0;
    for (int i = 0; i <= 2 * n; i++) {

      vec[i].clear();
    }

    for (int i = 1; i <= n; i++) {
      for (int j = i + 1; j <= n; j++) {
        if ((u[i] < u[j] && v[i] < v[j] && v[i] > u[j]) ||
            u[j] < u[i] && v[i] > v[j] && v[j] > u[i]) {
          addedge(2 * i - 1, 2 * j);
          addedge(2 * j - 1, 2 * i);
          addedge(2 * j, 2 * i - 1);
          addedge(2 * i, 2 * j - 1);
        }
      }
    }

    //缩点
    bool flag = false;
    for (int i = 0; i < 2 * n; i++) {
      if (dfn[i] == -1)
        tarjan(i, i);
    }
    //判断有解
    for (int i = 0; i < 2 * n; i += 2)
      if (scc[i] == scc[i + 1]) {
        printf("NO\n");
        flag = true;
        break;
      }

    if (flag) {
      continue;
    } else {
      printf("YES\n");
    }
  }
  system("pause");
  return 0;
}