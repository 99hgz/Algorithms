#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, k;
int main()
{
    scanf("%d%d", &n, &k);
    ll ans = (ll)n * k;
    int j;
    for (int i = 1; i <= n; i = j + 1)
    {
        if (!(k / i))
            break;
        j = min(k / (k / i), n);
        ans -= (ll)(i + j) * (j - i + 1) / 2 * (k / i);
    }
    printf("%lld\n", ans);
    system("pause");
    return 0;
}