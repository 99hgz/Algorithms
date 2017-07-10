#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
int low[100100], dfn[100100];
int n, m, a, b, root, time1;
bool visited[100100];
vector<int> cut_vertex;
vector<int> vec[100100];
void addedge(int a, int b) { vec[a].push_back(b); }

void tarjan(int u, int fa) {
  low[u] = dfn[u] = ++time1;
  visited[u] = true;
  int son = 0;
  for (int i = 0; i < vec[u].size(); i++) {
    int v = vec[u][i];
    if (!visited[v]) {
      son++;
      tarjan(v, u);
      low[u] = min(low[u], low[v]);
      /*if (dfn[u] < low[v]) {
  bridge.push_back((BRIDGE){u, v})
}*/
      if (((u == root) && (son > 1)) || ((u != root) && (dfn[u] <= low[v]))) {
        cut_vertex.push_back(u);
      }
    } else if (fa != v) {
      low[u] = min(low[u], dfn[v]);
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
      tarjan(i, 0);
    }
  }

  sort(cut_vertex.begin(), cut_vertex.end());
  cut_vertex.erase(unique(cut_vertex.begin(), cut_vertex.end()),
                   cut_vertex.end());
  printf("%d\n", cut_vertex.size());
  for (int i = 0; i < cut_vertex.size(); i++) {
    printf("%d ", cut_vertex[i]);
  }
  // system("pause");
  return 0;
}