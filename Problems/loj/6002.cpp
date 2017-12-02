#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, m, used[50010], belong[50010], T, ans;
vector<int> vec[50010];
int Next[50010];
bool vis[50010];
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
                Next[x] = v;
                belong[v] = x;
                return true;
            }
        }
    }
    return false;
}

void print(int x)
{
    if (x == 0 || vis[x])
    {
        printf("\n");
        return;
    }
    vis[x] = true;
    printf("%d ", x);
    print(Next[x]);
}

int main()
{
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        addedge(u, v);
    }
    for (int i = 1; i <= n; i++)
        reverse(vec[i].begin(), vec[i].end());
    ans = 0;
    for (int i = 1; i <= n; i++)
    {
        T++;
        if (find(i))
            ans++;
    }

    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
            print(i);
    }
    printf("%d\n", n - ans);

    system("pause");
    return 0;
}