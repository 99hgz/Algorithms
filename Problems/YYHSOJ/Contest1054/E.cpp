#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
bool used[10010];
bool deleted[110][110];
int belong[10010];
vector<int> vec[10010];
int ans, n, m, sl, b, x, y;
int calc_V(int i, int j) { return (i - 1) * n + j - 1; }

void addedge(int ui, int uj, int vi, int vj) {
  if ((ui > 0) && (uj > 0) && (ui <= n) && (uj <= n)) {
    if (deleted[ui][uj])
      return;
    vec[calc_V(ui, uj)].push_back(calc_V(vi, vj));
    // vec[calc_V(vi, vj)].push_back(calc_V(ui, uj));
  }
}

bool find(int x) {
  for (int y = 0; y < vec[x].size(); y++) {
    int j = vec[x][y];
    if (!used[j]) {
      used[j] = true;
      if ((belong[j] == 0) || (find(belong[j]))) {
        belong[j] = x;
        return true;
      }
    }
  }
  return false;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &x, &y);
    deleted[x][y] = true;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (deleted[i][j])
        continue;
      addedge(i - 1, j, i, j);
      addedge(i, j - 1, i, j);
      addedge(i + 1, j, i, j);
      addedge(i, j + 1, i, j);
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      memset(used, 0, sizeof used);
      if (find(calc_V(i, j)))
        ans++;
    }
  }
  printf("%d\n", ans / 2);
  system("pause");
  return 0;
}