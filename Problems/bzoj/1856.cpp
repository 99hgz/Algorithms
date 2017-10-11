#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
ll MOD = 20100403;
ll fac[2000013], inv[2000013];
ll n, l, r, m;
void init(ll MOD, ll n)
{
    fac[0] = 1;
    for (ll i = 1; i <= n; i++)
    {
        fac[i] = fac[i - 1] * i % MOD;
    }
    inv[1] = inv[0] = 1;
    for (ll i = 2; i < n; i++)
    {
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    }
    for (ll i = 1; i < n; i++)
    {
        inv[i] = inv[i] * inv[i - 1] % MOD; //阶乘求逆
    }
}

ll lucas(ll n, ll m)
{
    if (m > n)
        return 0;
    if (n < MOD && m < MOD)
        return fac[n] * inv[n - m] % MOD * inv[m] % MOD;
    return lucas(n % MOD, m % MOD) * lucas(n / MOD, m / MOD) % MOD;
}

int main()
{
    ll t;
    init(MOD, 2000010);
    scanf("%lld%lld", &n, &m);
    printf("%lld\n", (lucas(n + m, m) - lucas(n + m, m - 1) + MOD) % MOD);

    system("pause");
    return 0;
}