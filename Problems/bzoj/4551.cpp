#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

int p[1000100], mark[1000100], father[1000100], obj[1000100], ans[1000100];
vector<int> vec[1000100];
bool visited[1000100];
int n, q, a, b;
char opt[1000100];

int Find_set(int x) { return p[x] == -1 ? x : p[x] = Find_set(p[x]); }
void U(int a, int b) {
  a = Find_set(a);
  b = Find_set(b);
  if (a != b)
    p[a] = b;
}
void dfs(int x, int closetmark, int thisfather) {
  visited[x] = true;
  father[x] = thisfather;
  if (mark[x]) {
    for (int i = 0; i < vec[x].size(); i++) {
      if (!visited[vec[x][i]])
        dfs(vec[x][i], x, x);
    }
  } else {
    U(x, closetmark);
    for (int i = 0; i < vec[x].size(); i++) {
      if (!visited[vec[x][i]])
        dfs(vec[x][i], closetmark, x);
    }
  }
}

void addedge(int a, int b) {
  vec[a].push_back(b);
  vec[b].push_back(a);
}

int main() {
  memset(p, -1, sizeof p);
  scanf("%d%d", &n, &q);
  for (int i = 1; i < n; i++) {
    scanf("%d%d", &a, &b);
    addedge(a, b);
  }
  for (int i = 1; i <= q; i++) {
    opt[i] = getchar();
    while (opt[i] != 'C' && opt[i] != 'Q')
      opt[i] = getchar();
    scanf("%d", &obj[i]);
    if (opt[i] == 'C')
      mark[obj[i]]++;
  }
  mark[1]++;
  dfs(1, 0, 1);
  for (int i = q; i >= 1; i--) {
    if (opt[i] == 'C') {
      mark[obj[i]]--;
      if (mark[obj[i]] == 0)
        U(obj[i], father[obj[i]]);
    } else {
      ans[i] = Find_set(obj[i]);
    }
  }
  for (int i = 1; i <= q; i++) {
    if (ans[i])
      printf("%d\n", ans[i]);
  }
  // system("pause");
  return 0;
}