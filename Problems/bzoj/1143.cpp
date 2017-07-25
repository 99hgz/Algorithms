#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
bool used[110];
int belong[110];
bool line[110][110];
int ans, n, m, sl, b;
bool find(int x)
{
    for (int j = 1; j <= n; j++)
    {
        if (line[x][j] && (!used[j]))
        {
            used[j] = true;
            if ((belong[j] == 0) || (find(belong[j])))
            {
                belong[j] = x;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    scanf("%d%d", &n, &m);
    int x, y;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &x, &y);
        line[x][y] = true;
    }
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                line[i][j] = line[i][j] | (line[i][k] & line[k][j]);
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        memset(used, 0, sizeof(used));
        if (find(i))
            ans++;
    }
    printf("%d\n", n - ans);
    system("pause");
    return 0;
}