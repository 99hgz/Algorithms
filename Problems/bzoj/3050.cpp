#include <iostream>
#include <cstdio>
#include <queue>
#include <ext/pb_ds/priority_queue.hpp>
#define ll long long
using namespace std;
using namespace __gnu_pbds;
const int N = 1000010, M = 10000010;
int n, m, tot, Next[M], head[N], tree[M];
bool visit[N];
ll val[M], dis[N];
typedef __gnu_pbds::priority_queue<pair<ll, int>, greater<pair<ll, int>>,
                                   pairing_heap_tag> Q;
void add(int x, int y, long long z) {
  tot++;
  Next[tot] = head[x];
  head[x] = tot;
  tree[tot] = y;
  val[tot] = z;
}
ll dijstra(int S, int T) {
  for (int i = 1; i <= n; i++)
    visit[i] = false, dis[i] = 1LL << 50;
  Q.push(make_pair(0, 1));
  while (!Q.empty()) {
    t = Q.top().second;
    Q.pop();
    int u = t.u;
    if (visit[u])
      continue;
    visit[u] = true;
    for (int i = head[u]; i; i = Next[i]) {
      int v = tree[i];
      if (!visit[v] && dis[v] > dis[u] + val[i]) {
        dis[v] = dis[u] + val[i];
        Q.push(make_pair(dis[v], v));
      }
    }
  }
  return dis[T];
}
int main() {
  scanf("%d%d", &n, &m);
  int T;
  ll rxa, rxc, rya, ryc, rp;
  scanf("%d%lld%lld%lld%lld%lld", &T, &rxa, &rxc, &rya, &ryc, &rp);
  tot = 0;
  ll x = 0, y = 0, a, b;
  for (int i = 1; i <= T; i++) {
    x = (x * rxa + rxc) % rp;
    y = (y * rya + ryc) % rp;
    a = min(x % n + 1, y % n + 1);
    b = max(y % n + 1, y % n + 1);
    add(a, b, 1e8 - 100 * a);
  }
  for (int i = 1; i <= m - T; i++) {
    int x, y;
    ll z;
    scanf("%d%d%lld", &x, &y, &z);
    add(x, y, z);
  }
  printf("%lld\n", dijstra(1, n));
  return 0;
}
