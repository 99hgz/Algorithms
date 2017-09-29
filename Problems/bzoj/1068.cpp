#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

char A[200];
int f[200][200][2];

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

int lowbit(int x) { return x & -x; }
int calc(int x)
{
    if (x != lowbit(x))
        return -1;
    return (int)(log(x) / log(2));
}

int dfs(int l, int r, int t)
{
    if (f[l][r][t] > 0)
        return f[l][r][t];
    f[l][r][t] = r - l + 1;
    if (t)
        for (int k = l; k < r; k++)
            f[l][r][t] = min(f[l][r][t], dfs(l, k, 1) + dfs(k + 1, r, 1) + 1);
    for (int k = l; k < r; k++)
        f[l][r][t] = min(f[l][r][t], dfs(l, k, t) + r - k);
    if (judge(l, ((l + r) >> 1), r))
        f[l][r][t] = min(f[l][r][t], dfs(l, (l + r) >> 1, 0) + 1);
    return f[l][r][t];
}

int main()
{
    scanf("%s", A + 1);
    int len = strlen(A + 1);
    printf("%d\n", dfs(1, len, 1));
    system("pause");
    return 0;
}