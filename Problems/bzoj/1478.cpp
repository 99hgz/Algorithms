#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int l[100], n, m, MOD;
ll pre[100], ipre[100], inv[100], ans, pw[100000], g[100][100];

void work(int rest, int least, int dep)
{
    if (rest == 0)
    {
        dep--;
        ll invl = 1, invb = 1, b = 0;
        for (int i = 1; i <= dep; i++)
        {
            if (l[i] != l[i - 1])
            {
                invb = invb * ipre[b] % MOD;
                b = 1;
            }
            else
                b++;
            invl = invl * inv[l[i]] % MOD;
        }
        invb = invb * ipre[b] % MOD;
        ll tmp = invl * invb % MOD;
        int lsum = 0;
        for (int i = 1; i <= dep; i++)
        {
            for (int j = 1; j < i; j++)
                lsum += g[l[i]][l[j]];
            lsum += l[i] / 2;
        }
        tmp = tmp * pw[lsum] % MOD;
        (ans += tmp) %= MOD;
        return;
    }
    for (int i = least; i <= rest; i++)
    {
        l[dep] = i;
        work(rest - i, i, dep + 1);
    }
}

int main()
{
    //scanf("%d%d%d", &n, &m, &MOD);
    scanf("%d", &n);
    m = 2, MOD = 997;
    for (int i = 0; i <= n; i++)
        g[i][0] = i;
    for (int i = 0; i <= n; i++)
        for (int j = 1; j <= i; j++)
            g[i][j] = g[j][i % j];
    for (int i = pw[0] = 1; i <= n * n / 2; i++)
        pw[i] = pw[i - 1] * m % MOD;
    inv[1] = inv[0] = pre[0] = pre[1] = ipre[1] = ipre[0] = 1;
    for (int i = 2; i <= n; i++)
        pre[i] = (ll)pre[i - 1] * i % MOD, inv[i] = (ll)(MOD - MOD / i) * inv[MOD % i] % MOD;
    for (int i = 2; i <= n; i++)
        ipre[i] = (ll)inv[i] * ipre[i - 1] % MOD;
    work(n, 1, 1);
    printf("%lld\n", ans);
    system("pause");
    return 0;
}