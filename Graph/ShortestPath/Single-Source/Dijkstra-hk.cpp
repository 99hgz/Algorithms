/*
 * @Author: hekai
 * @Date: 2017-06-05 21:53:26
 * @Last Modified by:   hgz
 * @Last Modified time: 2017-06-05 21:53:26
 */
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
int n, m, S, tot, Next[500010], head[20000], tree[500010], val[500010],
    dis[20000];
bool visit[20000];
struct Node
{
  int d, n;
} cur;
struct cmp
{
  bool operator()(Node a, Node b) { return a.d > b.d; }
};
priority_queue<Node, vector<Node>, cmp> Q;
void add(int x, int y, int z)
{
  tot++;
  Next[tot] = head[x];
  head[x] = tot;
  tree[tot] = y;
  val[tot] = z;
}
int main()
{
  scanf("%d%d%d", &n, &m, &S);
  tot = 0;
  for (int i = 1; i <= m; i++)
  {
    int x, y, z;
    scanf("%d%d%d", &x, &y, &z);
    if (x == y)
      continue;
    add(x, y, z);
  }
  for (int i = 1; i <= n; i++)
  {
    visit[i] = false;
    dis[i] = 2147483647;
  }
  cur.d = 0;
  cur.n = S;
  Q.push(cur);
  dis[S] = 0;
  while (!Q.empty())
  {
    int u = Q.top().n;
    Q.pop();
    if (visit[u])
      continue;
    visit[u] = true;
    for (int i = head[u]; i; i = Next[i])
    {
      int v = tree[i];
      if (!visit[v] && dis[v] > dis[u] + val[i])
      {
        dis[v] = dis[u] + val[i];
        cur.d = dis[v];
        cur.n = v;
        Q.push(cur);
      }
    }
  }
  for (int i = 1; i <= n - 1; i++)
    printf("%d ", dis[i]);
  printf("%d\n", dis[n]);
  return 0;
}
