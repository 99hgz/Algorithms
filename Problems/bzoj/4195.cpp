#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

ll n, a[1000010], b[1000010], e[1000010], map[2000010], tn, fa, fb, tmpa, father[1000010], tmpb, cnt;

ll get_father(ll x)
{
    return father[x] == -1 ? x : father[x] = get_father(father[x]);
}

int main()
{
    ll t;
    scanf("%lld", &t);
    while (t--)
    {
        memset(father, -1, sizeof father);
        scanf("%lld", &n);
        for (ll i = 1; i <= n; i++)
        {
            scanf("%lld%lld%lld", &a[i], &b[i], &e[i]);
            map[++cnt] = a[i];
            map[++cnt] = b[i];
        }
        sort(map + 1, map + cnt + 1);
        ll tn = unique(map + 1, map + cnt + 1) - map - 1;

        for (ll i = 1; i <= n; i++)
        {
            if (e[i] == 0)
                continue;
            ll tmpa = lower_bound(map + 1, map + tn + 1, a[i]) - map;
            ll tmpb = lower_bound(map + 1, map + tn + 1, b[i]) - map;
            ll fa = get_father(tmpa);
            ll fb = get_father(tmpb);
            if (fa != fb)
            {
                father[fa] = fb;
            }
        }
        bool flag = false;
        for (ll i = 1; i <= n; i++)
        {
            if (e[i] == 1)
                continue;
            ll tmpa = lower_bound(map + 1, map + tn + 1, a[i]) - map;
            ll tmpb = lower_bound(map + 1, map + tn + 1, b[i]) - map;
            ll fa = get_father(tmpa);
            ll fb = get_father(tmpb);
            if (fa == fb)
            {
                printf("NO\n");
                flag = true;
                break;
            }
        }
        if (!flag)
            printf("YES\n");
    }
    system("pause");
    return 0;
}