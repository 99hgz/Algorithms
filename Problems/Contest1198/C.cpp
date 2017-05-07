#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

struct Node
{
    int h;
    int v;
} node[400];
int dp[400];
int main()
{
    int t, n, m, l;

    scanf("%d%d", &m, &n);
    int i;
    for (i = 1; i <= n; i++)
        scanf("%d%d", &node[i].v, &node[i].h);
    for (i = 1; i <= n; i++)
    {
        for (l = m; l >= node[i].v; l--)
            dp[l] = max(dp[l], dp[l - node[i].v] + node[i].h);
    }
    printf("%d\n", dp[m]);
    //system("pause");
    return 0;
}
