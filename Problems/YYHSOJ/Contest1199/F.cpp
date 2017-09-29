#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>
using namespace std;
typedef long long ll;

ll pre[110], s[110];
ll f[110][110];
ll point[110][110];
ll n;

ll get_min_score()
{
    ll i, j, k;
    for (i = 1; i <= n; i++)
        f[i][i] = 0, point[i][i] = i;
    for (j = 1; j <= n; j++)
    {
        for (i = 1; i <= n - j; i++)
        {
            f[i][i + j] = INT_MAX;
            for (k = point[i][i + j - 1]; k <= point[i + 1][i + j]; k++)
            {
                int tmp = f[i][k] - pre[i - 1] + f[k + 1][i + j] + pre[i + j];
                if (tmp < f[i][i + j])
                {
                    f[i][i + j] = tmp;
                    point[i][i + j] = k;
                }
            }
        }
    }
    return f[1][n];
}

int main()
{
    ll i, j, k;
    ll global_min = INT_MAX;
    scanf("%lld", &n);
    for (i = 1; i <= n; i++)
        scanf("%lld", &s[i]);
    for (i = 1; i < n; i++)
    {
        swap(s[i], s[i + 1]);
        pre[0] = 0;
        for (k = 1; k <= n; k++)
        {
            pre[k] = pre[k - 1] + s[k];
        }
        global_min = min(global_min, get_min_score());
        swap(s[i], s[i + 1]);
    }
    printf("%lld\n", global_min);
    //system("pause");
    return 0;
}