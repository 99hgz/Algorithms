#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int change[1 << 22][2];
ll f[12][1 << 13];
int num = 0;
int n, m;
void init(int d, int to, int from)
{
    //printf("%d %d %d\n", d, to, from);
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
    while ((scanf("%d%d", &n, &m)) && ((n != 0) && (m != 0)))
    {
        num = 0;
        init(0, 0, 0);
        memset(f, 0, sizeof(f));
        f[0][0] = 1;
        for (j = 1; j <= n; j++)
        {
            for (i = 0; i < num; i++)
            {
                f[j][change[i][1]] += f[j - 1][change[i][0]];
            }
        }
        printf("%lld\n", f[n][0]);
    }
    //system("pause");
    return 0;
}
