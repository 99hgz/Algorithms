#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
ll n, A, B, C, a[10000010];
double ans;
int main()
{
    scanf("%lld%lld%lld%lld%lld", &n, &A, &B, &C, &a[1]);
    bool flag = false;
    for (int i = 2; i <= n; i++)
        a[i] = (a[i - 1] * A + B) % 100000001;
    for (int i = 1; i <= n; i++)
    {
        a[i] = a[i] % C + 1;
        if (a[i] == 0)
            flag = true;
    }
    if (flag)
    {
        printf("0.000\n");
    }
    else
    {
        for (int i = 1; i <= n - 1; i++)
        {
            ans += (double)min(a[i], a[i + 1]) / (double)(a[i] * a[i + 1]);
        }
        ans += (double)min(a[1], a[n]) / (double)(a[1] * a[n]);
        printf("%.3lf\n", ans);
    }
    system("pause");
    return 0;
}