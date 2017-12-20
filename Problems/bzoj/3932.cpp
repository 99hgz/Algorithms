#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

ll tot;
struct TREE
{
    ll num, lson, rson;
    ll sum;
} Tree[2000010];
ll n, m, s[100010], e[100010], p[100010];
struct TIME
{
    ll t, base, id;
} ttp[200010];

bool cmp(TIME a, TIME b)
{
    return a.t < b.t;
}
ll k, x, a, b, c, head, Root[10000010];

void modify(ll &rt, ll l, ll r, ll x, ll base)
{
    ll thisrt = ++tot;
    Tree[thisrt] = Tree[rt];
    rt = thisrt;
    ll mid = (l + r) >> 1;
    Tree[thisrt].num += base, Tree[thisrt].sum += x * base;
    if (l == r)
        return;
    if (x <= mid)
        modify(Tree[thisrt].lson, l, mid, x, base);
    else
        modify(Tree[thisrt].rson, mid + 1, r, x, base);
}

ll query(ll rt, ll l, ll r, ll x, ll sum)
{
    if (l == r)
        return sum + x * l;
    ll mid = (l + r) >> 1;
    if (Tree[Tree[rt].lson].num >= x)
        return query(Tree[rt].lson, l, mid, x, sum);
    else
        return query(Tree[rt].rson, mid + 1, r, x - Tree[Tree[rt].lson].num, sum + Tree[Tree[rt].lson].sum);
}

int main()
{
    scanf("%lld%lld", &m, &n);
    ll MAXP = 0, pos = 0;
    for (ll i = 1; i <= m; i++)
    {
        scanf("%lld%lld%lld", &s[i], &e[i], &p[i]);
        MAXP = max(MAXP, p[i]);
        ttp[++pos] = (TIME){s[i], 1, i};
        ttp[++pos] = (TIME){e[i] + 1, -1, i};
    }
    sort(ttp + 1, ttp + 1 + pos, cmp);
    ll head = 1;
    for (ll i = 1; i <= 100010; i++)
    {
        Root[i] = Root[i - 1];
        while (ttp[head].t == i)
        {
            modify(Root[i], 1, MAXP, p[ttp[head].id], ttp[head].base);
            head++;
        }
    }
    ll pre = 1;
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld%lld%lld%lld", &x, &a, &b, &c);
        k = 1 + (a * pre + b) % c;
        //printf("true:%d\n", k);
        if (k >= Tree[Root[x]].num)
            pre = Tree[Root[x]].sum;
        else
            pre = query(Root[x], 1, MAXP, k, 0);
        printf("%lld\n", pre);
    }
    // system("pause");
    return 0;
}