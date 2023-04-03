#include <cstdio>
#include <algorithm>
using namespace std;

int n, a, b, d, m[50010], prime[50010], tot, f[50010], pre[50010];

void init()
{
    m[1] = 1;
    for (int i = 2; i <= 50000; i++)
    {
        if (!f[i])
        {
            prime[++tot] = i;
            m[i] = -1;
        }
        for (int j = 1; j <= tot && i * prime[j] <= 50000; j++)
        {
            f[i * prime[j]] = true;
            if (i % prime[j] == 0)
            {
                m[i * prime[j]] = 0;
                break;
            }
            else
                m[i * prime[j]] = -m[i];
        }
    }
    for (int i = 1; i <= 50000; i++)
        pre[i] = pre[i - 1] + m[i];
}

int main()
{
    init();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d%d", &a, &b, &d);
        int a1 = a / d, b1 = b / d;
        int x = min(a1, b1);
        int pos, ans = 0;
        for (int i = 1; i <= x; i = pos + 1)
        {
            pos = min(a1 / (a1 / i), b1 / (b1 / i));
            ans += (pre[pos] - pre[i - 1]) * (a1 / i) * (b1 / i);
        }
        printf("%d\n", ans);
    }
}