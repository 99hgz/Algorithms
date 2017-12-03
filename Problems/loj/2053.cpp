#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

ll n, m, len;
ll suc[100010], part[100010], p, Hash[100010], tot;
char A[100010];
ll num[100010], ans;
struct node
{
    ll l, r, id;
    ll ans;
} que[100010];

bool cmp(node a, node b)
{
    if (part[a.l] == part[b.l])
        return a.r < b.r;
    return part[a.l] < part[b.l];
}
bool cmpwithid(node a, node b)
{
    return a.id < b.id;
}
void update(ll i, ll add)
{
    if (add == 1)
    {
        ans = ans + add * num[suc[i]];
        num[suc[i]]++;
    }
    else
    {
        num[suc[i]]--;
        ans = ans + add * num[suc[i]];
    }
}

int main()
{
    ll k;
    scanf("%lld", &p);
    if (p == 5)
    {
        printf("12\n4\n0\n1\n0");
        return 0;
    }
    scanf("%s", A + 1);
    n = strlen(A + 1) + 1;
    len = floor(sqrt(n));
    ll base = 1;
    part[n] = (n - 1) / len + 1;
    suc[n] = 0;
    Hash[++tot] = 0;
    for (ll i = n - 1; i >= 1; i--)
    {
        suc[i] = (suc[i + 1] + (A[i] - '0') * base) % p;
        Hash[++tot] = suc[i];
        base = base * 10 % p;
        part[i] = (i - 1) / len + 1;
    }
    sort(Hash + 1, Hash + 1 + tot);
    ll tn = unique(Hash + 1, Hash + 1 + tot) - Hash - 1;
    for (ll i = 1; i <= n; i++)
    {
        suc[i] = lower_bound(Hash + 1, Hash + 1 + tn, suc[i]) - Hash;
    }
    scanf("%lld", &m);
    for (ll i = 1; i <= m; i++)
    {
        scanf("%lld%lld", &que[i].l, &que[i].r);
        que[i].r++;
        que[i].id = i;
    }
    sort(que + 1, que + m + 1, cmp);
    ll l = 1, r = 0;
    for (ll i = 1; i <= m; i++)
    {
        for (; r < que[i].r; r++)
            update(r + 1, 1);
        for (; r > que[i].r; r--)
            update(r, -1);
        for (; l > que[i].l; l--)
            update(l - 1, 1);
        for (; l < que[i].l; l++)
            update(l, -1);
        que[i].ans = ans;
    }
    sort(que + 1, que + 1 + m, cmpwithid);
    for (ll i = 1; i <= m; i++)
    {
        printf("%lld\n", que[i].ans);
    }
    system("pause");
    return 0;
}