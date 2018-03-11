#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
typedef long double ld;
#define eps 1e-15
ld f[310][310], sum;
int n, m, p, q, u, v, edge[310][310], du[310];

int main()
{
    scanf("%d%d%d%d", &n, &m, &p, &q);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        edge[u][v]++, edge[v][u]++;
        du[u]++, du[v]++;
    }
    f[1][n + 1] = 1;
    for (int i = 1; i <= n; i++)
    {
        f[i][i] = 1;
        for (int j = 1; j <= n; j++)
            if (edge[i][j])
                f[i][j] = ((ld)p / q - 1) / du[j] * edge[i][j];
    }
    for (int i = 1; i <= n; i++)
    {
        int t = i;
        for (int j = i; j <= n; j++)
            if (fabs(f[j][i]) > eps)
                t = j;
        for (int j = 1; j <= n + 1; j++)
            swap(f[i][j], f[t][j]);
        for (int j = 1; j <= n; j++)
            if (j != i && fabs(f[j][i]) > eps)
            {
                ld bs = f[j][i] / f[i][i];
                for (int k = 1; k <= n + 1; k++)
                    f[j][k] -= f[i][k] * bs;
            }
    }
    for (int i = 1; i <= n; i++)
        sum += (f[i][i] = f[i][n + 1] / f[i][i]);
    for (int i = 1; i <= n; i++)
        printf("%.9lf\n", (double)(f[i][i] / sum + eps));
    system("pause");
    return 0;
}