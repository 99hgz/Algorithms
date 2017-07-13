#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <stack>
#include <map>
#include <algorithm>
#include <string>
#include <climits>
using namespace std;
typedef long long ll;
int low[100100], dfn[100100], bh[100100];
int n, m, root, time1, scc;
bool instack[100100];
string a, b;
map<string, int> M;
vector<int> vec[100100];
stack<int> pointstack;

void addedge(int a, int b) {
  printf("%d %d\n", a, b);
  vec[a].push_back(b);
}

void tarjan(int u, int fa) {
  low[u] = dfn[u] = ++time1;
  pointstack.push(u);
  instack[u] = true;
  for (int i = 0; i < vec[u].size(); i++) {
    int v = vec[u][i];
    if (dfn[v] == 0) {
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
      tmp = pointstack.top();
      bh[tmp] = scc;
      instack[tmp] = false;
      pointstack.pop();
      if (tmp == u) {
        break;
      }
    }
  }
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a;
    cin >> b;
    M[a] = i;
    M[b] = i + n;
    addedge(i, i + n);
  }
  cin >> m;
  for (int i = 1; i <= m; i++) {
    cin >> a;
    cin >> b;
    addedge(M[b], M[a]);
  }
  for (int i = 1; i <= 2 * n; i++) {
    if (dfn[i] == 0) {
      root = i;
      tarjan(i, i);
    }
  }
  for (int i = 1; i <= n; i++) {
    printf("%d %d\n", bh[i], bh[i + n]);
    if (bh[i] != bh[i + n])
      printf("Safe\n");
    else
      printf("Unsafe\n");
  }
  system("pause");
  return 0;
}