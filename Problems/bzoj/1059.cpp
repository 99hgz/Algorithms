#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
vector<int> vec[210];
bool vis[210];
int belong[210], n, flag;
bool dfs(int x)
{
    for (int i = 0; i < vec[x].size(); i++)
    {
        int v = vec[x][i];
        if (!vis[v])
        {
            vis[v] = true;
            if (!belong[v] || dfs(belong[v]))
            {
                belong[v] = x;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        memset(belong, 0, sizeof belong);
        for (int i = 1; i <= n; i++)
        {
            vec[i].clear();
            for (int j = 1; j <= n; j++)
            {
                scanf("%d", &flag);
                if (flag)
                    vec[i].push_back(j);
            }
        }
        int cnt = 0;
        for (int i = 1; i <= n; i++)
        {
            memset(vis, 0, sizeof vis);
            if (dfs(i))
                cnt++;
        }
        if (cnt == n)
            printf("Yes\n");
        else
            printf("No\n");
    }
    system("pause");
    return 0;
}