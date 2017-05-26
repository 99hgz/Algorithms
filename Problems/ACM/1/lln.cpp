

#include <map>
#include <set>
#include <cmath>
#include <stack>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define mod 998244353
#define pi acos(-1)
#define inf 0x7fffffff
#define ll long long
using namespace std;
ll read()
{
    ll x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
ll n, blo;
ll v[50005], bl[50005], atag[50005];
vector<ll> ve[505];
void reset(ll x)
{
    ve[x].clear();
    for (ll i = (x - 1) * blo + 1; i <= min(x * blo, n); i++)
        ve[x].push_back(v[i]);
    sort(ve[x].begin(), ve[x].end());
}
void add(ll a, ll b, ll c)
{
    for (ll i = a; i <= min(bl[a] * blo, b); i++)
        v[i] += c;
    reset(bl[a]);
    if (bl[a] != bl[b])
    {
        for (ll i = (bl[b] - 1) * blo + 1; i <= b; i++)
            v[i] += c;
        reset(bl[b]);
    }
    for (ll i = bl[a] + 1; i <= bl[b] - 1; i++)
        atag[i] += c;
}
ll query(ll a, ll b, ll c)
{
    ll ans = -1;
    for (ll i = a; i <= min(bl[a] * blo, b); i++)
        if (v[i] + atag[bl[a]] < c)
            ans = max(ans, atag[bl[a]] + v[i]);
    if (bl[a] != bl[b])
        for (ll i = (bl[b] - 1) * blo + 1; i <= b; i++)
            if (v[i] + atag[bl[b]] < c)
                ans = max(ans, v[i] + atag[bl[b]]);
    for (ll i = bl[a] + 1; i <= bl[b] - 1; i++)
    {
        ll x = c - atag[i];
        vector<ll>::iterator it1 = lower_bound(ve[i].begin(), ve[i].end(), x);
        if (it1 != ve[i].begin())
        {
            it1--;
            ans = max(ans, *it1 + atag[i]);
        }
    }
    return ans;
}
int main()
{
    freopen("lln.in", "r", stdin);
    freopen("lln.out", "w", stdout);
    n = read();
    blo = sqrt(n);
    for (ll i = 1; i <= n; i++)
        v[i] = read();
    for (ll i = 1; i <= n; i++)
    {
        bl[i] = (i - 1) / blo + 1;
        ve[bl[i]].push_back(v[i]);
    }
    for (ll i = 1; i <= bl[n]; i++)
        sort(ve[i].begin(), ve[i].end());
    for (ll i = 1; i <= n; i++)
    {
        ll f = read(), a = read(), b = read(), c = read();
        if (f == 0)
            add(a, b, c);
        if (f == 1)
            printf("%lld\n", query(a, b, c));
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}