#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

void maintain(int &a)
{
    int tmp = ((a == 0) ? 0x3f3f3f3f : a);
    a = tmp;
}
int n, a[100010], b[100010], c[100010], f[300010];

int main()
{
    scanf("%d", &n);
    int m = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d%d", &a[i], &b[i], &c[i]);
        maintain(a[i]);
        maintain(b[i]);
        maintain(c[i]);
        m += min(a[i], min(b[i], c[i]));
    }
    memset(f, 0x3f3f3f3f, sizeof f);
    f[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = m; j >= 0; j--)
        {
            f[j] += b[i];
            if (j >= a[i])
                f[j] = min(f[j], f[j - a[i]]);
            if (j >= c[i])
                f[j] = min(f[j], f[j - c[i]] + c[i]);
        }
    }
    int ans = 0x3f3f3f3f;
    for (int i = 1; i <= m; i++)
        ans = min(ans, max(f[i], i));
    printf("%d", ans);
    while (1)
    {
    }
}