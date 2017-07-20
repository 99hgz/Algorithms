#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
bool used[110];
int belong[110];
int ishome[55], isstu[55];
vector<int> vec[110];
int ans, n, m, sl, b, total, tmp;

void addedge(int u, int v) { vec[u].push_back(v); }

bool find(int x) {
  for (int k = 0; k < vec[x].size(); k++) {
    int j = vec[x][k];
    if ((!used[j])) {
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
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    for (int i = 1; i <= 2 * n; i++) {
      vec[i].clear();
    }
    for (int i = 1; i <= n; i++) {
      scanf("%d", &isstu[i]);
      // if (isstu[i]) owner[++bed]=i;
    }

    for (int i = 1; i <= n; i++) {
      scanf("%d", &ishome[i]);
      if ((!ishome[i]) && (isstu[i]))
        addedge(i, i);
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        scanf("%d", &tmp);
        if ((isstu[j]) && (tmp))
          addedge(i, j);
      }
    }
    ans = 0;
    memset(belong, 0, sizeof belong);
    for (int i = 1; i <= n; i++) {
      memset(used, 0, sizeof(used));
      if (((isstu[i]) && (!ishome[i])) || (!isstu[i]))
        if (find(i))
          ans++;
    }
    total = 0;
    for (int i = 1; i <= n; i++) {
      if (((isstu[i]) && (!ishome[i])) || (!isstu[i]))
        total++;
    }
    if (ans == total)
      printf("ˆ ˆ\n");
    else
      printf("T_T\n");
  }
  return 0;
}