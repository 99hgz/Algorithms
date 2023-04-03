#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int vis[25], n, m, p, u, v, f[25][25], w[25], l, iseg[1 << 21], cnt[1 << 21], s[1 << 21], invs[1 << 21];
int g[22][1 << 21], dp[22][1 << 21];
int MOD = 998244353, inv2 = 499122177;
ll pow(ll a, int b)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
void fwt(int *f)
{
    for (int i = 1; i < l; i <<= 1)
        for (int j = 0, m = i << 1; j < l; j += m)
            for (int k = 0; k < i; k++)
            {
                int l = f[j + k], r = f[i + j + k];
                f[i + j + k] = (l + r) % MOD;
            }
}

void ufwt(int *f)
{
    for (int i = 1; i < l; i <<= 1)
        for (int j = 0, m = i << 1; j < l; j += m)
            for (int k = 0; k < i; k++)
            {
                int l = f[j + k], r = f[i + j + k];
                f[i + j + k] = (ll)(r - l + MOD) % MOD;
            }
}

void dfs(int i, int sta)
{
    vis[i] = true;
    for (int j = 0; j < n; j++)
        if (!vis[j] && ((sta >> j) & 1) && (f[i][j]))
            dfs(j, sta);
}

int check(int sta)
{
    memset(vis, 0, sizeof vis);
    dfs(__builtin_ctz(sta), sta);
    for (int i = 0; i < n; i++)
        if (((sta >> i) & 1) && vis[i] == false)
            return 1;
    for (int i = 0; i < n; i++)
        if ((sta >> i) & 1)
        {
            int s = 0;
            for (int j = 0; j < n; j++)
                if ((sta >> j) & 1 && f[i][j])
                    s++;
            if (s & 1)
                return 1;
        }
    return 0;
}

int main()
{
    scanf("%d%d%d", &n, &m, &p);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        u--, v--;
        f[u][v] = f[v][u] = 1;
    }
    for (int i = 1; i <= n; i++)
        scanf("%d", &w[i - 1]);
    l = (1 << n);
    for (int i = 1; i < l; i++)
    {
        iseg[i] = check(i);
        for (int j = 0; j < n; j++)
            if ((i >> j) & 1)
            {
                cnt[i]++;
                s[i] += w[j];
            }
        s[i] = pow(s[i], p);
        invs[i] = pow(s[i], MOD - 2);
        //printf("%d %d %d\n", i, iseg[i], s[i]);
    }
    for (int j = 0; j < l; j++)
        if (iseg[j])
            g[cnt[j]][j] = s[j];
    for (int i = 1; i <= n; i++)
        fwt(g[i]);
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        fwt(dp[i - 1]);
        for (int j = 1; j <= i; j++)
            for (int k = 0; k < l; k++)
                dp[i][k] = (dp[i][k] + (ll)dp[i - j][k] * g[j][k] % MOD) % MOD;
        ufwt(dp[i]);
        for (int j = 0; j < l; j++)
            dp[i][j] = (ll)dp[i][j] * invs[j] % MOD;
    }
    printf("%d\n", dp[n][l - 1]);
    system("pause");
    return 0;
}