#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
ll n, m, isntzero, sum, ans;
ll belong[200], col[110], row[110], a[110][110];
bool map[110][110], used[110];

bool find(ll x)
{
    for (ll j = 1; j <= n; j++)
    {
        if (map[j][x] && (!used[j]))
        {
            used[j] = true;
            if ((belong[j] == 0) || (find(belong[j])))
            {
                belong[j] = x;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= n; i++)
    {
        for (ll j = 1; j <= m; j++)
        {
            scanf("%lld", &a[i][j]);
            if (a[i][j] != 0)
                isntzero++;
            row[i] = max(row[i], a[i][j]);
            col[j] = max(col[j], a[i][j]);
            sum += a[i][j];
        }
    }
    for (ll i = 1; i <= n; i++)
    {
        for (ll j = 1; j <= m; j++)
        {
            if ((row[i] == col[j]) && (a[i][j] != 0))
            {
                map[i][j] = true;
            }
        }
    }
    for (ll i = 1; i <= m; i++)
    {
        memset(used, 0, sizeof used);
        find(i);
        if (col[i] != 0)
        {
            ans += col[i];
            isntzero--;
        }
    }
    for (ll i = 1; i <= n; i++)
    {
        if (!belong[i] && (row[i] != 0))
        {
            ans += row[i];
            isntzero--;
        }
    }
    printf("%lld\n", sum - ans - isntzero);
    system("pause");
    return 0;
}