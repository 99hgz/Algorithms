#include <cstdio>
using namespace std;
typedef long long ll;
ll dp[20][20][20][20][20][6];
int k, n, num[10], v;
ll MOD = 1000000007;
ll dfs(int a, int b, int c, int d, int e, int last)
{
    if (!a && !b && !c && !d && !e)
        return 1;
    if (dp[a][b][c][d][e][last])
        return dp[a][b][c][d][e][last];
    int tmp = 0;
    if (a)
        tmp = (tmp + (ll)(a - (last == 2)) * dfs(a - 1, b, c, d, e, 1)) % MOD;
    if (b)
        tmp = (tmp + (ll)(b - (last == 3)) * dfs(a + 1, b - 1, c, d, e, 2)) % MOD;
    if (c)
        tmp = (tmp + (ll)(c - (last == 4)) * dfs(a, b + 1, c - 1, d, e, 3)) % MOD;
    if (d)
        tmp = (tmp + (ll)(d - (last == 5)) * dfs(a, b, c + 1, d - 1, e, 4)) % MOD;
    if (e)
        tmp = (tmp + (ll)(e)*dfs(a, b, c, d + 1, e - 1, 5)) % MOD;
    return dp[a][b][c][d][e][last] = tmp;
}

int main()
{
    scanf("%d", &k);
    for (int i = 1; i <= k; i++)
    {
        scanf("%d", &v);
        num[v]++;
    }
    printf("%lld", dfs(num[1], num[2], num[3], num[4], num[5], 0));
    while (1)
    {
    }
}