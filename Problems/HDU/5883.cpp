#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
int n, m, mark[100100], u, v, du[100100], blocks, oddv, all;
int fa[100100];

int get_father(int x)
{
    return fa[x] == 0 ? x : fa[x] = get_father(fa[x]);
}
bool un(int u, int v)
{
    int fa1 = get_father(u);
    int fb = get_father(v);
    if (fa1 == fb)
        return false;
    fa[fa1] = fb;
    return true;
}

int main()
{

    int t;
    scanf("%d", &t);
    while (~scanf("%d%d", &n, &m))
    {
        memset(fa, 0, sizeof fa);
        memset(du, 0, sizeof du);
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &mark[i]);
        }
        blocks = n;
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d", &u, &v);
            du[u]++;
            du[v]++;
            if (un(u, v))
                blocks--;
        }
        int zp = 0;
        for (int i = 1; i <= n; i++)
        {
            if (du[i] == 0)
                zp++;
        }
        if ((blocks - zp) > 1)
        {
            printf("Impossible\n");
            continue;
        }
        oddv = 0;
        all = 0;
        for (int i = 1; i <= n; i++)
        {
            if (du[i] == 0)
                continue;
            if ((du[i] % 2) == 1)
                oddv++;
            if ((((du[i] + 1) / 2) % 2) == 1)
            {
                all ^= mark[i];
            }
        }
        if ((oddv != 0) && (oddv != 2))
        {
            printf("Impossible\n");
        }
        else
        {
            if (oddv == 2)
            {
                printf("%d\n", all);
            }
            else
            {
                int max1 = 0;
                for (int i = 1; i <= n; i++)
                {
                    if (du[i] == 0)
                        continue;
                    if ((all ^ mark[i]) > max1)
                        max1 = (all ^ mark[i]);
                }
                printf("%d\n", max1);
            }
        }
    }
    return 0;
}
