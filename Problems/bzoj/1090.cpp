#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

char A[200];
int f[200][200];

bool judge(int l, int r2, int r)
{
    if ((r - r2) % (r2 - l + 1) != 0)
        return false;
    for (int i = r2 + 1; i <= r; i++)
    {
        if (A[i] != A[((i - r2 - 1) % (r2 - l + 1)) + l])
            return false;
    }
    return true;
}

int calc(int x)
{
    int res = 0;
    while (x)
    {
        x /= 10;
        res++;
    }
    //printf("%d %d\n", x, res);
    return res;
}

int dfs(int l, int r)
{
    if (f[l][r] > 0)
        return f[l][r];
    f[l][r] = r - l + 1;
    //printf("%d %d\n", l, r);
    for (int i = l; i <= r - 1; i++)
    {
        if (judge(l, i, r))
        {
            //printf("%d %d %d\n", l, i, r);
            f[l][r] = min(f[l][r], calc((r - l + 1) / (i - l + 1)) + dfs(l, i) + 2);
        }
    }
    for (int i = l; i <= r - 1; i++)
    {
        f[l][r] = min(f[l][r], dfs(l, i) + dfs(i + 1, r));
    }
    //printf("f[%d][%d]=%d\n", l, r, f[l][r]);
    return f[l][r];
}

int main()
{
    scanf("%s", A + 1);
    int len = strlen(A + 1);
    //printf("%d\n", judge(6, 8, 14));
    printf("%d\n", dfs(1, len));
    system("pause");
    return 0;
}