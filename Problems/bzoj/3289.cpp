#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

ll n, m, len;
ll d[50010], c[50010], part[50010];
ll ans;

struct node
{
    ll l, r, id;
    ll a;
} que[50010];
ll alreadyinset;
ll tree[50010];
typedef long long ll;

ll lowbit(ll x)
{
    return x & -x;
}
ll sum(ll end)
{
    ll ans = 0;
    while (end > 0)
    {
        ans += tree[end];
        end -= lowbit(end);
    }
    return ans;
}
void update(ll pos, ll num)
{
    while (pos < 50010)
    {
        tree[pos] += num;
        pos += lowbit(pos);
    }
}

bool cmp(node a, node b)
{
    if (part[a.l] == part[b.l])
        return a.r < b.r;
    return part[a.l] < part[b.l];
}
bool cmpwithid(node a, node b)
{
    return a.id < b.id;
}
void update1(ll i, ll cases)
{
    ll tmp = 0;
    if (cases == 1)
    {
        alreadyinset++;
        update(c[i], 1);
        tmp = sum(c[i]);
        ans += alreadyinset - tmp;
    }
    else if (cases == 2)
    {
        alreadyinset--;
        update(c[i], -1);
        tmp = sum(c[i]);
        ans -= alreadyinset - tmp;
    }
    else if (cases == 3)
    {
        alreadyinset++;
        update(c[i], 1);
        tmp = sum(c[i] - 1);
        ans += tmp;
    }
    else
    {
        alreadyinset--;
        update(c[i], -1);
        tmp = sum(c[i] - 1);
        ans -= tmp;
    }
}

int main()
{
    scanf("%lld", &n);
    len = floor(sqrt(n));
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld", &c[i]);
        d[i] = c[i];
        part[i] = (i - 1) / len + 1;
    }
    sort(d + 1, d + 1 + n);
    for (ll i = 1; i <= n; i++)
    {
        c[i] = lower_bound(d + 1, d + 1 + n, c[i]) - d;
    }
    scanf("%lld", &m);
    for (ll i = 1; i <= m; i++)
    {
        scanf("%lld%lld", &que[i].l, &que[i].r);
        que[i].id = i;
    }
    sort(que + 1, que + m + 1, cmp);
    ll l = 1, r = 0;
    alreadyinset = 0;
    for (ll i = 1; i <= m; i++)
    {
        for (; r < que[i].r; r++)
            update1(r + 1, 1); //in
        for (; r > que[i].r; r--)
            update1(r, 2); //out
        for (; l > que[i].l; l--)
            update1(l - 1, 3); //in
        for (; l < que[i].l; l++)
            update1(l, 4); //out
        if (que[i].l == que[i].r)
        {
            que[i].a = 0;
            continue;
        }
        que[i].a = ans;
    }
    sort(que + 1, que + 1 + m, cmpwithid);
    for (ll i = 1; i <= m; i++)
    {
        printf("%lld\n", que[i].a);
    }
    system("pause");
    return 0;
}