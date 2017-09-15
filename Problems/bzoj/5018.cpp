#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

ll n, m, k[150], c[150], total, f[130][199 * 10 * 130];

int main()
{
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld", &k[i]);
    }
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld", &c[i]);
        total += k[i] * c[i];
    }
    for (ll i = 0; i <= total; i++)
    {
        f[0][i] = 1;
    }
    for (ll i = 1; i <= n; i++)
    {
        for (ll j = 0; j <= total; j++)
        {
            f[i][j] = max(f[i][j], f[i - 1][j]);
            for (ll l = 1; l <= k[i]; l++)
            {
                if (l * c[i] > j)
                    break;
                f[i][j] = max(f[i][j], f[i - 1][j - l * c[i]] * l);
            }
        }
    }
    for (ll i = 0; i <= total; i++)
    {
        if (f[n][i] > m)
        {
            printf("%lld\n", i);
            break;
        }
    }
    system("pause");
    return 0;
}