#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
ll ans, n, m;

ll phi(ll n)
{
    ll x = n;
    for (int i = 2; i <= m; i++)
    {
        if (n % i == 0)
            x = x / i * (i - 1);
        while (n % i == 0)
            n /= i;
    }
    if (n > 1)
        x = x / n * (n - 1);
    return x;
}

int main()
{
    scanf("%lld", &n);
    m = sqrt(n);
    for (ll i = 1; i <= m; i++)
    {
        if (n % i == 0)
        {
            ans += (i)*phi(n / i);
            if (i * i < n)
                ans += (n / i) * phi(i);
        }
    }
    printf("%lld\n", ans);
    system("pause");
    return 0;
}