#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

ll f[100][100], k, bit[100], n, ans;

ll dfs(ll cd, ll pos, bool limit)
{
    //printf("%lld %lld %d\n", cd, pos, limit);
    if (cd == 0)
        return 1;
    if (pos == 0)
        return 0;
    if (!limit && f[cd][pos] != -1)
        return f[cd][pos];
    ll res = 0;
    ll maxx = (limit ? bit[pos] : 1);
    for (ll i = 0; i <= maxx; i++)
    {
        res += dfs(cd - i, pos - 1, limit && i == bit[pos]);
        // res %= (ll)10000007;
    }
    if (!limit)
        f[cd][pos] = res;
    return res;
}

ll power(ll a, ll b, ll p)
{
    // a^b mod p
    //辣鸡
    ll ans = 1;
    while (b > 0)
    {
        if (b & 1)
            ans = (ans * a) % p;
        a = (a * a) % p;
        b >>= 1;
    }
    return ans;
}

int main()
{
    scanf("%lld", &n);
    ll nn = n;
    k = 0;
    while (n)
    {
        bit[++k] = n % (ll)2;
        n /= (ll)2;
    }
    ans = 1;
    memset(f, -1, sizeof f);
    for (ll i = 2; i <= k; i++)
    {
        ///memset(f, 0, sizeof f);
        ll tmp = dfs(i, k, true);
        //printf("%lld %lld\n", i, tmp);
        ans *= power(i, tmp, 10000007);
        ans %= (ll)10000007;
    }
    printf("%lld\n", ans);
    //printf("%d\n", k);
    //printf("%d", dfs(k, false));
    system("pause");
    return 0;
}