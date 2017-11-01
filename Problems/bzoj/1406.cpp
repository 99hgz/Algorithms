#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

ll n, ys[500000], ans[500000], ansnum, ysnum;

int main()
{
    ll x;
    scanf("%lld", &n);
    for (int i = 1; i <= (ll)sqrt(n); i++)
        if (n % i == 0)
            ys[++ysnum] = i;
    for (int i = 1; i <= ysnum; i++)
    {
        int a = ys[i], b = n / a;
        for (int k = 0; (x = b * k + 2) < n; k++)
        {
            if (x % a == 0)
                ans[++ansnum] = x - 1;
        }
        for (int k = 0; (x = b * k - 2) < n; k++)
        {
            if (x % a == 0)
                ans[++ansnum] = x + 1;
        }
    }
    sort(ans + 1, ans + 1 + ansnum);
    ans[0] = -1;
    bool flag = true;
    for (int i = 1; i <= ansnum; i++)
    {
        if (ans[i] != ans[i - 1] && ans[i] < n)
        {
            printf("%lld\n", ans[i]);
            flag = false;
        }
    }
    if (flag)
        printf("None\n");
    system("pause");
    return 0;
}