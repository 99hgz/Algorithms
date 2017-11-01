#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
ll n;
struct Node
{
    ll x, y, id;
} p[100010];
bool cmp(Node a, Node b)
{
    return a.x < b.x;
}
bool cmp2(Node a, Node b)
{
    return a.y < b.y;
}
ll tmpx, tmpy, ans[100010], prex, prey, ANS;

int main()
{
    ANS = 1ll << 62;
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld%lld", &tmpx, &tmpy);
        p[i].x = tmpx + tmpy;
        p[i].id = i;
        p[i].y = tmpx - tmpy;
    }
    sort(p + 1, p + 1 + n, cmp);
    prex = prey = 0;
    for (ll i = 1; i <= n; i++)
    {

        ans[p[i].id] += -prex + p[i].x * (i - 1);
        prex += p[i].x;
    }
    prex = 0;
    for (ll i = n; i >= 1; i--)
    {

        ans[p[i].id] += -p[i].x * (n - i) + prex;
        prex += p[i].x;
    }
    sort(p + 1, p + 1 + n, cmp2);
    prey = 0;
    for (ll i = 1; i <= n; i++)
    {

        ans[p[i].id] += -prey + p[i].y * (i - 1);
        prey += p[i].y;
    }
    prey = 0;
    for (ll i = n; i >= 1; i--)
    {

        ans[p[i].id] += -p[i].y * (n - i) + prey;
        prey += p[i].y;
        ANS = min(ANS, ans[p[i].id]);
    }
    printf("%lld\n", ANS / (ll)2);
    system("pause");
    return 0;
}