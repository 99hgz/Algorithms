#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

ll n, m, a[100010], sum[100010], f[2][100010], q[100010];
ll sqr(ll x)
{
    return x * x;
}
double slope(ll id, ll i, ll j)
{
    return (double)(f[id][j] - sqr(sum[j]) - f[id][i] + sqr(sum[i])) / (double)(sum[i] - sum[j]);
}

int main()
{
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    int num = 0;
    for (ll i = 1; i <= n; i++)
        if (a[i])
            a[++num] = a[i];
    n = num;
    for (ll i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + a[i];
    int cur = 1, last = 0;
    for (ll i = 1; i <= m; i++)
    {
        swap(cur, last);
        ll head = 1, tail = 1;
        for (ll j = 1; j <= n; j++)
        {
            while (head < tail && slope(last, q[head], q[head + 1]) < sum[j])
                head++;
            f[cur][j] = f[last][q[head]] + sum[q[head]] * (sum[j] - sum[q[head]]);
            while (head < tail && slope(last, q[tail], j) < slope(last, q[tail - 1], q[tail]))
                tail--;
            q[++tail] = j;
        }
    }
    printf("%lld\n", f[cur][n]);
    system("pause");
    return 0;
}