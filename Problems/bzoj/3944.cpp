#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <map>
using namespace std;
#define fi first
#define se second
typedef long long ll;
typedef pair<ll, ll> pr;
int n, lim = 5000000;
map<int, pr> mp;
int prime[5000010], primetot;
bool mark[5000010];
ll phi[5000010], miu[5000010];

void pre(int n)
{
    phi[1] = miu[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (!mark[i])
        {
            prime[++primetot] = i;
            phi[i] = i - 1;
            miu[i] = -1;
        }
        for (int j = 1; j <= primetot; j++)
        {
            if (i * prime[j] > n)
                break;
            mark[i * prime[j]] = true;
            if (i % prime[j] == 0)
            {
                phi[i * prime[j]] = phi[i] * (prime[j]);
                miu[i * prime[j]] = 0;
                break;
            }
            else
            {
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
                miu[i * prime[j]] = -miu[i];
            }
        }
    }
    for (int i = 2; i <= n; i++)
        phi[i] += phi[i - 1], miu[i] += miu[i - 1];
}

pr work(ll n)
{
    if (n <= lim)
        return make_pair(phi[n], miu[n]);
    if (mp.count(n))
        return mp[n];
    pr res = make_pair((n + 1) * n >> 1, 1LL);
    ll nxt;
    for (ll i = 2; i <= n; i = nxt + 1)
    {
        nxt = n / (n / i);
        pr tmp = work(n / i);
        res.fi -= tmp.fi * (nxt - i + 1);
        res.se -= tmp.se * (nxt - i + 1);
    }
    mp[n] = res;
    return res;
}

int main()
{
    pre(lim);
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        pr res = work(n);
        printf("%lld %lld\n", res.fi, res.se);
    }
    system("pause");
    return 0;
}