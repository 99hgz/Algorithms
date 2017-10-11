#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, m, a[210][210], used[50010], belong[50010], T, total, ans;
vector<int> vec[50010];
int cx[9] = {0, -1, -1, 1, 1, -2, -2, 2, 2};
int cy[9] = {0, 2, -2, 2, -2, 1, -1, 1, -1};
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
    scanf("%d", &n);
    m = n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            scanf("%1d", &a[i][j]);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (a[i][j])
                continue;
            total++;
            if ((i ^ j) & 1)
            {
                for (int fx = 1; fx <= 8; fx++)
                {
                    int tx = i + cx[fx], ty = j + cy[fx];
                    if (tx < 1 || tx > n || ty < 1 || ty > m)
                        continue;
                    if (a[tx][ty] == 0)
                        addedge(calc(i, j), calc(tx, ty));
                }
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {

            T++;
            if ((i ^ j) & 1)
            {
                if (find(calc(i, j)))
                    ans++;
            }
        }
    }
    printf("%d\n", total - ans);
    system("pause");
    return 0;
}