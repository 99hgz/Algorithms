#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, m, k, ans, f[310][160][22][22];
int MOD = 12345678;
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    f[0][0][0][0] = 1;
    for (int i = 0; i < n + m; i++)
        for (int j = 0; j <= n; j++)
            for (int p = 0; p <= k; p++)
                for (int q = 0; q <= k; q++)
                {
                    (f[i + 1][j + 1][p + 1][max(q - 1, 0)] += f[i][j][p][q]) %= MOD;
                    (f[i + 1][j][max(p - 1, 0)][q + 1] += f[i][j][p][q]) %= MOD;
                }
    for (int p = 0; p <= k; p++)
        for (int q = 0; q <= k; q++)
            (ans += f[n + m][n][p][q]) %= MOD;
    printf("%d\n", ans);
    system("pause");
    return 0;
}