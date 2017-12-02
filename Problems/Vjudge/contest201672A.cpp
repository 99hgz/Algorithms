#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, m, used[50010], belong[50010], T, ans;
vector<int> vec[50010];
int calc(int x, int y)
{
    return ((x - 1) * m + y - 1);
}

void addedge(int x, int y)
{
    vec[x].push_back(y);
}

bool find(int x)
{
    for (int j = 0; j < vec[x].size(); j++)
    {
        int v = vec[x][j];
        if (used[v] != T)
        {
            used[v] = T;
            if ((belong[v] == 0) || (find(belong[v])))
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
    while (~scanf("%d%d", &n, &m))
    {
        memset(belong, 0, sizeof belong);
        memset(used, 0, sizeof used);
        T = 0;
        for (int i = 1; i <= n; i++)
        {
            vec[i].clear();

            int edges;
            scanf("%d", &edges);
            for (int j = 1; j <= edges; j++)
            {
                int tmp;
                scanf("%d", &tmp);
                addedge(i, tmp + n);
            }
        }
        ans = 0;
        for (int i = 1; i <= n; i++)
        {
            T++;
            if (find(i))
                ans++;
        }
        printf("%d\n", ans);
    }
    system("pause");
    return 0;
}