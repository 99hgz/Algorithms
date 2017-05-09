#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;

struct Node
{
    int h;
    int k;
    int v;
} node[101];
vector<int> kinds[11];
int dp[11][10010];
int main()
{
    int t, n, m, l, k, j;
    while (~scanf("%d%d%d", &n, &m, &k))
    {
        //scanf("%d%d%d", &n, &m, &k);
        int i;
        memset(dp, -1, sizeof(dp));
        memset(dp[0], 0, sizeof(dp[0]));
        memset(node, 0, sizeof(node));
        for (i = 0; i <= k; i++)
        {
            kinds[i].clear();
        }
        for (i = 1; i <= n; i++)
        {
            scanf("%d%d%d", &node[i].k, &node[i].v, &node[i].h);
            kinds[node[i].k].push_back(i);
        }
        for (i = 1; i <= k; i++)
        {
            for (j = 0; j < kinds[i].size(); j++)
            {
                for (l = m; l >= node[kinds[i][j]].v; l--)  
                {
                    if (dp[i][l - node[kinds[i][j]].v] != -1)
                        dp[i][l] = max(dp[i][l], dp[i][l - node[kinds[i][j]].v] + node[kinds[i][j]].h);
                    if (dp[i - 1][l - node[kinds[i][j]].v] != -1)
                        dp[i][l] = max(dp[i][l], dp[i - 1][l - node[kinds[i][j]].v] + node[kinds[i][j]].h);
                }
            }
        }
        if (dp[k][m] != -1)
        {
            printf("%d\n", dp[k][m]);
        }
        else
        {
            printf("Impossible\n");
        }
    }
    //system("pause");
    return 0;
}
