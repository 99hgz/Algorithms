#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
int max(int x, int y) { return x > y ? x : y; }
int f[10010];
vector<int> to[10010];
int main()
{
    int m, n, i, j, p, t;
    scanf("%d%d", &m, &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d%d", &p, &t);
        to[p].push_back(p + t - 1);
    }
    memset(f, 0xff, sizeof(f));
    f[0] = 0;
    for (i = 1; i <= m; i++)
    {
        if (f[i - 1] >= 0)
        {
            if (to[i].size())
            {
                for (j = 0; j < to[i].size(); j++)
                {
                    f[to[i][j]] = max(f[to[i][j]], f[i - 1]);
                }
            }
            else
            {
                f[i] = max(f[i], f[i - 1] + 1);
            }
        }
    }
    printf("%d\n", f[m]);
    //system("pause");
    return 0;
}