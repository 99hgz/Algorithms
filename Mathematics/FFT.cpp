#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <complex>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
#define pi acos(-1)
typedef complex<double> E;
typedef long long ll;
ll n, m, l, r[862144],ans,t;
E a[862144], b[862144];
void fft(E *u, ll v)
{
    for (ll i = 0; i < n; i++)
        if (i < r[i])
            swap(u[i], u[r[i]]);
    for (ll i = 1; i < n; i <<= 1)
    {
        E wn(cos(pi / i), v * sin(pi / i));
        for (ll j = 0; j < n; j += (i << 1))
        {
            E w(1, 0);
            for (ll k = 0; k < i; k++, w *= wn)
            {
                E x = u[j + k], y = w * u[i + j + k];
                u[j + k] = x + y;
                u[i + j + k] = x - y;
            }
        }
    }
    if (v == -1)
        for (ll i = 0; i < n; i++)
            u[i] /= n;
}

int main()
{
    scanf("%lld", &n);
    m = 2 * n;
    for (ll i = 0; i < n; i++){
        scanf("%lld",&t);
        a[i]=t;
    }
    for (ll i = 0; i < n; i++){
        scanf("%lld",&t);
        b[i]=t;
    }
    for (n = 1; n <= m; n <<= 1)
        l++;
    for (ll i = 0; i < n; i++)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
    fft(a, 1);
    fft(b, 1);
    for (ll i = 0; i < n; i++)
        a[i] *= b[i];
    fft(a, -1);
    for (ll i = 0; i <= m; i++)
        ans+=(ll)(a[i].real() + 0.1);
    printf("%lld\n", ans);
    system("pause");
    return 0;
}