#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int dp[101][101];
int t[101][101];
int rmb[101], rp[101], time1[101];
int main()
{
    int i, j, k, n, m, r;
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        scanf("%d%d%d", &rmb[i], &rp[i], &time1[i]);
    scanf("%d%d", &m, &r);
    for (k = 1; k <= n; k++)
        for (i = m; i >= rmb[k]; i--)
            for (j = r; j >= rp[k]; j--)
            {
                if (dp[i][j] < dp[i - rmb[k]][j - rp[k]] + 1)
                {
                    dp[i][j] = dp[i - rmb[k]][j - rp[k]] + 1;
                    t[i][j] = t[i - rmb[k]][j - rp[k]] + time1[k];
                }
                else if (dp[i][j] == dp[i - rmb[k]][j - rp[k]] + 1)
                    t[i][j] = min(t[i][j], t[i - rmb[k]][j - rp[k]] + time1[k]);
            }
    printf("%d\n", t[m][r]);
    //system("pause");
    return 0;
}
