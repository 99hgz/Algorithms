/*
 * @key word:边双联通分量
 * @已测试:http://hihocoder.com/problemset/problem/1184
 * @Author: hgz
 * @Date: 2017-07-10 21:14:01
 * @Last Modified by: hgz
 * @Last Modified time: 2017-07-10 22:08:33
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>
using namespace std;
typedef long long ll;
int low[100100], dfn[100100], ans[100100];
int n, m, a, b, root, time1, dcc;
bool visited[100100];

vector<int> vec[100100];
struct BRIDGE {
  int u, v;
};
vector<BRIDGE> bridge;
stack<int> pointstack;
void addedge(int a, int b) { vec[a].push_back(b); }
bool cmp(BRIDGE a, BRIDGE b) {
  if (a.u == b.u)
    return (a.v < b.v);
  else
    return (a.u < b.u);
}
void tarjan(int u, int fa) {
  low[u] = dfn[u] = ++time1;
  visited[u] = true;
  int son = 0;
  pointstack.push(u);
  for (int i = 0; i < vec[u].size(); i++) {
    int v = vec[u][i];
    if (!visited[v]) {
      son++;
      tarjan(v, u);
      low[u] = min(low[u], low[v]);
      if (dfn[u] < low[v]) {
        int tu = u, tv = v;
        if (u > v)
          swap(tu, tv);
        bridge.push_back((BRIDGE){tu, tv});
      }

    } else if (fa != v) {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if (low[u] == dfn[u]) {
    stack<int> group;
    dcc++;
    int tmp, minst = INT_MAX;
    while (!pointstack.empty()) {
      // ans[pointstack.top()]=dcc;
      tmp = pointstack.top();
      group.push(tmp);
      if (tmp < minst)
        minst = tmp;
      pointstack.pop();
      if (tmp == u) {
        break;
      }
    }
    while (!group.empty()) {
      ans[group.top()] = minst;
      group.pop();
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &a, &b);
    addedge(a, b);
    addedge(b, a);
  }
  for (int i = 1; i <= n; i++) {
    if (!visited[i]) {
      root = i;
      tarjan(i, i);
    }
  }
  printf("%d\n", dcc);
  for (int i = 1; i <= n; i++) {
    printf("%d ", ans[i]);
  }
  system("pause");
  return 0;
}