#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

ll n;
ll a, ans;
int main()
{
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld", &a);
        a--;
        ans = 0;
        for (ll i = 1; i * i <= a; i++)
        {
            if (a % i == 0)
            {
                ans += 2;
            }
            if (i * i == a)
                ans--;
        }
        printf("%lld\n", ans);
    }
    system("pause");
    return 0;
}