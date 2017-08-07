#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, m, a[310], b[310];
bool inblock[310][310];
int f[310][310][310];

int main()
{
    freopen("chess.in", "r", stdin);
    freopen("chess.out", "w", stdout);

    int MOD = 1000000007;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &a[i], &b[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            if (inblock[i][j])
                continue;
            for (int l = 1; l <= m && !inblock[i][j]; l++)
            {
                if (i >= a[l] && j <= b[l])
                    inblock[i][j] = inblock[j][i] = true;
            }
        }
    }
    f[0][0][0] = 1;
    for (int i = 0; i <= n; i++)
    {
        for (int k = 0; k <= i; k++)
        {
            for (int j = 0; j <= k; j++)
            {
                if (k == j && k != 0)
                    continue;
                f[i + 1][j][k] = (f[i + 1][j][k] + f[i][j][k]) % MOD;
                if (!inblock[j][i + 1])
                    f[i + 1][k][i + 1] = (f[i + 1][k][i + 1] + f[i][j][k]) % MOD;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            ans += f[n][j][i];
            ans %= MOD;
        }
    }
    printf("%d\n", ans);
    //system("pause");
    return 0;
}