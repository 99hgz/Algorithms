#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, u, v, edge[51][51], pl[51], ans, del[51];

int main()
{
    srand(6666);
    scanf("%d", &n);
    while (~scanf("%d%d", &u, &v))
        edge[u][v] = edge[v][u] = 1;
    for (int i = 1; i <= n; i++)
        pl[i] = i;
    for (int i = 1; i <= 100000; i++)
    {
        memset(del, 0, sizeof del);
        random_shuffle(pl + 1, pl + 1 + n);
        int t = 0;
        for (int j = 1; j <= n; j++)
            if (!del[pl[j]])
            {
                t++;
                for (int k = j + 1; k <= n; k++)
                    if (!edge[pl[j]][pl[k]])
                        del[pl[k]] = true;
            }
        ans = max(ans, t);
    }
    printf("%d\n", ans);
    system("pause");
    return 0;
}