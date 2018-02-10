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
int n, m, l, r[262144];
E a[262144], b[262144];
void fft(E *u, int v)
{
    for (int i = 0; i < n; i++)
        if (i < r[i])
            swap(u[i], u[r[i]]);
    for (int i = 1; i < n; i <<= 1)
    {
        E wn(cos(pi / i), v * sin(pi / i));
        for (int j = 0; j < n; j += (i << 1))
        {
            E w(1, 0);
            for (int k = 0; k < i; k++, w *= wn)
            {
                E x = u[j + k], y = w * u[i + j + k];
                u[j + k] = x + y;
                u[i + j + k] = x - y;
            }
        }
    }
    if (v == -1)
        for (int i = 0; i < n; i++)
            u[i] /= n;
}

int main()
{
    scanf("%d", &n);
    n--;
    m = 2 * n;
    for (int i = 0; i <= n; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        a[i] = x, b[n - i] = y;
    }
    for (n = 1; n <= m; n <<= 1)
        l++;
    for (int i = 0; i < n; i++)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
    fft(a, 1);
    fft(b, 1);
    for (int i = 0; i <= n; i++)
        a[i] *= b[i];
    fft(a, -1);
    for (int i = m / 2; i <= m; i++)
        printf("%d\n", (int)(a[i].real() + 0.1));
    system("pause");
    return 0;
}