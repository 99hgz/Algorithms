#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

ll n, m, a[100010], sum[100010], f[3010][3010], q[3010];
ll sqr(ll x)
{
    return x * x;
}
double slope(ll id, ll i, ll j)
{
    return (double)(f[id][j] + sqr(sum[j]) - f[id][i] - sqr(sum[i])) / (double)(sum[j] - sum[i]);
}

int main()
{
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
        sum[i] = sum[i - 1] + a[i];
    }
    for (ll i = 1; i <= n; i++)
        f[1][i] = sqr(sum[i]);

    for (ll i = 2; i <= m; i++)
    {
        ll head = 1, tail = 1;
        for (ll j = 1; j <= n; j++)
        {
            while (head < tail && slope(i - 1, q[head], q[head + 1]) < (double)2 * sum[j])
                head++;
            f[i][j] = f[i - 1][q[head]] + sqr(sum[j] - sum[q[head]]);
            while (head < tail && slope(i - 1, q[tail], j) < slope(i - 1, q[tail - 1], q[tail]))
                tail--;
            q[++tail] = j;
        }
    }
    printf("%lld\n", m * f[m][n] - sum[n] * sum[n]);
    system("pause");
    return 0;
}