#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

ll fa[100010], size[100010], timestamp, maxsonid[100010], dep[100010], in[100010], top[100010], init[100010], val[100010], out[100010];
vector<ll> vec[100010];

struct TREE
{
  ll lazy, sum;
} Tree[100010 * 4];
ll n, m, u, v, cases, x, y;

void addedge(ll u, ll v)
{
  vec[u].push_back(v);
}

void dfs1(ll x, ll father, ll depth)
{
  fa[x] = father, size[x] = 1, maxsonid[x] = 0, dep[x] = depth;
  ll maxsize = 0;
  for (ll i = 0; i < vec[x].size(); i++)
  {
    ll v = vec[x][i];
    if (v != father)
    {
      dfs1(v, x, depth + 1);
      size[x] += size[v];
      if (maxsize < size[v])
        maxsize = size[v],
        maxsonid[x] = v;
    }
  }
}

void dfs2(ll x, ll father, ll ancestor)
{
  in[x] = ++timestamp, top[x] = ancestor, init[timestamp] = val[x];
  if (maxsonid[x])
    dfs2(maxsonid[x], x, ancestor);
  for (ll i = 0; i < vec[x].size(); i++)
  {
    ll v = vec[x][i];
    if (v != father && v != maxsonid[x])
      dfs2(v, x, v);
  }
  out[x] = timestamp;
}

void up(ll rt)
{
  Tree[rt].sum = Tree[rt * 2].sum + Tree[rt * 2 + 1].sum;
}

void doplus(ll rt, ll l, ll r, ll v)
{
  Tree[rt].lazy += v;
  Tree[rt].sum += (ll)(r - l + 1) * v;
}

void pushdown(ll rt, ll l, ll r)
{
  if (Tree[rt].lazy)
  {
    ll mid = (l + r) >> 1;
    doplus(rt * 2, l, mid, Tree[rt].lazy);
    doplus(rt * 2 + 1, mid + 1, r, Tree[rt].lazy);
    Tree[rt].lazy = 0;
  }
}

void build(ll rt, ll l, ll r)
{
  if (l == r)
  {
    Tree[rt].sum = init[l];
    return;
  }
  ll mid = (l + r) >> 1;
  build(rt * 2, l, mid);
  build(rt * 2 + 1, mid + 1, r);
  up(rt);
}

void modify(ll rt, ll l, ll r, ll L, ll R, ll v)
{
  if (L <= l && r <= R)
  {
    doplus(rt, l, r, v);
    return;
  }
  if (r < L || l > R)
    return;
  pushdown(rt, l, r);
  ll mid = (l + r) >> 1;
  modify(rt * 2, l, mid, L, R, v), modify(rt * 2 + 1, mid + 1, r, L, R, v);
  up(rt);
}

ll query(ll rt, ll l, ll r, ll L, ll R)
{
  if (L <= l && r <= R)
    return Tree[rt].sum;
  if (r < L || l > R)
    return 0;
  pushdown(rt, l, r);
  ll mid = (l + r) >> 1;
  return query(rt * 2, l, mid, L, R) + query(rt * 2 + 1, mid + 1, r, L, R);
}

ll Query(ll x, ll y)
{
  ll res = 0;
  while (top[x] != top[y])
  {
    if (dep[top[x]] < dep[top[y]])
      swap(x, y);
    res += query(1, 1, n, in[top[x]], in[x]);
    x = fa[top[x]];
    //printf("jump:%lld %lld\n", x, y);
  }
  if (dep[x] < dep[y])
    swap(x, y);
  res += query(1, 1, n, in[y], in[x]);
  return res;
}

int main()
{

  scanf("%lld%lld", &n, &m);
  for (ll i = 1; i <= n; i++)
    scanf("%lld", &val[i]);
  for (ll i = 1; i <= n - 1; i++)
  {
    scanf("%lld%lld", &u, &v);
    addedge(u, v);
    addedge(v, u);
  }
  dfs1(1, 1, 1);
  dfs2(1, 1, 1);
  build(1, 1, n);
  for (ll i = 1; i <= m; i++)
  {
    scanf("%lld%lld", &cases, &x);
    if (cases == 1)
    {
      scanf("%lld", &y);
      modify(1, 1, n, in[x], in[x], y);
    }
    else if (cases == 2)
    {
      scanf("%lld", &y);
      modify(1, 1, n, in[x], out[x], y);
    }
    else
      printf("%lld\n", Query(1, x));
  }
  //system("pause");
  return 0;
}