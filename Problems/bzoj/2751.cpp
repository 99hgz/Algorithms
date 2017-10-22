#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <algorithm>
using namespace std;
typedef long long ll;

ll mod_mul(ll a, ll b, ll p)
{
    //来自http://blog.csdn.net/mengxiang000000/article/details/52073217
    a %= p;
    b %= p;
    return (a * b - (ll)(a / (long double)p * b + 1e-8) * p + p) % p;
}

ll power2(ll a, ll b, ll p)
{
    // a^b mod p
    a %= p;
    ll ans = 1;
    while (b)
    {
        if (b % 2 == 1)
        {
            ans = mod_mul(ans, a, p);
            b -= 1;
        }
        a = mod_mul(a, a, p);
        b /= 2;
    }
    return ans;
}
ll n, m, k, x, y;

map<pair<ll, ll>, bool> mp2;
map<ll, ll> mp;
ll ans, sum, tot;

int main()
{
    scanf("%lld%lld%lld", &n, &m, &k);
    for (ll i = 1; i <= k; i++)
    {
        scanf("%lld%lld", &x, &y);
        if (!mp2[make_pair(x, y)])
        {
            mp2[make_pair(x, y)] = true;
            mp[x] += y;
        }
    }
    ans = 1, sum = (1 + n) * n / 2;
    //printf("%lld\n", sum);
    map<ll, ll>::iterator it = mp.begin();
    while (it != mp.end())
    {
        tot++;
        ans *= (sum - (it->second)) % 1000000007;
        //printf("%d\n", (sum - (it->second)));
        ans %= 1000000007;
        it++;
    }
    // printf("%d\n", ans);
    ans = (ans * power2(sum, m - tot, 1000000007)) % 1000000007;
    printf("%lld\n", ans);
    system("pause");
    return 0;
}