#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int change[1 << 10][2];
int f[12][1 << 11];
int num = 0;
int n, m;
void init(int d, int to, int from)
{
    printf("%d %d %d\n", d, to, from);
    if (m < d)
    {
        return;
    }
    if (m == d)
    {
        change[num][1] = to;
        change[num++][0] = from;
        return;
    }
    init(d + 1, (to << 1) + 1, (from << 1));
    init(d + 1, (to << 1), (from << 1) + 1);
    init(d + 2, (to << 2), (from << 2));
}

int main()
{
    int i, j;
    scanf("%d%d", &n, &m);
    init(0, 0, 0);
    f[0][0] = 1;
    for (j = 1; j <= n; j++)
    {
        for (i = 0; i < num; i++)
        {
            f[j][change[i][1]] += f[j - 1][change[i][0]];
        }
    }
    printf("%d\n", f[n][(1 << m) - 1]);
    system("pause");
    return 0;
}