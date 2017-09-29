#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

struct EDGE {
  int l, r;
} Edge;
bool exist_edge[100010];
bool cmp(EDGE a, EDGE b) { return a.r < b.r; }
vector<EDGE> edge;

void addedge(int a, int b) {
  Edge.l = a;
  Edge.r = b;
  edge.push_back(Edge);
}

int n, m, ans, a, b, r;

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &a, &b);
    if (a > b)
      swap(a, b);
    if ((b == (a + 1)) && (exist_edge[a] == false)) {
      exist_edge[a] = true;
    } else {
      addedge(a, b);
    }
  }
  ans = n - 1;
  sort(edge.begin(), edge.end(), cmp);
  for (int i = 0; i < edge.size(); i++) {
    if (edge[i].l >= r) {
      ans++;
      r = edge[i].r;
    }
  }
  printf("%d", ans);
  system("pause");
  return 0;
}