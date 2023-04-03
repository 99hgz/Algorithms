#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int m, p, n;
ll t, MOD, e0[2000010], b[2000010], gx[2000010];
int cnt[2000010];

ll mt(ll x, ll y) //ll*ll
{
    x = ((x * y - ((ll)((long double)x / MOD * y)) * MOD) % MOD + MOD) % MOD;
    return x;
}

void fwt(ll *f)
{
    for (int d = 1; d < n; d <<= 1)
        for (int j = 0, m = d << 1; j < n; j += m)
            for (int i = 0; i < d; i++)
            {
                ll x = f[j + i], y = f[j + i + d];
                f[j + i] = (x + y) % MOD;
                f[j + i + d] = (x - y + MOD) % MOD;
            }
}

ll pow(ll a, ll b, ll c)
{
    ll res = c;
    while (b)
    {
        if (b & 1)
            res = mt(res, a);
        a = mt(a, a);
        b >>= 1;
    }
    return res;
}

int main()
{
    scanf("%d%I64d%d", &m, &t, &p);
    n = 1 << m;
    MOD = (ll)p * n;
    for (int i = 0; i < n; i++)
        scanf("%I64d", &e0[i]);
    for (int i = 0; i <= m; i++)
        scanf("%I64d", &b[i]);
    for (int i = 0; i < n; i++)
    {
        cnt[i] = cnt[i >> 1] + (i & 1);
        gx[i] = b[cnt[i]];
    }
    fwt(e0), fwt(gx);
    for (int i = 0; i < n; i++)
        e0[i] = pow(gx[i], t, e0[i]);
    fwt(e0);
    MOD = p;
    for (int i = 0; i < n; i++)
        printf("%I64d\n", ((e0[i] / n % MOD) + MOD) % MOD);
    //system("pause");
    return 0;
}