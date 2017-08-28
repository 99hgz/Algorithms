#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
unsigned int A, B, C, a[3010][3010], xx[3010][3010], c[3010][3010], sum, ans;
int n, m, q, x, y, k;
inline unsigned int rng61()
{
    A ^= A << 16;
    A ^= A >> 5;
    A ^= A << 1;
    unsigned int t = A;
    A = B;
    B = C;
    C ^= t ^ A;
    return C;
}
int main()
{
    scanf("%d%d%d%u%u%u", &n, &m, &q, &A, &B, &C);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            a[i][j] = rng61();
    for (int i = 1; i <= n; i++)
    {
        unsigned int hzh = 0;
        for (int j = m; j >= 1; j--)
        {
            hzh += a[i][j];
            xx[i][j] = xx[i - 1][j + 1] + hzh;
            c[i][j] = c[i - 1][j] + hzh;
        }
    }
    for (int i = 1; i <= q; i++)
    {
        x = rng61() % n + 1;
        y = rng61() % m + 1;
        k = rng61() % min(x, y) + 1;
        sum = xx[x][y - k + 1] - xx[x - k][y + 1] - (c[x][y + 1] - c[x - k][y + 1]);
        ans = ans * 233 + sum;
    }
    printf("%u\n", ans);
    system("pause");
}