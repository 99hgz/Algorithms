#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
ll f[110][110];
ll sum[110];
int a[110];
int i, k, j, n, m;
int main()
{
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        sum[i] = sum[i - 1] + a[i];
        f[i][0] = sum[i];
    }
    for (i = 1; i <= n; i++)
    {
        for (k = 1; k <= min(i - 1, m); k++)
        {
            for (j = 1; j <= (i - 1); j++)
            {
                f[i][k] = max(f[i][k], f[j][k - 1] * (sum[i] - sum[j]));
            }
        }
    }
    printf("%d", f[n][m]);
    //system("pause");
    return 0;
}