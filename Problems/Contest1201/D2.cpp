#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

const int MAXN = 1010, MAXE = 2020;
int head[MAXN], Next[MAXE], son[MAXE], dis[MAXE];
int f[MAXN][50];
bool flag[MAXN];
int tot, n;

void add_e(int x, int y, int z)
{
    tot++;
    Next[tot] = head[x];
    head[x] = tot;
    son[tot] = y;
    dis[tot] = z;
}

void init()
{
    int x, y, z;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &x);
        f[i][1 << x - 1] = 0;
    }
    for (int i = i; i < n; i++)
    {
        scanf("%d%d%d", &x, &y, &z);
        add_e(x, y, z);
        add_e(y, x, z);
    }
}

void dfs(int u)
{
    flag[u] = true;
    for (int i = head[u]; i; i = Next[i])
    {
        int v = son[i];
        if (!flag[v])
        {
            dfs(v);
            for (int j = 0; j <= 31; j++)
                for (int k = 0; k <= 31; k++)
                    f[u][j | k] = min(f[u][j | k], f[u][j] + f[v][k] + dis[i]);
            f[u][31] = min(f[u][31], f[v][31]);
        }
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        memset(f, 0x3f, sizeof(f));
        memset(head, 0, sizeof(head));
        tot = 0;
        memset(flag, false, sizeof(flag));
        init();
        dfs(1);
        printf("%d\n", f[1][31]);
    }
    //system("pause");
    return 0;
}
