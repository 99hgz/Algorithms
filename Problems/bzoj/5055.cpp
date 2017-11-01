#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
ll tree[300010], tree2[300010], n, a[300010], ans, Hash[300010];
ll lowbit(ll x) { return x & -x; }
void add2(ll x, ll val)
{
    val %= 19260817;
    for (; x <= 300010; x += lowbit(x))
        tree2[x] = (tree2[x] + val) % 19260817;
}

void add(ll x, ll val)
{
    val %= 19260817;
    for (; x <= 300010; x += lowbit(x))
        tree[x] = (tree[x] + val) % 19260817;
}

ll sum(ll x)
{
    ll res = 0;
    for (; x; x -= lowbit(x))
        res = (res + tree[x]) % 19260817;
    return res;
}

ll sum2(ll x)
{
    ll res = 0;
    for (; x; x -= lowbit(x))
        res = (res + tree2[x]) % 19260817;
    return res;
}

int main()
{
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
        Hash[i] = a[i];
    }
    sort(Hash + 1, Hash + n + 1);
    ll tn = unique(Hash + 1, Hash + n + 1) - Hash - 1;
    for (ll i = 1; i <= n; i++)
    {
        ll x = lower_bound(Hash + 1, Hash + tn + 1, a[i]) - Hash;
        ans = (ans + (sum2(x - 1) % 19260817) * (a[i] % 19260817) % 19260817) % 19260817;
        add2(x, (sum(x - 1) % 19260817) * (a[i] % 19260817));
        add(x, a[i] % 19260817);
    }
    printf("%lld\n", ans);
    system("pause");
    return 0;
}