#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

ll n, x[1010], y[1010], r[1010], vis[1010];

ll sqr(ll x)
{
    return x * x;
}

bool bh(ll i, ll j)
{
    if ((sqr(x[i] - x[j]) + sqr(y[i] - y[j])) <= sqr(r[i]))
        return true;
    return false;
}

int main()
{
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)
        scanf("%lld%lld%lld", &x[i], &y[i], &r[i]);
    for (ll i = 1; i <= n; i++)
    {
        for (ll j = 1; j <= n; j++)
        {
            if (i == j)
                continue;
            if ((r[i] > r[j]) && bh(i, j))
                vis[j]++;
        }
    }
    ll ans = 0;
    for (ll i = 1; i <= n; i++)
    {
        if (vis[i] == 0)
            ans += r[i] * r[i];
        else
        {
            if (vis[i] & 1)
                ans += r[i] * r[i];
            else
                ans -= r[i] * r[i];
        }
    }
    //printf("%d\n", ans);
    printf("%.8lf\n", 3.141592653589 * ans);
    system("pause");
    return 0;
}