#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
#define eps 1e-8
int n, m, op, tot, q[21], idx[21], idy[21];
double a[21][21], A[21];

void Pivot(int x, int y)
{
    swap(idy[x], idx[y]);
    double tmp = a[x][y];
    a[x][y] = 1 / a[x][y];
    for (int i = 0; i <= n; i++)
    {
        if (y != i)
            a[x][i] /= tmp;
    }
    tot = 0;
    for (int i = 0; i <= n; i++)
    {
        if (i != y && (a[x][i] > eps || a[x][i] < -eps))
            q[++tot] = i;
    }
    for (int i = 0; i <= m; i++)
    {
        if ((x == i) || (a[i][y] < eps && a[i][y] > -eps))
            continue;
        for (int j = 1; j <= tot; j++)
            a[i][q[j]] -= a[x][q[j]] * a[i][y];
        a[i][y] = -a[i][y] / tmp;
    }
}
int main()
{
    scanf("%d%d%d", &n, &m, &op);
    for (int i = 1; i <= n; i++)
        scanf("%lf", &a[0][i]);
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
            scanf("%lf", &a[i][j]);
        scanf("%lf", &a[i][0]);
    }
    for (int i = 1; i <= n; i++)
        idx[i] = i;
    for (int i = 1; i <= m; i++)
        idy[i] = i + n;
    while (1)
    {
        int x = 0, y = 0;
        for (int i = 1; i <= m; i++)
            if (a[i][0] < -eps && ((!x) || (rand() & 1)))
                x = i;
        if (!x)
            break;
        for (int i = 1; i <= n; i++)
            if (a[x][i] < -eps && ((!y) || (rand() & 1)))
                y = i;
        if (!y)
        {
            printf("Infeasible\n");
            return 0;
        }
        Pivot(x, y);
    }
    while (1)
    {
        int x = 0, y = 0;
        double mn = 1e15;
        for (int i = 1; i <= n; i++)
            if (a[0][i] > eps)
            {
                y = i;
                break;
            }
        if (!y)
            break;
        for (int i = 1; i <= m; i++)
            if (a[i][y] > eps && a[i][0] / a[i][y] < mn)
                mn = a[i][0] / a[i][y], x = i;
        if (!x)
        {
            printf("Unbounded\n");
            return 0;
        }
        Pivot(x, y);
    }
    printf("%.8lf\n", -a[0][0]);
    if (!op)
        return 0;
    for (int i = 1; i <= m; i++)
        if (idy[i] <= n)
            A[idy[i]] = a[i][0];
    for (int i = 1; i <= n; i++)
        printf("%.8lf%c", A[i], i == n ? '\n' : ' ');
    system("pause");
    return 0;
}