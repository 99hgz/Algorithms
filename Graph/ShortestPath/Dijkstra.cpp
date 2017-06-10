#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <queue>

using namespace std;
typedef long long ll;

struct queNode
{
  int n, d;
} quenode;
struct vecNode
{
  int v, w;
} vecnode;
struct cmp
{
  bool operator()(queNode a, queNode b) { return a.d > b.d; }
};

int n, m, s, e, a, b, c;
bool visited[10010];
int d[10010];
vector<vecNode> vec[10010];
priority_queue<queNode, vector<queNode>, cmp> q;

void addedge(int u, int v, int w)
{
  vecnode.v = v;
  vecnode.w = w;
  vec[u].push_back(vecnode);
}

int dijkstra(int s, int e)
{
  for (int i = 1; i <= n; i++)
  {
    d[i] = 2147483647;
    visited[i] = false;
  }
  quenode.d = 0;
  quenode.n = s;
  d[s] = 0;
  q.push(quenode);
  queNode tmp;
  while (!q.empty())
  {
    tmp = q.top();
    q.pop();
    if (visited[tmp.n])
      continue;
    visited[tmp.n] = true;
    for (int i = 0; i < vec[tmp.n].size(); i++)
    {
      int u = tmp.n, v = vec[tmp.n][i].v;
      if ((!visited[v]) && (d[v] > d[u] + vec[u][i].w))
      {
        d[v] = d[u] + vec[u][i].w;
        quenode.d = d[v];
        quenode.n = v;
        q.push(quenode);
      }
    }
  }
}

int main()
{
  scanf("%d%d%d", &n, &m, &s);
  for (int i = 1; i <= m; i++)
  {
    scanf("%d%d%d", &a, &b, &c);
    addedge(a, b, c);
  }
  printf("%d\n", dijkstra(s, n));
  return 0;
}