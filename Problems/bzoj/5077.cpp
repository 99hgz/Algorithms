#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

ll in[500010], out[500010], timestamp, n, m, c0, cases, fr, id, x, y, z, c;
struct PL
{
    ll x, c, k, b, id;
} pl[500010];
vector<ll> edges[500010];
vector<ll> appeared[500010];
void addedge(ll u, ll v)
{
    edges[u].push_back(v);
}

struct LINE
{
    ll k, b;
};

bool canout(LINE a, LINE b, LINE c)
{
    if (b.k == c.k)
        return b.b >= c.b;
    return (b.b - a.b) * (a.k - c.k) > (a.k - b.k) * (c.b - a.b);
}
ll ans[500010];
struct hall
{
    vector<LINE> vec;
    ll now1;
    hall() : now1(0){};
    void insert(ll k, ll b)
    {
        if (vec.size() <= 1)
            vec.push_back((LINE){k, b});
        else
        {
            LINE tmp = (LINE){k, b};
            while (vec.size() > 1 && canout(vec[vec.size() - 2], vec[vec.size() - 1], tmp))
                vec.pop_back();
            vec.push_back(tmp);
        }
    }
    ll calc(ll x, ll k)
    {
        return vec[k].k * x + vec[k].b;
    }
    ll query(ll x)
    {
        if (vec.size() == 0)
            return 0x3f3f3f3f3f3f3f3f;
        while ((now1 < (vec.size()) - 1) && (calc(x, now1) > calc(x, now1 + 1)))
            now1++;
        return calc(x, now1);
    }
} Tree[500010 * 4];

void insert(ll rt, ll l, ll r, ll L, ll R, ll id)
{
    if (L <= l && r <= R)
    {
        //printf("Tree %lld l=%lld r=%lld inserted %lld %lld\n", rt, l, r, pl[id].k, pl[id].b);
        Tree[rt].insert(pl[id].k, pl[id].b);
        return;
    }
    if (l > R || r < L)
        return;
    ll mid = (l + r) >> 1;
    insert(rt * 2, l, mid, L, R, id);
    insert(rt * 2 + 1, mid + 1, r, L, R, id);
}

void dfs(ll x)
{
    in[x] = ++timestamp;
    //printf("dfsin:%lld=%lld\n", x, in[x]);
    for (int it = 0; it < edges[x].size(); it++)
        dfs(edges[x][it]);
    out[x] = timestamp;
    //printf("dfsout:%lld=%lld\n", x, out[x]);
}

bool cmp(PL a, PL b)
{
    return a.k > b.k;
}

bool cmp2(ll a, ll b)
{
    return in[a] < in[b];
}
struct QRY
{
    ll s, x, id;
} qry[500010];
bool cmp3(QRY a, QRY b)
{
    return a.x < b.x;
}

ll query(ll rt, ll l, ll r, ll pos, ll x)
{
    ll res = Tree[rt].query(x);
    if (l == r)
        return res;
    ll mid = (l + r) >> 1;
    if (pos <= mid)
        res = min(res, query(rt * 2, l, mid, pos, x));
    else
        res = min(res, query(rt * 2 + 1, mid + 1, r, pos, x));
    return res;
}

int main()
{
    freopen("D:/tmp/travel3.in", "r", stdin);
    freopen("D:/tmp/travel3.out", "w", stdout);

    scanf("%lld%lld%lld", &n, &m, &c0);
    for (ll i = 2; i <= n; i++)
    {
        scanf("%lld", &cases);
        if (cases == 0)
        {
            scanf("%lld%lld%lld%lld%lld%lld", &fr, &id, &x, &y, &z, &c);
            pl[id] = (PL){x, c};
            fr++;
            addedge(fr, i);
            appeared[id].push_back(i);
        }
        else
        {
            scanf("%lld%lld", &fr, &id);
            fr++;
            addedge(fr, i);
            appeared[id].push_back(i);
        }
    }
    dfs(1);
    for (ll i = 1; i < n; i++)
    {
        pl[i].k = -2 * pl[i].x;
        pl[i].b = pl[i].x * pl[i].x + pl[i].c;
        pl[i].id = i;
    }
    sort(pl + 1, pl + n, cmp);
    for (ll i = 1; i < n; i++)
    {
        ll id = pl[i].id;
        if (appeared[id].size() == 0)
            continue;
        sort(appeared[id].begin(), appeared[id].end(), cmp2);
        ll head = in[appeared[id][0]], tail = out[appeared[id][0]];
        //printf("insert:%lld\n", appeared[id][0]);
        for (ll it = 1; it < appeared[id].size(); it++)
            insert(1, 1, n, head, in[appeared[id][it]] - 1, i),
                head = out[appeared[id][it]] + 1;
        insert(1, 1, n, head, tail, i);
    }
    for (ll i = 1; i <= m; i++)
    {
        scanf("%lld%lld", &qry[i].s, &qry[i].x);
        qry[i].s++;
        qry[i].id = i;
    }
    sort(qry + 1, qry + 1 + m, cmp3);
    for (ll i = 1; i <= m; i++)
    {
        //printf("query %lld from %lld\n", qry[i].id, qry[i].x);
        ans[qry[i].id] = min(query(1, 1, n, in[qry[i].s], qry[i].x) + qry[i].x * qry[i].x, qry[i].x * qry[i].x + c0);
    }
    for (ll i = 1; i <= m; i++)
        printf("%lld\n", ans[i]);
    return 0;
}