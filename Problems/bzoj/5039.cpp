#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 200010
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ll long long
ll sum[N * 4];
ll add[N * 4], mul[N * 4], P;
void pushUp(ll rt) { sum[rt] = (sum[rt << 1] + sum[rt << 1 | 1]) % P; }
void build(ll l, ll r, ll rt)
{
    add[rt] = 0;
    mul[rt] = 1;
    if (l == r)
    {
        scanf("%lld", &sum[rt]);
        return;
    }
    ll m = (l + r) >> 1;
    build(lson);
    build(rson);
    pushUp(rt);
}
void pushDown(ll rt, ll d)
{
    if (add[rt] == 0 && mul[rt] == 1)
        return;
    mul[rt << 1] = (mul[rt << 1] * mul[rt]) % P;
    add[rt << 1] = (((add[rt << 1] * mul[rt]) % P) + add[rt]) % P;
    mul[rt << 1 | 1] = (mul[rt << 1 | 1] * mul[rt]) % P;
    add[rt << 1 | 1] = (((add[rt << 1 | 1] * mul[rt]) % P) + add[rt]) % P;
    sum[rt << 1 | 1] =
        ((sum[rt << 1 | 1] * mul[rt] % P) + ((ll)(d >> 1) * add[rt] % P)) % P;
    sum[rt << 1] =
        ((sum[rt << 1] * mul[rt] % P) + ((ll)(d - (d >> 1)) * add[rt] % P)) % P;
    mul[rt] = 1;
    add[rt] = 0;
}
void update(ll L, ll R, ll c, ll l, ll r, ll rt)
{
    if (L <= l && R >= r)
    {
        add[rt] += c;
        sum[rt] += (r - l + 1) * c;
        add[rt] %= P;
        sum[rt] %= P;
        return;
    }
    pushDown(rt, r - l + 1);
    ll m = (l + r) >> 1;
    if (L <= m)
        update(L, R, c, lson);
    if (R > m)
        update(L, R, c, rson);
    pushUp(rt);
}
void update2(ll L, ll R, ll c, ll l, ll r, ll rt)
{
    if (L <= l && R >= r)
    {
        add[rt] *= c;
        mul[rt] *= c;
        sum[rt] *= c;
        add[rt] %= P;
        mul[rt] %= P;
        sum[rt] %= P;
        return;
    }
    pushDown(rt, r - l + 1);
    ll m = (l + r) >> 1;
    if (L <= m)
        update2(L, R, c, lson);
    if (R > m)
        update2(L, R, c, rson);
    pushUp(rt);
}

ll query(ll L, ll R, ll l, ll r, ll rt)
{
    if (L <= l && R >= r)
    {
        return sum[rt] % P;
    }
    pushDown(rt, r - l + 1);
    ll m = (l + r) >> 1;
    ll ret = 0;
    if (L <= m)
        ret += query(L, R, lson);
    if (R > m)
        ret += query(L, R, rson);
    return (ret % P);
}
int main()
{

    ll n, q, a, b, c, s;
    scanf("%lld%lld", &n, &P);
    build(1, n, 1);
    scanf("%lld", &q);
    while (q--)
    {
        scanf("%lld", &s);
        if (s == 2)
        {
            scanf("%lld%lld%lld", &a, &b, &c);
            update(a, b, c, 1, n, 1);
        }
        else if (s == 1)
        {
            scanf("%lld%lld%lld", &a, &b, &c);
            update2(a, b, c, 1, n, 1);
        }
        else if (s == 3)
        {
            scanf("%lld%lld", &a, &b);
            printf("%lld\n", query(a, b, 1, n, 1));
        }
    }
    // system("pause");
    return 0;
}
