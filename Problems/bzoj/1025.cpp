#include <cstdio>
#include <cstdlib>
using namespace std;

int mark[1010], primetot, prime[1010], n, f[1010][1010];
typedef long long ll;

void getphi(int n)
{
    for (int i = 2; i <= n; i++)
    {
        if (!mark[i])
            prime[++primetot] = i;
        for (int j = 1; j <= primetot; j++)
            if (i * prime[j] > n)
                break;
            else
                mark[i * prime[j]] = true;
    }
}

int main()
{
    scanf("%d", &n);
    getphi(n);
    f[0][0] = 1;
    for (int i = 1; i <= primetot; i++)
    {
        for (int j = 0; j <= n; j++)
            f[i][j] = f[i - 1][j];
        for (int j = prime[i]; j <= n; j *= prime[i])
            for (int k = j; k <= n; k++)
                f[i][k] += f[i - 1][k - j];
    }
    ll ans = 0;
    for (int i = 0; i <= n; i++)
        ans += f[primetot][i];
    printf("%lld\n", ans);
    system("pause");
}