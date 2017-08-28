#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

ll tree[3][101000];
char A[10];
ll a[101000];
ll n, m, f, t, tmp;
ll lowbit(ll x) { return x & -x; }
void add(ll wz, ll pos, ll x)
{
    for (; pos <= n; pos += lowbit(pos))
        tree[wz][pos] += x;
}
ll sum(ll wz, ll pos)
{
    ll res = 0;
    for (; pos; pos -= lowbit(pos))
        res += tree[wz][pos];
    return res;
}

int main()
{
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
        add(1, i, a[i]);
        add(2, i, (i - 1) * a[i]);
    }
    for (ll i = 1; i <= m; i++)
    {
        scanf("%s", A);
        if (A[0] == 'Q')
        {
            scanf("%lld", &tmp);
            printf("%lld\n", tmp * sum(1, tmp) - sum(2, tmp));
        }
        else
        {
            scanf("%lld%lld", &f, &t);

            add(1, f, t - a[f]);
            add(2, f, (f - 1) * (t - a[f]));
            a[f] = t;
        }
    }
    system("pause");
    return 0;
}