#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
typedef long long ll;
using namespace std;
ll a[101000];
struct LB
{
    ll f[70];
    LB()
    {
        memset(f, 0, sizeof(f));
    }
    void insert(ll val, ll tmp)
    {
        for (int i = 60; i >= 0; i--)
        {
            if ((val & (1LL << i)) && !((tmp >> i) & 1))
            {
                if ((!f[i]))
                {
                    f[i] = val;
                    return;
                }
                val ^= (f[i]);
            }
        }
        for (int i = 60; i >= 0; i--)
        {
            if ((val & (1LL << i)) && ((tmp >> i) & 1))
            {
                if ((!f[i]))
                {
                    f[i] = val;
                    return;
                }
                val ^= (f[i]);
            }
        }
    }
    ll max(ll tmp)
    {
        ll res = 0;
        for (int i = 60; i >= 0; i--)
            if (!(res >> i & 1) && !((tmp >> i) & 1))
                res = (res ^ f[i]);
        for (int i = 60; i >= 0; i--)
            if (!(res >> i & 1) && ((tmp >> i) & 1))
                res = (res ^ f[i]);
        return res;
    }
};
int main()
{
    LB list;
    ll ans = 0;
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
        printf("%lld\n", a[i]);
        ans ^= a[i];
    }
    for (int i = 1; i <= n; i++)
        list.insert(a[i], ans);
    printf("%lld", ans ^ list.max(ans));
    system("pause");
}