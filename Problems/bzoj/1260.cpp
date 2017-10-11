#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
char a[100];
int f[100][100];
int main()
{
    scanf("%s", a + 1);
    memset(f, 0x3f3f3f3f, sizeof f);
    int len = strlen(a + 1);
    for (int i = 1; i <= len; i++)
        f[i][i] = 1;
    for (int i = 1; i < len; i++)
    {
        for (int j = 1; j <= len; j++)
        {
            int l = j, r = j + i;
            if (r > len)
                break;
            if (a[l] == a[r])
            {
                f[l][r] = min(f[l][r], min(f[l][r - 1], min(f[l + 1][r], f[l + 1][r - 1] + 1)));
            }
            else
            {
                for (int k = l; k < r; k++)
                {
                    f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r]);
                }
            }
        }
    }
    printf("%d\n", f[1][len]);
    system("pause");
    return 0;
}