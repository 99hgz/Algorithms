#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, a[10010], f[10010][2][2][2], ans;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    f[1][0][0][0] = 1;
    if (a[1] >= 1)
        f[1][0][0][1] = 1;
    for (int i = 2; i <= n; i++)
        for (int a1 = 0; a1 <= 1; a1++)
            for (int a2 = 0; a2 <= 1; a2++)
                for (int a3 = 0; a3 <= 1; a3++)
                {
                    if (a[i - 1] < a3 + a2)
                        continue;
                    if ((a[i - 1] - a3 - a2) + a3 > a[i])
                        continue;
                    f[i][a2][a3][a[i - 1] - a3 - a2] += f[i - 1][a1][a2][a3];
                }
    for (int a1 = 0; a1 <= 1; a1++)
        for (int a2 = 0; a2 <= 1; a2++)
            for (int a3 = 0; a3 <= 1; a3++)
                if (a[n] == a3 + a2)
                    ans += f[n][a1][a2][a3];
    printf("%d\n", ans);
    system("pause");
    return 0;
}