#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxn = 2100;
int a[maxn][maxn], b[maxn][maxn], c[maxn][maxn], d[maxn][maxn];
int n, m;

int lowbit(int i) { return i & (-i); }

void origin_update(int a[maxn][maxn], int i, int j, int x)
{
    int tj;
    while (i <= n)
    {
        tj = j;
        while (tj <= m)
        {
            a[i][tj] += x;
            tj += lowbit(tj);
        }
        i += lowbit(i);
    }
}

int origin_sum(int a[maxn][maxn], int i, int j)
{
    int tj, sum = 0;
    while (i > 0)
    {
        tj = j;
        while (tj > 0)
        {
            sum += a[i][tj];
            tj -= lowbit(tj);
        }
        i -= lowbit(i);
    }
    return sum;
}

int sum(int x, int y)
{
    return (x + 1) * (y + 1) * origin_sum(a, x, y) - (y + 1) * origin_sum(b, x, y) - (x + 1) * origin_sum(c, x, y) + origin_sum(d, x, y);
}
void update(int x1, int y1, int x2, int y2, int w)
{
    origin_update(a, x1, y1, w);
    origin_update(a, x2 + 1, y1, -w);
    origin_update(a, x1, y2 + 1, -w);
    origin_update(a, x2 + 1, y2 + 1, w);
    origin_update(b, x1, y1, w * x1);
    origin_update(b, x2 + 1, y1, -w * (x2 + 1));
    origin_update(b, x1, y2 + 1, -w * x1);
    origin_update(b, x2 + 1, y2 + 1, w * (x2 + 1));
    origin_update(c, x1, y1, w * y1);
    origin_update(c, x2 + 1, y1, -w * y1);
    origin_update(c, x1, y2 + 1, -w * (y2 + 1));
    origin_update(c, x2 + 1, y2 + 1, w * (y2 + 1));
    origin_update(d, x1, y1, w * x1 * y1);
    origin_update(d, x2 + 1, y1, -w * (x2 + 1) * y1);
    origin_update(d, x1, y2 + 1, -w * x1 * (y2 + 1));
    origin_update(d, x2 + 1, y2 + 1, w * (x2 + 1) * (y2 + 1));
}

int main()
{
    int x1, y1, x2, y2, w;
    char ch;
    scanf("%c %d %d\n", &ch, &n, &m);
    while (scanf("%c", &ch) != EOF)
    {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        if (ch == 'L')
        {
            scanf("%d\n", &w);
            update(x1, y1, x2, y2, w);
        }
        else
        {
            //scanf("\n");
            printf("%d\n", sum(x2, y2) - sum(x1 - 1, y2) - sum(x2, y1 - 1) + sum(x1 - 1, y1 - 1));
        }
    }
    return 0;
    //system("pause");
}