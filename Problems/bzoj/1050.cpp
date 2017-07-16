#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, m, S, T, ansx, ansy, f[505];
struct node
{
    int u, v, val;
} a[5005];
double ans;
bool cmp(node a, node b) { return a.val < b.val; }
int gcd(int x, int y)
{
    if (y == 0)
        return x;
    else
        return gcd(y, x % y);
}
int get(int x)
{
    if (f[x] == x)
        return x;
    else
        f[x] = get(f[x]);
    return f[x];
}
bool calc()
{
    int x1 = get(S), y1 = get(T);
    if (x1 == y1)
        return true;
    return false;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &a[i].u, &a[i].v, &a[i].val);
    scanf("%d%d", &S, &T);
    sort(a + 1, a + m + 1, cmp);
    ans = 1 << 29;
    for (int i = 1; i <= m; i++)
        if (a[i].val == a[i - 1].val)
        {
            for (int j = 1; j <= n; j++)
                f[j] = j;
            for (int j = i; j <= m; j++)
            {
                int x1 = get(a[j].u), y1 = get(a[j].v);
                if (x1 != y1)
                    f[x1] = y1;
                if (calc())
                {
                    if ((double)a[j].val / (double)a[i].val < ans)
                    {
                        ansx = a[j].val;
                        ansy = a[i].val;
                        ans = (double)a[j].val / (double)a[i].val;
                    }
                    break;
                }
            }
        }
    int z = gcd(ansx, ansy);
    if (ansy == z)
    {
        printf("%d\n", ansx / z);
        return 0;
    }
    if (ans != 1 << 29)
        printf("%d/%d\n", ansx / z, ansy / z);
    else
        printf("IMPOSSIBLE\n");
    return 0;
}
