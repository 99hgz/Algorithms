#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, p, f[3][4300];
int main()
{
    int now = 1;
    scanf("%d%d", &n, &p);
    f[now][1] = 1;
    for (int i = 2; i <= n; i++)
    {
        now ^= 1;
        memset(f[now], 0, sizeof f[now]);
        for (int j = 1; j <= n; j++)
            f[now][j] = (f[now][j - 1] + f[now ^ 1][i - j]) % p;
    }
    printf("%d\n", (2 * f[now][n]) % p);
    system("pause");
    return 0;
}