#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
ll MOD = 1000003;
ll fac[1000013], inv[1000013];
ll n, l, r;
void init(ll MOD)
{
    fac[0] = 1;
    for (ll i = 1; i <= MOD; i++)
    {
        fac[i] = fac[i - 1] * i % MOD;
    }
    inv[1] = inv[0] = 1;
    for (ll i = 2; i < MOD; i++)
    {
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    }
    for (ll i = 1; i < MOD; i++)
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
    ll b, n, ANS = 0;
    init(MOD);
    scanf("%lld%lld", &n, &b);
    b = b + n;
    for (ll i = 1; i <= b; i++)
    {
        ANS = (ANS + lucas(i - 1, n - 1)) % MOD;
    }
    printf("%lld\n", ANS);
    system("pause");
    return 0;
}