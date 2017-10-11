#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

int stacktop, n, b, u, v, S[1010], belong[1010], province, province_center[1010];
vector<int> vec[1010];
void addedge(int u, int v)
{
    vec[u].push_back(v);
}

void dfs(int x, int fa)
{
    int fastacktop = stacktop;
    for (int i = 0; i < vec[x].size(); i++)
    {
        int v = vec[x][i];
        if (v != fa)
        {
            dfs(v, x);
            if (stacktop - fastacktop >= b)
            {
                province++;
                while (stacktop > fastacktop)
                    belong[S[stacktop--]] = province;
                province_center[province] = x;
            }
        }
    }
    S[++stacktop] = x;
}

int main()
{
    scanf("%d%d", &n, &b);
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }
    stacktop = 1;
    dfs(1, 1);
    while (stacktop >= 1)
    {
        belong[S[stacktop--]] = province;
    }
    province_center[province] = 1;
    printf("%d\n", province);
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", belong[i]);
    }
    printf("\n");
    for (int i = 1; i <= province; i++)
    {
        printf("%d ", province_center[i]);
    }
    printf("\n");
    system("pause");
    return 0;
}