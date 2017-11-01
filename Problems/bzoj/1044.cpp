#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, m, a[50010], sum[50010], total, gmax, l, r, ans, f[2][500010], preans, prepos;

bool check(int x)
{
    int ranges = 0, pre = 0;
    for (int i = 1; i <= n; i++)
    {
        if (pre + a[i] > x)
        {
            ranges++;
            if (ranges > m + 1)
                return false;
            pre = a[i];
        }
        else
            pre += a[i];
    }
    if (pre > 0)
    {
        ranges++;
    }
    if (ranges > m + 1)
        return false;
    else
        return true;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        total += a[i];
        sum[i] = sum[i - 1] + a[i];
        gmax = max(gmax, a[i]);
    }
    l = gmax, r = total;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
        {
            r = mid - 1;
            ans = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    printf("%d ", ans);
    int now = 0;
    f[now][0] = 1;
    int ANS = 0;
    for (int i = 0; i <= m; i++)
    {
        now ^= 1;
        preans = 0, prepos = 1;
        for (int i = 1; i <= n; i++)
        {
            f[now][i] = 0;
        }
        for (int j = 1; j <= n; j++)
        {
            if (i == 0)
            {
                if (sum[j] <= ans)
                    f[now][j] = 1;
                else
                    f[now][j] = 0;
            }
            else
            {
                while (prepos < j && sum[j] - sum[prepos] > ans)
                {
                    preans -= f[now ^ 1][prepos];
                    preans = (preans + 10007) % 10007;
                    prepos++;
                }
                f[now][j] = preans;
                preans += f[now ^ 1][j];
                preans %= 10007;
            }
        }
        ANS += f[now][n];
        ANS %= 10007;
    }
    printf("%d\n", ANS);
    system("pause");
    return 0;
}