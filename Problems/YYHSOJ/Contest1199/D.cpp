#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n;
int w[50];
ll f[50][50];
int g[50][50];
void print(int l, int r)
{
    if (l > r)
        return;
    int k = g[l][r];
    printf("%d ", k);
    print(l, k - 1);
    print(k + 1, r);
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &w[i]);
        f[i][i] = w[i];
        g[i][i] = i;
    }
    for (int i = n; i > 0; i--)
        for (int j = i + 1; j <= n; j++)
            for (int k = i; k <= j; k++)
            {
                int x = f[i][k - 1], y = f[k + 1][j];
                if (k == i)
                    x = 1;
                if (k == j)
                    y = 1;
                if (f[i][j] < (x * y + w[k]))
                {
                    f[i][j] = x * y + w[k];
                    g[i][j] = k;
                }
            }
    printf("%d\n", f[1][n]);
    print(1, n);
    printf("\n");
    system("pause");
    return 0;
}