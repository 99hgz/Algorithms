#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
ll n, m, a[100010], b, f[2][200010], ans, pre, pos;
int main()
{
    scanf("%lld%lld", &n, &b);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
        if (a[i] == b)
        {
            pos = i;
            //break;
        }
    }
    f[0][100000] = 1;
    for (ll j = pos + 1; j <= n; j++)
    {
        if (a[j] > b)
            pre += 1;
        else
            pre -= 1;
        f[(j - pos) % 2][pre + 100000]++;
        //printf("%d %d %d\n", (j - pos) % 2, pre, a[j]);
    }
    ans+=f[0][100000];
    pre = 0;
    for (ll i = pos - 1; i >= 1; i--)
    {
        if (a[i] > b)
            pre += 1;
        else
            pre -= 1;
        ans += f[(pos - i) % 2][(-pre) + 100000];
        //printf("%d %d %d\n", i, pre, f[(pos - i) % 2][(-pre) + 100000]);
    }
    printf("%lld\n", ans);
    //system("pause");
    return 0;
}