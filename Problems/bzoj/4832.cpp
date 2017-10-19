#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int k, a, b, c;
double ab, f[2][10][10][10], ans;
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        ans = 0;
        memset(f, 0, sizeof f);
        scanf("%d%d%d%d", &k, &a, &b, &c);
        int now = 0;
        f[now][a][b][c] = 1.0;
        for (int i = 0; i < k; i++)
        {
            now ^= 1;
            memset(f[now], 0, sizeof f[now]);
            for (int j = 0; j <= 7; j++)
            {
                for (int k = 0; k <= 7; k++)
                {
                    for (int l = 0; l <= 7; l++)
                    {

                        if (f[now ^ 1][j][k][l] == 0)
                            continue;
                        if (j + k + l > 7)
                            continue;
                        ab = (double)1 / (double)(1 + j + k + l);
                        f[now][j][k][l] += f[now ^ 1][j][k][l] * ab;
                        ans += (f[now ^ 1][j][k][l] * ab);
                        if (j)
                            f[now][j - 1][k][l] += f[now ^ 1][j][k][l] * (double)j * ab;
                        if (k)
                        {
                            if (j + k + l <= 6)
                                f[now][j + 1][k - 1][l + 1] += f[now ^ 1][j][k][l] * (double)k * ab;
                            else
                                f[now][j + 1][k - 1][l] += f[now ^ 1][j][k][l] * (double)k * ab;
                        }
                        if (l)
                        {
                            if (j + k + l <= 6)
                                f[now][j][k + 1][l] += f[now ^ 1][j][k][l] * (double)l * ab;
                            else
                                f[now][j][k + 1][l - 1] += f[now ^ 1][j][k][l] * (double)l * ab;
                        }
                    }
                }
            }
        }

        printf("%.2lf\n", ans);
    }
    system("pause");
    return 0;
}