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
vector<int> kinds[10];
int dp[10][10010];
int main()
{
    int t, n, m, l, k, j;
    scanf("%d%d%d", &n, &m, &k);
    int i;
    for (i = 1; i <= n; i++)
    {
        scanf("%d%d%d", &node[i].k, &node[i].v, &node[i].h);
        kinds[node[i].k].push_back(i);
    }
    for (i = 1; i <= k; i++)
    {
        for (j = 0; j < kinds[i].size(); j++)
        {
            for (l = m; l >= node[i].v; l--)
                dp[i][l] = max(dp[i][l], dp[i - 1][l - node[kinds[i][j]].v] + node[kinds[i][j]].h);
        }
    }
    printf("%d\n", dp[k][m]);
    system("pause");
    return 0;
}
