#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
double f[33001], t[33001][21], pre[21][21], are[33001];
int price[21], area[21];
int n, i, j, p, q, yhq, sta;
double min(double a, double b)
{
    if (a < b)
        return a;
    else
        return b;
}
int main()
{
    while ((cin >> n) && (n != 0))
    {
        double max;
        for (i = 0; i <= 20; i++)
            for (j = 0; j <= 20; j++)
                pre[i][j] = 1;
        for (i = 1; i <= n; i++)
        {
            cin >> price[i] >> area[i] >> yhq;
            for (j = 1; j <= yhq; j++)
            {
                cin >> p >> q;
                pre[i][p] *= (double)(100 - q) / 100.0;
            }
        }
        for (i = 0; i <= 33000; i++)
            for (j = 0; j <= 20; j++)
                t[i][j] = 1;
        for (sta = 0; sta <= (1 << n) - 1; sta++)
        {
            are[sta] = 0;
            for (i = 1; i <= n; i++)
            {
                if ((sta & (1 << (i - 1))) > 0)
                    are[sta] += area[i];
                else
                {
                    for (j = 1; j <= n; j++)
                        if ((sta & (1 << (j - 1))) > 0)
                            t[sta][i] = t[sta][i] * pre[j][i];
                }
            }
        }
        f[0] = 0;
        max = 99999999;
        for (sta = 1; sta <= (1 << n) - 1; sta++)
        {
            f[sta] = 99999999;
            for (i = 1; i <= n; i++)
            {
                if ((sta & (1 << (i - 1))) > 0)
                    f[sta] = min(f[sta], f[sta ^ (1 << (i - 1))] + t[sta ^ (1 << (i - 1))][i] * price[i]);
                if ((are[sta] * max) > f[sta])
                    max = f[sta] / are[sta];
            }
        }
        printf("%.4lf\n", max);
    }
    //system("pause");
}
