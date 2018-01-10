#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
double sqr(double x) { return x * x; }
double a[1010][1010], b[1010], ans[1010];
int n, m;
double eps = 1e-6;
void swap1(int a1, int b)
{
    for (int i = 1; i <= n; i++)
        swap(a[a1][i], a[b][i]);
}

int gauss()
{
    for (int i = 1; i <= n; i++)
    {
        int idx = 0;
        for (int j = i; j <= m; j++)
            if (fabs(a[j][i]) > fabs(a[idx][i]))
                idx = i;
        if (!idx)
            return 2;
        swap1(i, idx);
        for (int j = i + 1; j <= m; j++)
        {
            double f = 1.0 * a[j][i] / a[i][i];
            for (int k = 1; k <= n; k++)
                a[j][k] -= a[i][k] * f;
            b[j] -= b[i] * f;
        }
    }
    for (int i = 1; i <= m; i++)
    {
        bool flag = true;
        for (int j = 1; j <= n; j++)
            if (fabs(a[i][j]) >= eps)
                flag = false;
        if (flag && fabs(b[i]) < eps)
            flag = false;
        if (flag)
            return 0;
    }
    for (int i = n; i >= 1; i--)
    {
        for (int j = i + 1; j <= n; j++)
        {
            b[i] -= a[i][j] * ans[j];
            a[i][j] = 0;
        }
        ans[i] = 1.0 * b[i] / a[i][i];
    }
    return 1;
}
double f[1010];
int main()
{
    scanf("%d", &n);
    m = n;
    for (int i = 1; i <= n; i++)
        scanf("%lf", &f[i]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            double t;
            scanf("%lf", &t);
            a[i][j] = 2 * (t - f[j]);
            b[i] += sqr(t) - sqr(f[j]);
        }
    int flag = gauss();

    for (int i = 1; i <= n - 1; i++)
        printf("%.3lf ", ans[i]);
    printf("%.3lf\n", ans[n]);
}