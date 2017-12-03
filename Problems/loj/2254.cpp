#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

int n, m, len, l1, r1, l2, r2;
int c[50010], part[50010], tot;
ll num[50010], ans;
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll sqr(ll x) { return x * x; }
ll lrange[50010], rrange[50010], ANS[50010];
struct node
{
    int l, r, belong, gx;
} que[200010];

bool cmp(node a, node b)
{
    if (part[a.l] == part[b.l])
        return a.r < b.r;
    return part[a.l] < part[b.l];
}

void update(int i, int add, int isl)
{
    if (isl)
    {
        lrange[c[i]] += add;
        ans = ans + rrange[c[i]] * add;
    }
    else
    {
        rrange[c[i]] += add;
        ans = ans + lrange[c[i]] * add;
    }
}

int main()
{
    int k;
    scanf("%d", &n);
    len = floor(sqrt(n));
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &c[i]);
        part[i] = (i - 1) / len + 1;
    }

    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        que[++tot] = (node){r1, r2, i, 1};
        que[++tot] = (node){l1 - 1, r2, i, -1};
        que[++tot] = (node){r1, l2 - 1, i, -1};
        que[++tot] = (node){l1 - 1, l2 - 1, i, 1};
    }
    sort(que + 1, que + tot + 1, cmp);
    int l = 0, r = 0;
    for (int i = 1; i <= tot; i++)
    {
        for (; r < que[i].r; r++)
            update(r + 1, 1, 0);
        for (; r > que[i].r; r--)
            update(r, -1, 0);
        for (; l > que[i].l; l--)
            update(l, -1, 1);
        for (; l < que[i].l; l++)
            update(l + 1, 1, 1);
        //printf("range:%d %d fx=%d ans=%lld\n", que[i].l, que[i].r, que[i].gx, ans);
        ANS[que[i].belong] += ans * que[i].gx;
    }
    for (int i = 1; i <= m; i++)
        printf("%lld\n", ANS[i]);
    system("pause");
    return 0;
}