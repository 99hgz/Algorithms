#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, dp[50], ans;
ll v;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &v);
        int tmp = 0;
        for (ll j = 1; j <= 31; j++)
            if ((v >> j) & 1)
                tmp = max(tmp, dp[j] + 1);
        for (ll j = 1; j <= 31; j++)
            if ((v >> j) & 1)
                dp[j] = max(dp[j], tmp);
        ans = max(ans, tmp);
    }
    printf("%d", ans);
    while (1)
    {
    }
}