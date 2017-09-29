#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
int n;
struct node
{
    long long x, y;
    double z;
} a[3005], b[3005];
bool cmp(node a, node b)
{
    return a.z > b.z;
}
bool cmp1(node a, node b) { return (a.y != b.y) ? a.y > b.y : a.x < b.x; }
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &a[i].x, &a[i].y);
    sort(a + 1, a + n + 1, cmp1);
    long long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i - 1; j++)
            b[j].x = a[j].x, b[j].y = a[j].y;
        for (int j = 1; j <= i - 1; j++)
            b[j].x -= a[i].x, b[j].y -= a[i].y;
        for (int j = 1; j <= i - 1; j++)
            b[j].z = atan2(b[j].y, b[j].x);
        sort(b + 1, b + i, cmp);
        long long x = 0, y = 0;
        for (int j = 1; j <= i - 1; j++)
        {
            ans = ans + y * b[j].x - x * b[j].y;
            x += b[j].x;
            y += b[j].y;
        }
    }
    if (ans%2==1) printf("%lld.5\n",ans);else printf("%lld.0\n", ans);
    return 0;
}