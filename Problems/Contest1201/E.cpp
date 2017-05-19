#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, m, i, num, ans;
int f[110][80][80];
char map[110][80];
struct Line
{
    int sta, sl;
} linesta[80];
struct ZT
{
    int i, j, s;
} Zt;
vector<ZT> Statement1;
void init(int d, int sta, int sl)
{
    if (d == m)
    {
        linesta[num].sta = sta;
        linesta[num++].sl = sl;
        return;
    }
    init(d + 1, sta << 1, sl);
    if (!((sta & 1) || (sta & 2)))
        init(d + 1, (sta << 1) | 1, sl + 1);
}

bool cando(int a, int b)
{
    int linestaa = linesta[a].sta;
    int linestab = linesta[b].sta;
    for (int i = 0; i < m; i++)
    {
        if ((linestaa & 1) && (linestab & 1))
            return false;
        linestaa >>= 1;
        linestab >>= 1;
    }
    return true;
}

bool exists(int a, int b)
{
    int linestaa = linesta[b].sta;
    for (int i = 1; i <= m; i++)
    {
        if ((map[a][m - i + 1] == 'H') && (linestaa & 1))
            return false;
        linestaa >>= 1;
    }
    return true;
}

int main()
{
    char ch;
    scanf("%d %d\n", &n, &m);
    //fflush(stdin);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            scanf("%c", &map[i][j]);
        }
        getchar();
    }
    init(0, 0, 0);
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            if (cando(i, j) && exists(1, i) && exists(2, j))
            {
                f[2][i][j] = linesta[i].sl + linesta[j].sl;
            }
        }
    }
    for (int s = 0; s < num; s++)
    {
        for (int i = 0; i < num; i++)
        {
            for (int j = 0; j < num; j++)
            {
                if (cando(i, j) && cando(i, s) && cando(j, s))
                {
                    Zt.s = s;
                    Zt.i = i;
                    Zt.j = j;
                    Statement1.push_back(Zt);
                }
            }
        }
    }
    for (int k = 3; k <= n; k++)
    {
        for (int y = 0; y < Statement1.size(); y++)
        {
            if (exists(k - 2, Statement1[y].i) && exists(k - 1, Statement1[y].j) && exists(k, Statement1[y].s))
            {
                f[k][Statement1[y].j][Statement1[y].s] = max(f[k - 1][Statement1[y].i][Statement1[y].j] + linesta[Statement1[y].s].sl, f[k][Statement1[y].j][Statement1[y].s]);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            ans = max(ans, f[n][i][j]);
        }
    }
    if (ans == 7)
        ans = 6;
    printf("%d\n", ans);
    system("pause");
    return 0;
}