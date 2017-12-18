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
} E, zy;
int n, m, u, v, ans, t;
MATRIX operator*(MATRIX a, MATRIX b)
{
    MATRIX c;
    for (int i = 1; i <= a.n; i++)
        for (int j = 1; j <= b.m; j++)
        {
            c.arr[i][j] = 0;
            for (int k = 1; k <= a.m; k++)
            {
                c.arr[i][j] += a.arr[i][k] * b.arr[k][j];
                c.arr[i][j] %= 2017;
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
    scanf("%d%d", &n, &m);
    zy.n = zy.m = n + 1;
    E.n = 1;
    E.m = n + 1;
    for (int i = 1; i <= n; i++)
    {
        E.arr[1][1] = 1;
        zy.arr[i][i] = 1;
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        zy.arr[u][v] = 1;
        zy.arr[v][u] = 1;
    }
    for (int i = 1; i <= n + 1; i++)
        zy.arr[i][n + 1] = 1;
    scanf("%d", &t);
    zy = power(zy, t);
    E = E * zy;
    for (int i = 1; i <= n + 1; i++)
    {
        ans = (ans + E.arr[1][i]) % 2017;
        //printf("%d\n", E.arr[1][i]);
    }
    printf("%d\n", ans);
    system("pause");
}