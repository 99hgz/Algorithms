#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
ll n;
int main()
{
    scanf("%lld", &n);
    ll ans = 1;
    ll k;
    for (k = 1; k <= n; k++)
    {
        ans *= 2;
        if ((ans - 1) >= n)
            break;
    }
    printf("%lld\n", k);
    system("pause");
    return 0;
}