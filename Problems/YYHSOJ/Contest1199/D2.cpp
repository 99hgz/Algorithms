#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
ll f[40][40];
int pre[40][40];
int i, j, n, k, left, right;
int a[40];
bool first = true;
void printans(int l, int r)
{
    if (l > r)
        return;
    if (first)
        printf("%d", pre[l][r]), first = false;
    else
        printf(" %d", pre[l][r]);
    printans(l, pre[l][r] - 1);
    printans(pre[l][r] + 1, r);
}
int main()
{
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        f[i][i] = a[i];
        pre[i][i] = i;
    }
    for (i = 1; i <= n; i++)
    {
        for (j = i - 1; j >= 1; j--)
        {
            for (k = j; k <= i; k++)
            {
                left = f[j][k - 1];
                right = f[k + 1][i];
                if (k == j)
                    left = 1;
                if (k == i)
                    right = 1;
                if (left * right + a[k] > f[j][i])
                    f[j][i] = left * right + a[k], pre[j][i] = k;
            }
        }
    }
    printf("%lld\n", f[1][n]);
    printans(1, n);
    system("pause");
    return 0;
}
