#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
typedef unsigned long long LL;
const int maxn = 25;
int n, A, B;
LL f[maxn][maxn][maxn];

int main()
{
    scanf("%d%d%d", &n, &A, &B);

    for (int a = 0; a <= A; a++)
        for (int b = 0; b <= B; b++)
            f[0][a][b] = 1;

    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= A; j++)
            for (int k = 0; k <= B; k++)
                for (int a = 0; a <= j; a++)
                    for (int b = 0; b <= k; b++)
                        f[i][j][k] += f[i - 1][j - a][k - b];

    cout << f[n][A][B] << '\n';

    return 0;
}