#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef unsigned long long ll;

ll pow1[200010], pow2[200010], f1[200010], f2[200010];
ll a[200010], b[200010];
ll mod = 1000007;
struct Node
{
    ll hash, l;
};
vector<Node> vmap[1000007];
ll x, y, n, m, k;

ll calc2(ll r)
{
    ll l = r - k + 1;
    return (f2[r] - f2[l - 1] * pow2[r - l + 1]);
}

ll calc1(ll r)
{
    ll l = r - k + 1;
    return (f1[r] - f1[l - 1] * pow1[r - l + 1] % mod + mod) % mod;
}

bool check()
{
    ll hash1 = 0, hash2 = 0;
    for (ll i = 1; i <= k; i++)
    {
        hash1 = (hash1 * 233333 + b[i]) % mod;
        hash2 = hash2 * 1000007 + b[i];
    }
    printf("%lld %lld\n", hash1, hash2);
    for (ll i = 0; i < vmap[hash1].size(); i++)
    {
        if ((vmap[hash1][i].hash == hash2) && (vmap[hash1][i].l >= x) && ((vmap[hash1][i].l + k - 1 <= y)))
            return true;
    }
    return false;
}

int main()
{
    scanf("%lld%lld%lld", &n, &m, &k);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
    }
    pow1[0] = 1;
    pow2[0] = 1;
    for (ll i = 1; i <= n; i++)
    {
        pow1[i] = (pow1[i - 1] * 233333) % mod;
        pow2[i] = pow2[i - 1] * 1000007;
    }
    for (ll i = 1; i <= n; i++)
    {
        f1[i] = (f1[i - 1] * 233333 + a[i]) % mod;
        f2[i] = f2[i - 1] * 1000007 + a[i];
    }
    for (ll i = k; i <= n; i++)
    {
        printf("%lld %lld\n", calc1(i), calc2(i));
        vmap[calc1(i)].push_back((Node){calc2(i), i - k + 1});
    }
    for (ll i = 1; i <= m; i++)
    {
        scanf("%lld%lld", &x, &y);
        for (ll i = 1; i <= k; i++)
        {
            scanf("%lld", &b[i]);
        }
        if (check())
            printf("No\n");
        else
            printf("Yes\n");
    }
    system("pause");
    return 0;
}