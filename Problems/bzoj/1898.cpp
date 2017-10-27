#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

struct MATRIX
{
    int n, m;
    int arr[55][55];
} map, bridge, step12[20], E, ans, tmp;
int n, m, s, t, x, y, fishnum, turn[55], fish[55][55], step[55];
ll k;
MATRIX operator*(MATRIX a, MATRIX b)
{
    MATRIX c;
    for (int i = 1; i <= a.n; i++)
        for (int j = 1; j <= a.m; j++)
        {
            c.arr[i][j] = 0;
            for (int k = 1; k <= a.m; k++)
            {
                c.arr[i][j] += a.arr[i][k] * b.arr[k][j];
                c.arr[i][j] %= 10000;
            }
        }
    c.n = a.n;
    c.m = b.m;
    return c;
}

MATRIX power(MATRIX a, ll b)
{
    MATRIX ans = E;
    while (b > 0)
    {
        if (b & 1)
            ans = ans * a;
        a = a * a;
        b >>= 1;
    }
    return ans;
}

int main()
{
    scanf("%d%d%d%d%lld", &n, &m, &s, &t, &k);
    s++, t++;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &x, &y);
        x++, y++;
        map.arr[x][y] = 1;
        map.arr[y][x] = 1;
    }
    E.n = n;
    E.m = n;
    for (int i = 1; i <= n; i++)
    {
        E.arr[i][i] = 1;
    }
    map.n = n;
    map.m = n;
    scanf("%d", &fishnum);
    for (int i = 1; i <= fishnum; i++)
    {
        scanf("%d", &turn[i]);
        for (int j = 1; j <= turn[i]; j++)
        {
            scanf("%d", &fish[i][j]);
            fish[i][j]++;
        }
        step[i] = 1;
    }
    bridge.arr[1][s] = 1;
    bridge.n = 1;
    bridge.m = n;

    step12[0] = E;

    for (int i = 1; i <= 12; i++)
    {
        step12[i] = step12[i - 1] * map;
        tmp = E;
        for (int j = 1; j <= fishnum; j++)
        {
            step[j]++;
            if (step[j] > turn[j])
                step[j] = 1;

            tmp.arr[fish[j][step[j]]][fish[j][step[j]]] = 0;
        }
        step12[i] = step12[i] * tmp;
    }

    ans = power(step12[12], k / (ll)12);

    //printf("%d\n", (bridge * ans).arr[1][t]);

    ans = ans * step12[k % (ll)12];

    ans = bridge * ans;

    printf("%d\n", ans.arr[1][t]);

    system("pause");
    return 0;
}