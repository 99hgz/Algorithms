#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
bool used[1010];
int belong[1010];
bool line[1010][1010];
int ans, n, m, sl, a, b;
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
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &a, &b);
        line[a][b] = true;
        line[b][a] = true;
    }
    for (int i = 1; i <= n; i++)
    {
        memset(used, 0, sizeof(used));
        if (find(i))
            ans++;
    }
    printf("%d\n", ans);
    system("pause");
    return 0;
}