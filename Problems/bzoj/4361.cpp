#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

ll P = 1000000007;
int BIT[2010][2010], Hash[2010], a[2010], n;
ll dp[2010], ans, fac[2010], f[2010][2010];

int query(int id, int x)
{
    int res = 0;
    for (; x; x -= x & (-x))
        res = (res + BIT[id][x]) % P;
    return res;
}

void add(int id, int x, int v)
{
    for (; x <= n; x += x & (-x))
        BIT[id][x] = (BIT[id][x] + v) % P;
}

void init()
{
    fac[0] = 1;
    for (int i = 1; i <= n; i++)
        fac[i] = fac[i - 1] * i % P;
}

int main()
{
    scanf("%d", &n);
    init();
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        Hash[i] = a[i];
    }
    sort(Hash + 1, Hash + 1 + n);
    int tn = unique(Hash + 1, Hash + 1 + n) - Hash - 1;
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(Hash + 1, Hash + 1 + tn, a[i]) - Hash;
    f[1][1] = 1;
    add(1, a[1], 1);
    for (int i = 2; i <= n; i++)
    {
        for (int j = 2; j <= i; j++)
            f[i][j] = query(j - 1, a[i]);

        f[i][1] = 1;
        add(1, a[i], 1);
        for (int j = 2; j <= i; j++)
            add(j, a[i], f[i][j]);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            dp[i] = (dp[i] + f[j][i]) % P;
        //printf("%lld\n", dp[i]);
    }
    for (int i = 1; i <= n; i++)
        ans = (ans + dp[i] * fac[n - i]) % P;
    for (int i = 2; i <= n; i++)
        ans = (((ans - dp[i] * i % P * fac[n - i] % P) % P) + P) % P;
    printf("%lld\n", ans);
    system("pause");
    return 0;
}