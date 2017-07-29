#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, m, a, b, t, ans;
bool dist[110][110], dist1[110][110];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &a, &b);
        dist[a][b] = true;
        dist1[b][a] = true;
    }
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                dist1[i][j] |= dist1[i][k] & dist1[k][j];
                dist[i][j] |= dist[i][k] & dist[k][j];
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        int t = 0;
        for (int j = 1; j <= n; j++)
        {

            if ((i != j) && ((dist[i][j]) | dist1[i][j]))
            {
                t++;
            }
        }
        if (t == n - 1)
            ans++;
    }
    printf("%d\n", ans);
    system("pause");
    return 0;
}