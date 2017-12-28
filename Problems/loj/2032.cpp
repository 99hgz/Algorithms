#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

ll fa[100010], size[100010], timestamp, maxsonid[100010], dep[100010], in[100010], top[100010], init[100010], val[100010], out[100010];
ll toroot[100010], dfs2val[100010];
struct Node
{
    ll v, w;
};
vector<Node> vec[100010];
ll k[100010], b[100010];
ll tree[100010 * 4];
ll n, m, u, v, cases, x, y, w;
ll s, t, a, tot;
ll mx[100010 * 4];
void addedge(ll u, ll v, ll w)
{
    vec[u].push_back((Node){v, w});
}

void dfs1(ll x, ll father, ll depth, ll dep2)
{
    fa[x] = father, size[x] = 1, maxsonid[x] = 0, dep[x] = depth, toroot[x] = dep2;
    ll maxsize = 0;
    for (ll i = 0; i < vec[x].size(); i++)
    {
        ll v = vec[x][i].v;
        if (v != father)
        {
            dfs1(v, x, depth + 1, dep2 + vec[x][i].w);
            size[x] += size[v];
            if (maxsize < size[v])
                maxsize = size[v],
                maxsonid[x] = v;
        }
    }
}

void dfs2(ll x, ll father, ll ancestor)
{
    in[x] = ++timestamp, top[x] = ancestor, init[timestamp] = toroot[x];
    if (maxsonid[x])
        dfs2(maxsonid[x], x, ancestor);
    for (ll i = 0; i < vec[x].size(); i++)
    {
        ll v = vec[x][i].v;
        if (v != father && v != maxsonid[x])
            dfs2(v, x, v);
    }
    out[x] = timestamp;
}

bool pd(ll x, ll y, ll pos)
{
    return (ll)b[x] + (ll)k[x] * (init[pos]) < (ll)b[y] + (ll)k[y] * (init[pos]);
}

ll calc(ll x, ll pos)
{
    return (ll)b[x] + (ll)k[x] * (init[pos]);
}

void update(ll rt, ll l, ll r)
{
    if (l == r)
        mx[rt] = (ll)123456789123456789;
    else
        mx[rt] = min(mx[rt * 2], mx[rt * 2 + 1]);
    mx[rt] = min(mx[rt], min(calc(tree[rt], l), calc(tree[rt], r)));
    //printf("update %lld to %lld\n", rt, mx[rt]);
}

void insert(ll rt, ll l, ll r, ll L, ll R, ll id)
{
    //printf("insert:rt=%lld l=%lld r=%lld L=%lld R=%lld id=%lld\n", rt, l, r, L, R, id);
    if (L <= l && r <= R)
    {
        if (l == r)
        {
            if (pd(id, tree[rt], l))
                tree[rt] = id;
            update(rt, l, r);
            return;
        }
        ll mid = (l + r) >> 1;
        if (k[id] > k[tree[rt]])
        {
            if (pd(id, tree[rt], mid))
                insert(rt * 2, l, mid, L, R, tree[rt]), tree[rt] = id;
            else
                insert(rt * 2 + 1, mid + 1, r, L, R, id);
        }
        else
        {
            if (pd(id, tree[rt], mid))
                insert(rt * 2 + 1, mid + 1, r, L, R, tree[rt]), tree[rt] = id;
            else
                insert(rt * 2, l, mid, L, R, id);
        }
        update(rt, l, r);
        return;
    }
    if (l > R || r < L)
        return;
    ll mid = (l + r) >> 1;
    insert(rt * 2, l, mid, L, R, id), insert(rt * 2 + 1, mid + 1, r, L, R, id);
    update(rt, l, r);
}

ll getans(ll rt, ll l, ll r, ll L, ll R)
{
    //printf("getans:%lld %lld %lld %lld %lld\n", rt, l, r, L, R);
    if (L <= l && r <= R)
        return mx[rt];
    if (l > R || r < L)
        return (ll)123456789123456789;
    ll mid = (l + r) >> 1;
    return min(min(calc(tree[rt], max(l, L)), calc(tree[rt], min(r, R))), min(getans(rt * 2, l, mid, L, R), getans(rt * 2 + 1, mid + 1, r, L, R)));
}

ll _lca(ll s, ll t)
{
    ll x = s, y = t;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        x = fa[top[x]];
    }
    if (dep[x] < dep[y])
        swap(x, y);
    return toroot[s] + toroot[t] - 2 * toroot[y];
}

ll lca(ll s, ll t)
{
    ll tmp = _lca(s, t);
    //printf("lca(%lld,%lld)=%d\n", s, t, tmp);
    return tmp;
}

bool isson(ll s, ll x)
{
    return in[s] >= in[x] && in[s] <= out[x];
}

void Modify(ll s, ll t, ll a, ll b1)
{
    ll x = s, y = t;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        ll dis = lca(s, top[x]);
        if (isson(s, x))
        {
            tot++;
            k[tot] = -a;
            b[tot] = a * toroot[top[x]] + a * dis + b1;
        }
        else
        {
            tot++;
            k[tot] = a;
            b[tot] = -a * toroot[top[x]] + a * dis + b1;
        }
        //printf("line[%lld] k=%lld b=%lld\n", tot, k[tot], b[tot]);
        insert(1, 1, n, in[top[x]], in[s], tot);
        x = fa[top[x]];
    }
    if (dep[x] < dep[y])
        swap(x, y);
    ll dis = lca(s, y);
    if (isson(s, x))
    {
        tot++;
        k[tot] = -a;
        b[tot] = a * toroot[y] + a * dis + b1;
    }
    else
    {
        tot++;
        k[tot] = a;
        b[tot] = -a * toroot[y] + a * dis + b1;
    }
    //printf("line[%lld] k=%lld b=%lld\n", tot, k[tot], b[tot]);
    insert(1, 1, n, in[y], in[x], tot);
}

ll Query(ll x, ll y)
{
    ll res = (ll)123456789123456789;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        res = min(res, getans(1, 1, n, in[top[x]], in[x]));
        x = fa[top[x]];
    }
    if (dep[x] < dep[y])
        swap(x, y);
    res = min(res, getans(1, 1, n, in[y], in[x]));
    return res;
}

int main()
{
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i < n; i++)
    {
        scanf("%lld%lld%lld", &u, &v, &w);
        addedge(u, v, w);
        addedge(v, u, w);
    }
    k[0] = 0, b[0] = (ll)123456789123456789;
    for (ll i = 1; i <= 4 * n; i++)
        mx[i] = (ll)123456789123456789;
    dfs1(1, 1, 1, 0);
    dfs2(1, 1, 1);
    //printf("%d\n",toroot[2]);
    for (ll i = 1; i <= m; i++)
    {
        scanf("%d", &cases);
        if (cases == 1)
        {
            ll b;
            scanf("%lld%lld%lld%lld", &s, &t, &a, &b);
            Modify(s, t, a, b);
        }
        else
        {
            scanf("%lld%lld", &s, &t);
            printf("%lld\n", Query(s, t));
        }
    }
    system("pause");
    return 0;
}