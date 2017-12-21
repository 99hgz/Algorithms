#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

typedef pair<ll, ll> pr;
ll fa[100010], size[100010], ans, c, timestamp, maxsonid[100010], dep[100010], in[100010], top[100010], init[100010], val[100010], out[100010];
vector<ll> vec[100010];
struct TREE
{
    ll num, lazy, L, R;
} Tree[410000];
ll n, m, u, v, a, b;
char cases[10];
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
void make(ll rt, ll lazy)
{
    Tree[rt].L = Tree[rt].R = lazy;
    Tree[rt].lazy = lazy;
    Tree[rt].num = 1;
}

void pushdown(ll rt)
{
    if (Tree[rt].lazy != -1)
    {
        make(rt * 2, Tree[rt].lazy);
        make(rt * 2 + 1, Tree[rt].lazy);
        Tree[rt].lazy = -1;
    }
}

void up(ll rt)
{
    Tree[rt].num = Tree[rt * 2].num + Tree[rt * 2 + 1].num;
    if (Tree[rt * 2].R == Tree[rt * 2 + 1].L)
        Tree[rt].num--;
    Tree[rt].L = Tree[rt * 2].L, Tree[rt].R = Tree[rt * 2 + 1].R;
}

void build(ll rt, ll l, ll r)
{
    if (l == r)
    {
        Tree[rt].lazy = -1;
        Tree[rt].L = Tree[rt].R = init[l];
        Tree[rt].num = 1;
        return;
    }
    pushdown(rt);
    ll mid = (l + r) >> 1;
    build(rt * 2, l, mid);
    build(rt * 2 + 1, mid + 1, r);
    up(rt);
}

void modify(ll rt, ll l, ll r, ll L, ll R, ll c)
{
    if (L <= l && r <= R)
    {
        make(rt, c);
        return;
    }
    if (l > R || r < L)
        return;
    pushdown(rt);
    ll mid = (l + r) >> 1;
    modify(rt * 2, l, mid, L, R, c);
    modify(rt * 2 + 1, mid + 1, r, L, R, c);
    up(rt);
}

pr query(ll rt, ll l, ll r, ll L, ll R)
{
    if (L <= l && r <= R)
    {
        ans += Tree[rt].num;
        return make_pair(Tree[rt].L, Tree[rt].R);
    }
    if (l > R || r < L)
        return make_pair(-1, -1);
    pushdown(rt);
    ll mid = (l + r) >> 1;
    pr left = query(rt * 2, l, mid, L, R);
    pr right = query(rt * 2 + 1, mid + 1, r, L, R);
    if (left.second != -1 && right.first != -1)
        ans -= (left.second == right.first);
    return make_pair(left.first == -1 ? right.first : left.first, right.second == -1 ? left.second : right.second);
}

void Modify(ll x, ll y, ll c)
{
    ll res = 0;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        modify(1, 1, n, in[top[x]], in[x], c);
        x = fa[top[x]];
    }
    if (dep[x] < dep[y])
        swap(x, y);
    modify(1, 1, n, in[y], in[x], c);
}

void Query(ll x, ll y)
{
    ll left = -1, right = -1;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y), swap(left, right);
        pr tmp = query(1, 1, n, in[top[x]], in[x]);
        if (tmp.second != -1 && left != -1)
            ans -= (tmp.second == left);
        left = tmp.first;
        x = fa[top[x]];
    }
    if (dep[x] < dep[y])
        swap(x, y), swap(left, right);
    pr tmp = query(1, 1, n, in[y], in[x]);
    if (tmp.first == right)
        ans--;
    if (tmp.second == left)
        ans--;
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
        scanf("%s%lld%lld", cases, &a, &b);
        if (cases[0] == 'C')
        {
            scanf("%lld", &c);
            Modify(a, b, c);
        }
        else
        {
            ans = 0;
            Query(a, b);
            printf("%lld\n", ans);
        }
    }
    //system("pause");
    return 0;
}