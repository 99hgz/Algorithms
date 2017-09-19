#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, k, f[1010][1010], g[1010][1010];
int MOD = 10000;

int main()
{
    scanf("%d%d", &n, &k);
    f[1][0] = 1;
    for (int i = 0; i <= k; i++)
    {
        g[1][i] = 1;
    }

    for (int i = 2; i <= n; i++)
    {
        for (int j = 0; j <= k; j++)
        {
            f[i][j] = (g[i - 1][j] - (j >= i ? g[i - 1][j - i] : 0) + MOD) % MOD;
            g[i][j] = ((j > 0 ? g[i][j - 1] : 0) + f[i][j]) % MOD;
        }
    }
    printf("%d\n", f[n][k]);
    system("pause");
    return 0;
}