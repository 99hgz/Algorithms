#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
using namespace std;
int n, i, j, d[101][101][101], cost[101][101];
bool p[101][101][101];
void bin(int &x1, int &x2, int &x3)
{
    if (x2 > x1)
        swap(x1, x2);
    if (x3 > x1)
        swap(x1, x3);
    if (x3 > x2)
        swap(x2, x3);
}
int dfs(int x1, int x2, int x3)
{
    bin(x1, x2, x3);
    if (x1 == n)
        return 0;
    if (p[x1][x2][x3])
        return d[x1][x2][x3];
    p[x1][x2][x3] = 1;
    d[x1][x2][x3] = 2000000000;
    if (x1 < n)
        d[x1][x2][x3] = min(d[x1][x2][x3], cost[x1][x1 + 1] + dfs(x1 + 1, x2, x3));
    if (x2 < n)
    {
        for (int i = x2 + 1; i <= min(n, x1 + 1); i++)
            d[x1][x2][x3] = min(d[x1][x2][x3], cost[x2][i] + dfs(x1, i, x3));
    }
    for (int i = x3 + 1; i <= min(x1 + 1, n); i++)
        d[x1][x2][x3] = min(d[x1][x2][x3], cost[x3][i] + dfs(x1, x2, i));
    return d[x1][x2][x3];
}
int main()
{
    freopen("tower.in", "r", stdin);
    freopen("tower.out", "w", stdout);
    scanf("%d", &n);
    for (i = 1; i < n; i++)
        for (j = i + 1; j <= n; j++)
            scanf("%d", &cost[i][j]);
    cout << dfs(1, 1, 1) << endl;
    return 0;
}
