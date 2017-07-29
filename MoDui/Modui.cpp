/*
 * @key word:莫队
 * @已测试
 * 带修改的莫队:bzoj/2120.cpp
 * @Author: hgz 
 * @Date: 2017-07-25 21:19:18 
 * @Last Modified by:   hgz 
 * @Last Modified time: 2017-07-25 21:19:18 
 */
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
    if (part[a.l] == part[b.l])
        return a.r < b.r;
    return part[a.l] < part[b.l];
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
    scanf("%d%d%d", &n, &m, &k);
    len = floor(sqrt(n));
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &c[i]);
        part[i] = (i - 1) / len + 1;
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &que[i].l, &que[i].r);
        que[i].id = i;
    }
    sort(que + 1, que + m + 1, cmp);
    int l = 1, r = 0;
    for (int i = 1; i <= m; i++)
    {
        for (; r < que[i].r; r++)
            update(r + 1, 1);
        for (; r > que[i].r; r--)
            update(r, -1);
        for (; l > que[i].l; l--)
            update(l - 1, 1);
        for (; l < que[i].l; l++)
            update(l, -1);
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