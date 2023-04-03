#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <complex>
using namespace std;
typedef long long ll;
#define pi acos(-1)
typedef complex<double> E;
int n, edge[262144 << 1], num[262144 << 1], r[262144 << 1], len, l;
E a[262144 << 1], b[262144 << 1];
void FFT(E *u, int v)
{
    for (int i = 0; i < n; i++)
        if (r[i] > i)
            swap(u[i], u[r[i]]);
    for (int i = 1; i < n; i <<= 1)
    {
        E wn(cos(pi / i), v * sin(pi / i));
        for (int j = 0; j < n; j += (i << 1))
        {
            E w(1, 0);
            for (int k = 0; k < i; k++, w *= wn)
            {
                E x = u[j + k], y = w * u[j + k + i];
                u[j + k] = x + y;
                u[j + k + i] = x - y;
            }
        }
    }
    if (v == -1)
        for (int i = 0; i < n; i++)
            u[i] /= n;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        memset(num, 0, sizeof num);
        memset(r, 0, sizeof r);
        len = l = 0;
        scanf("%d", &n);
        ll enums = n;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &edge[i]);
            num[edge[i]]++;
            len = max(len, edge[i]);
        }
        len <<= 1;
        for (n = 1; n <= len; n <<= 1)
            l++;
        for (int i = 0; i <= n; i++)
            a[i] = b[i] = num[i];
        for (int i = 0; i < n; i++)
            r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
        FFT(a, 1);
        FFT(b, 1);
        for (int i = 0; i < n; i++)
            a[i] *= b[i];
        FFT(a, -1);
        ll sum = 0, tot = 1LL * enums * (enums - 1) * (enums - 2) / 6, ans = 0;
        for (int i = 1; i <= len; i++)
        {
            sum += a[i].real() + 0.1;
            if ((i & 1) == 0)
                sum -= num[i >> 1];
            ans += 1LL * num[i] * sum;
        }
        ans >>= 1;
        double res = 1.0 - 1.0 * ans / (1.0 * tot);
        printf("%.7f\n", res);
    }
    system("pause");
    return 0;
}