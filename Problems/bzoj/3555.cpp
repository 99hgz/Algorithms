#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef unsigned long long ll;

ll n, m, size;
ll BASE1 = 107;
char A[300];
ll f[30100][300], pow1[300], a[30100], cnt, ans;

int main()
{
    scanf("%lld%lld%lld", &n, &m, &size);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%s", A + 1);
        for (ll j = 1; j <= m; j++)
        {
            f[i][j] = f[i][j - 1] * BASE1 + A[j];
        }
    }
    pow1[0] = 1;
    for (ll i = 1; i <= m; i++)
    {
        pow1[i] = pow1[i - 1] * BASE1;
    }
    for (ll j = 1; j <= m; j++)
    {
        for (ll i = 1; i <= n; i++)
        {
            a[i] = f[i][m] - f[i][j] * pow1[m - j] + f[i][j - 1] * pow1[m - j + 1];
        }
        sort(a + 1, a + n + 1);
        cnt = 0;
        for (ll i = 2; i <= n; i++)
        {
            if (a[i] == a[i - 1])
                cnt++;
            else
                cnt = 0;
            ans += cnt;
        }
    }
    printf("%lld\n", ans);
    system("pause");
    return 0;
}