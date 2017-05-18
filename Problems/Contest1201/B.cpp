#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, i, j;
int f[20][1 << 20];
int a[20][20];

void find(int point, int sta)
{
    if (f[point][sta] > 0)
        return;
    for (int i = 0; i < n; i++)
    {
        int bit = (sta >> i) & 1;
        if (!bit)
        {
            find(point + 1, sta | (1 << i));
            f[point][sta] = max(f[point][sta], f[point + 1][sta | (1 << i)] + a[point][i + 1]);
        }
    }
}

int main()
{
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
    find(1, 0);
    printf("%d\n", f[1][0]);
    //system("pause");
    return 0;
}