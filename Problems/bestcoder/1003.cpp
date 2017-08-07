#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
ll now;
ll n, m, a[100010], b[100010], k1[1010], p[1010], f[12][2010], ans;
inline ll read()
{
    ll data = 0, w = 1;
    char ch = 0;
    while (ch != '-' && (ch < '0' || ch > '9'))
        ch = getchar();
    if (ch == '-')
        w = -1, ch = getchar();
    while (ch >= '0' && ch <= '9')
        data = data * 10 + ch - '0', ch = getchar();
    return data * w;
}
int main()
{
    while (~scanf("%lld%lld", &n, &m))
    {
        ll ans = 0;
        for (ll i = 1; i <= n; i++)
        {
            a[i] = read();
            b[i] = read();
            //scanf("%lld%lld", &a[i], &b[i]);
        }
        for (ll i = 1; i <= m; i++)
        {
            k1[i] = read();
            p[i] = read();
            //scanf("%lld%lld", &k1[i], &p[i]);
        }
        for (int i = 0; i <= 10; i++)
        {
            for (int j = 1; j <= 1000; j++)
            {
                f[i][j] = 1 << 29;
            }
        }
        for (ll i = 0; i <= 10; i++)
        {
            f[i][0] = 0;
            for (ll j = 1; j <= m; j++)
            {
                for (ll k = 1; k <= 1000; k++)
                {
                    if ((p[j] > i))
                        f[i][k] = min(f[i][k], f[i][max(k - (p[j] - i), (ll)0)] + k1[j]);
                }
            }
        }
        bool flag = false;
        for (ll i = 1; i <= n; i++)
        {
            if (f[b[i]][a[i]] == 1 << 29)
            {
                flag = true;
                break;
            }
            ans += f[b[i]][a[i]];
        }
        if (flag)
            printf("-1\n");
        else
            printf("%lld\n", ans);
    }
    system("pause");
    return 0;
}
