#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
typedef long long ll;
using namespace std;
struct Node
{
    ll x, y, v;
} a[20005];
ll father[20005], size[20005];
ll x, y, n, ans;
bool cmp(Node a, Node b) { return a.v < b.v; }
int find(int x)
{
    if (!father[x])
        return x;
    return father[x] = find(father[x]);
}
int main()
{
    scanf("%lld", &n);
    for (int i = 1; i < n; i++)
    {
        scanf("%lld%lld%lld", &a[i].x, &a[i].y, &a[i].v);
    }
    sort(a + 1, a + n, cmp);
    for (int i = 1; i <= n; i++)
    {
        size[i] = 1;
    }
    for (int i = 1; i < n; i++)
    {
        x = find(a[i].x);
        y = find(a[i].y);
        ans += (size[x] * size[y] - 1) * (a[i].v + 1) + a[i].v;
        father[x] = y;
        size[y] += size[x];
    }
    printf("%lld", ans);
}