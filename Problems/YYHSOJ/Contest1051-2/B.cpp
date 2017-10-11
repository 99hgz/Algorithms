/*
 * @key word:强联通分量
 * @已测试:http://acm.hdu.edu.cn/showproblem.php?pid=1269
 * @Author: hgz
 * @Date: 2017-07-10 21:14:01
 * @Last Modified by: hgz
 * @Last Modified time: 2017-07-12 20:28:07
 */
#define MAXN 6
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>
#include <queue>
using namespace std;
typedef long long ll;
int low[210], dfn[210], bh[210], size[210];
int n, m, a, b, root, time1, scc, ans;
bool instack[210];
vector<int> vec[210];

struct NEWEDGE {
  int to;
  bool p;
};

vector<NEWEDGE> newvec[210];

struct EDGE {
  int l, r;
};
vector<EDGE> edges;

stack<int> pointstack;

void addedge(int a, int b) { vec[a].push_back(b); }

void tarjan(int u, int fa) {
  low[u] = dfn[u] = ++time1;
  pointstack.push(u);
  instack[u] = true;
  for (int i = 0; i < vec[u].size(); i++) {
    int v = vec[u][i];
    if (!dfn[v]) {
      tarjan(v, u);
      low[u] = min(low[u], low[v]);
    } else if (instack[v]) {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if (low[u] == dfn[u]) {
    scc++;
    int tmp;
    while (!pointstack.empty()) {
      size[scc]++;
      tmp = pointstack.top();
      instack[tmp] = false;
      pointstack.pop();
      bh[tmp] = scc;
      if (tmp == u) {
        break;
      }
    }
  }
}

bool dfs(int u, int v) {
  if (u == v)
    return true;
  for (int i = 0; i < newvec[u].size(); i++) {
    if (!newvec[u][i].p)
      if (dfs(newvec[u][i].to, v))
        return true;
  }
  return false;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    edges.clear();

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      vec[i].clear();
      newvec[i].clear();
      for (int j = 1; j <= n; j++) {
        scanf("%d", &a);
        if ((a == 1) && (i != j)) {
          addedge(i, j);
          edges.push_back((EDGE){i, j});
        }
      }
    }
    memset(low, 0, sizeof(low));
    memset(dfn, 0, sizeof(dfn));
    memset(size, 0, sizeof(size));
    // memset(in, 0, sizeof(in));
    memset(instack, false, sizeof(instack));
    scc = 0;
    time1 = 0;
    while (!pointstack.empty())
      pointstack.pop();

    for (int i = 1; i <= n; i++) {
      if (dfn[i] == 0) {
        tarjan(i, i);
      }
    }

    int u, v;
    int ans = 0;
    for (int i = 0; i < edges.size(); i++) {
      u = edges[i].l;
      v = edges[i].r;
      if (bh[u] != bh[v]) {
        newvec[bh[u]].push_back((NEWEDGE){bh[v], false});
        // in[bh[u]]++;
        ans++;
      }
    }

    for (int i = 1; i <= scc; i++) {
      if (size[i] == 1)
        continue;
      ans += size[i];
    }
    for (int i = 1; i <= scc; i++) {
      for (int j = 0; j < newvec[i].size(); j++) {
        newvec[i][j].p = true;
        if (dfs(i, newvec[i][j].to))
          ans--;
        else
          newvec[i][j].p = false;
      }
    }
    printf("%d\n", ans);
  }

  return 0;
}