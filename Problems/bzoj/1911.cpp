#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

ll n, m, a[1000010], sum[1000010], f[1000010], q[1000010];
ll A, B, C;
ll sqr(ll x)
{
    return x * x;
}
double slope(ll q, ll p)
{
    return (double)(f[p] + A * sqr(sum[p]) - B * sum[p] - (f[q] + A * sqr(sum[q]) - B * sum[q])) / (double)(sum[p] - sum[q]);
}

int main()
{
    scanf("%lld", &n);
    scanf("%lld%lld%lld", &A, &B, &C);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
        sum[i] = sum[i - 1] + a[i];
    }

    ll head = 1, tail = 1;
    for (ll j = 1; j <= n; j++)
    {
        while (head < tail && slope(q[head], q[head + 1]) > (double)2 * A * sum[j])
            head++;
        ll k = q[head];
        f[j] = f[k] + A * sqr(sum[j] - sum[k]) + B * (sum[j] - sum[k]) + C;
        while (head < tail && slope(q[tail], j) > slope(q[tail - 1], q[tail]))
            tail--;
        q[++tail] = j;
    }
    //printf("%lld\n", f[1]);

    printf("%lld\n", f[n]);
    system("pause");
    return 0;
}