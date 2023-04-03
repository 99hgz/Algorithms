#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int f[1010], b[1010], a[1010], n, m, sg;

int dfs(int x)
{
    if (f[x] != -1)
        return f[x];
    bool vis[15];
    memset(vis, 0, sizeof vis);
    for (int i = 1; i <= m; i++)
        if (x >= b[i])
            vis[dfs(x - b[i])] = 1;
        else
            break;
    int res = 0;
    for (int i = 0;; i++)
        if (!vis[i])
        {
            res = i;
            break;
        }
    return f[x] = res;
}

int main()
{
    memset(f, -1, sizeof f);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
        scanf("%d", &b[i]);
    sort(b + 1, b + 1 + m);
    for (int i = 1; i <= n; i++)
        sg ^= dfs(a[i]);
    if (sg)
    {
        printf("YES\n");
        bool flag = true;
        for (int i = 1; i <= n && flag; i++)
            for (int j = 1; j <= m; j++)
                if (a[i] >= b[j] && (sg ^ dfs(a[i]) ^ dfs(a[i] - b[j])) == 0)
                {
                    printf("%d %d\n", i, b[j]);
                    flag = false;
                    break;
                }
    }
    else
        printf("%s\n", "NO");
    system("pause");
    return 0;
}