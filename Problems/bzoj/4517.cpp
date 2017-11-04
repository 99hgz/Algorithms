#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
ll MOD = 1000000007;
ll fac[1000010], inv[1000010], f[1000010];
ll n, l, m, r;
void init(ll MOD)
{
    fac[0] = 1;
    for (ll i = 1; i <= 1000010; i++)
    {
        fac[i] = fac[i - 1] * i % MOD;
    }
    inv[1] = inv[0] = 1;
    for (ll i = 2; i < 1000010; i++)
    {
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    }
    for (ll i = 1; i < 1000010; i++)
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
    scanf("%lld", &t);
    init(MOD);
    f[0] = 1;
    f[1] = 0;
    f[2] = 1;
    for (int i = 3; i <= 1000005; i++)
    {
        f[i] = (i - 1) * (f[i - 1] + f[i - 2]) % MOD;
    }
    while (t--)
    {
        scanf("%lld%lld", &n, &m);
        printf("%lld\n", (lucas(n, m) * f[n - m]) % MOD);
    }
    system("pause");
    return 0;
}