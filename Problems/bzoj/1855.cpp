#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int T, maxp, W;
struct Node
{
    int ap, bp, as, bs;
} day[2010];
int f[2010][2010];
int q[2010];
int main()
{
    scanf("%d%d%d", &T, &maxp, &W);
    for (int i = 1; i <= T; i++)
        scanf("%d%d%d%d", &day[i].ap, &day[i].bp, &day[i].as, &day[i].bs);
    memset(f, -0x3f, sizeof f);
    for (int i = 1; i <= T; i++)
    {
        for (int j = 0; j <= day[i].as; j++)
            f[i][j] = -j * day[i].ap;
        for (int j = 0; j <= maxp; j++)
            f[i][j] = max(f[i][j], f[i - 1][j]);
        if (i - W - 1 >= 0)
        {
            int head = 1, tail = 0;
            for (int j = 0; j <= maxp; j++)
            {
                while (head <= tail && q[head] < j - day[i].as)
                    head++;
                while (head <= tail && f[i - W - 1][j] + day[i].ap * j >= f[i - W - 1][q[tail]] + day[i].ap * q[tail])
                    tail--;
                q[++tail] = j;
                if (head <= tail)
                    f[i][j] = max(f[i][j], f[i - W - 1][q[head]] - day[i].ap * (j - q[head]));
            }
            head = 1, tail = 0;
            for (int j = maxp; j >= 0; j--)
            {
                while (head <= tail && q[head] > j + day[i].bs)
                    head++;
                while (head <= tail && f[i - W - 1][j] + day[i].bp * j >= f[i - W - 1][q[tail]] + day[i].bp * q[tail])
                    tail--;
                q[++tail] = j;
                if (head <= tail)
                    f[i][j] = max(f[i][j], f[i - W - 1][q[head]] + day[i].bp * (q[head] - j));
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= maxp; i++)
    {
        ans = max(ans, f[T][i]);
    }
    printf("%d\n", ans);
    system("pause");
    return 0;
}