#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int aa[310][310];
int n, m, a[110][310][310], x, y, c, x1, x2, y1, y2, q, cases;
int lowbit(int i) { return i & (-i); }

void update(int bh, int i, int j, int x)
{
    int tj;
    while (i <= 300)
    {
        tj = j;
        while (tj <= 300)
        {
            a[bh][i][tj] += x;
            tj += lowbit(tj);
        }
        i += lowbit(i);
    }
}

int sum(int bh, int i, int j)
{
    int tj, sum = 0;
    while (i > 0)
    {
        tj = j;
        while (tj > 0)
        {
            sum += a[bh][i][tj];
            tj -= lowbit(tj);
        }
        i -= lowbit(i);
    }
    return sum;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &aa[i][j]);
            update(aa[i][j], i, j, 1);
        }
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; i++)
    {
        scanf("%d", &cases);
        if (cases == 2)
        {
            scanf("%d%d%d%d%d", &x1, &x2, &y1, &y2, &c);
            printf("%d\n", sum(c, x2, y2) - sum(c, x2, y1 - 1) - sum(c, x1 - 1, y2) + sum(c, x1 - 1, y1 - 1));
        }
        else
        {
            scanf("%d%d%d", &x, &y, &c);
            update(c, x, y, 1);
            update(aa[x][y], x, y, -1);
            aa[x][y] = c;
        }
    }
    system("pause");
    return 0;
}