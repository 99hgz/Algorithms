#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

ll n, z;
struct Node
{
    ll d, a, i, plus;
} emy[100010];
ll P[100010], D[100010], num, ans[100010], dnum, pnum;

bool cmp(ll a, ll b)
{
    if (emy[a].d == emy[b].d)
        return emy[a].a > emy[b].a;
    else
        return emy[a].d < emy[b].d;
}

bool cmp1(ll a, ll b)
{
    if (emy[a].a == emy[b].a)
        return emy[a].d < emy[b].d;
    else
        return emy[a].a > emy[b].a;
}

void fail()
{
    printf("NIE\n");
}

int main()
{
    scanf("%lld%lld", &n, &z);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld%lld", &emy[i].d, &emy[i].a);
        emy[i].i = i;
        emy[i].plus = emy[i].a - emy[i].d;
        if (emy[i].plus > 0)
            P[++pnum] = i;
        else
            D[++dnum] = i;
    }
    sort(P + 1, P + 1 + pnum, cmp);
    sort(D + 1, D + 1 + dnum, cmp1);
    for (ll i = 1; i <= pnum; i++)
    {
        z -= emy[P[i]].d;
        if (z <= 0)
        {
            fail();
            return 0;
        }
        z += emy[P[i]].a;
        ans[++num] = emy[P[i]].i;
    }
    for (ll i = 1; i <= dnum; i++)
    {
        z -= emy[D[i]].d;
        if (z <= 0)
        {
            fail();
            return 0;
        }
        z += emy[D[i]].a;
        ans[++num] = emy[D[i]].i;
    }
    printf("TAK\n");
    for (ll i = 1; i <= num; i++)
    {
        printf("%lld ", ans[i]);
    }
    system("pause");
    return 0;
}