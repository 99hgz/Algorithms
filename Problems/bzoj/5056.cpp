#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int a[100][100], mp[100][100], n, tmp;
ll ans;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            scanf("%1d", &tmp);
            a[i][j] = tmp;
            mp[i][j] = ((tmp == 0 && i != j) ? 100 : tmp);
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                mp[j][k] = min(mp[j][k], mp[j][i] + mp[i][k]);
    ans = 1;
    for (int i = 2; i <= n; i++)
    {
        int hh = 0;
        for (int j = 1; j <= n; j++)
        {
            if (a[i][j] && mp[1][i] == mp[1][j] + a[i][j])
                hh++;
        }
        ans *= (ll)hh;
        ans %= (ll)1000000007;
    }
    printf("%lld\n", ans);
    system("pause");
    return 0;
}