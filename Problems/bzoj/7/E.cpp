#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int n;
double t;
double d[1010], s[1010];
double maxc;
int main()
{

    scanf("%d%lf", &n, &t);
    maxc = -1e7;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lf%lf", &d[i], &s[i]);
        double tmp = d[i] / t - s[i];
        if (tmp > maxc)
            maxc = tmp;
    }
    //printf("%.8lf\n", maxc);
    double l = maxc;
    double r = 10000000;
    int tt = 0;
    double mid;
    while (tt < 200)
    {
        tt++;
        mid = (l + r) / 2;
        double tmpt = 0;
        for (int i = 1; i <= n; i++)
        {
            tmpt += d[i] / (double)(s[i] + mid);
        }
        //printf("%.9lf\n", tmpt);
        if (tmpt > t)
            l = mid;
        else
            r = mid;

        //printf("%.9lf %.9lf\n", l, r);
    }
    printf("%.9lf\n", mid);
    system("pause");
    return 0;
}