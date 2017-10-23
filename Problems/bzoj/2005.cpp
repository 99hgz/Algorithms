#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
ll n, m, cnt[100010], ans;
int main()
{
    scanf("%lld%lld", &n, &m);
    for (ll i = min(n, m); i >= 1; i--)
    {
        cnt[i] = (n / i) * (m / i);
        for (ll j = i * 2; j <= min(n, m); j += i)
            cnt[i] -= cnt[j];
        //printf("%d %d\n", i, cnt[i]);
        ans += cnt[i] * (2 * i - 1);
    }
    printf("%lld\n", ans);
    system("pause");
    return 0;
}