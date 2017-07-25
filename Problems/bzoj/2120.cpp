#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

int n, m, len;
int c[50010], part[50010];
ll num[50010], ans;
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll sqr(ll x) { return x * x; }
struct node
{
    int l, r, id;
    ll a, b;
} que[50010];

bool cmp(node a, node b)
{
    return (part[a.l] < part[b.l]) || ((part[a.l] == part[b.l]) && (a.r < b.r)) || ((part[a.l] == part[b.l]) && (a.r == b.r) && (a.x < b.x)) ；
}
bool cmpwithid(node a, node b)
{
    return a.id < b.id;
}
void update(int i, int add)
{
    ans -= sqr(num[c[i]]);
    num[c[i]] += add;
    ans += sqr(num[c[i]]);
}

int main()
{
    int k;
    scanf("%d%d", &n, &m);
    len = floor(sqrt(n));
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &c[i]);
        part[i] = (i - 1) / len + 1;
    }
    char ch;
    for (int i = 1; i <= m; i++)
    {
        scanf("%c", &ch);
        printf("%c\n", ch);
        if (ch == 'Q')
        {
            quenum++;
            scanf("%d %d", &que[i].l, &que[i].r);
            que[i].x = changenum;
            que[i].id = i;
        }
        else
        {
            changenum++;
            scanf("%d%d", &chg[i].x, &chg[i].y);
            chg[i].o = c[chg[i].x];
            c[chg[i].x] = chg[i].y;
        }
    }
    sort(que + 1, que + quenum + 1, cmp);
    int l = 1, r = 0, cur = 0;
    for (int i = 1; i <= m; i++)
    {
        for (; cur < que[i].x; cur++)
        {
            change(chg[i].x + 1, chg[i].y);
        }
        for (; cur > que[i].x; cur--)
        {
            change(chg[i].x, chg[i].o);
        }
        for (; r < que[i].r; r++)
            update(r + 1);
        for (; r > que[i].r; r--)
            update(r);
        for (; l > que[i].l; l--)
            update(l - 1);
        for (; l < que[i].l; l++)
            update(l);
        if (que[i].l == que[i].r)
        {
            que[i].a = 0;
            que[i].b = 1;
            continue;
        }

        que[i].a = ans;
    }
    sort(que + 1, que + 1 + m, cmpwithid);
    for (int i = 1; i <= m; i++)
    {
        printf("%lld\n", que[i].a);
    }
    system("pause");
    return 0;
}