#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

bool visited[110][110];
int a[110][110];
int n, m;
int gx[5] = {0, 0, 0, 1, -1};
int gy[5] = {0, -1, 1, 0, 0};
bool dfs(int i, int j, int c)
{
    //printf("%d %d\n", i, j);
    visited[i][j] = true;
    bool res = false;
    if ((i == 1) || (i == n) || (j == 1) || (j == m))
        res = true;

        for (int k = 1; k <= 4; k++)
    {
        int tx = i + gx[k];
        int ty = j + gy[k];
        if ((tx < 1) || (ty < 1) || (tx > n) || (ty > m))
            continue;
        if ((a[tx][ty] == c) && (!visited[tx][ty]))
            res = res || dfs(tx, ty, c);
    }
    return res;
}

bool pd1()
{
    memset(visited, 0, sizeof visited);
    int ans1 = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if ((a[i][j] == 1) && (!visited[i][j]))
            {
                if (ans1 == 1)
                    return false;
                ans1++;
                dfs(i, j, 1);
            }
        }
    }
    if (ans1 == 0)
        return false;
    int block = 0;
    bool unrs = false;
    memset(visited, 0, sizeof visited);
    for (int i = 1; i <= n; i++)
    {
        int l1 = 0, r1 = 0;
        for (int j = 1; j <= m; j++)
        {
            if (a[i][j] == 1)
            {
                l1 = j;
                break;
            }
        }
        for (int j = m; j >= 1; j--)
        {
            if (a[i][j] == 1)
            {
                r1 = j;
                break;
            }
        }
        if (l1 == 0)
            continue;
        for (int j = l1; j <= r1; j++)
        {
            if ((a[i][j] == 0) && (!visited[i][j]))
            {
                if (!dfs(i, j, 0))
                    block++;
            }
        }
    }
    if (block == 1)
        return true;
    else
        return false;
}

bool pd2()
{
    memset(visited, 0, sizeof visited);
    int ans1 = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if ((a[i][j] == 1) && (!visited[i][j]))
            {
                if (ans1 == 1)
                    return false;
                ans1++;
                dfs(i, j, 1);
            }
        }
    }
    if (ans1 == 0)
        return false;
    int block = 0;
    bool unrs = false;
    memset(visited, 0, sizeof visited);
    for (int i = 1; i <= n; i++)
    {
        int l1 = 0, r1 = 0;
        for (int j = 1; j <= m; j++)
        {
            if (a[i][j] == 1)
            {
                l1 = j;
                break;
            }
        }
        for (int j = m; j >= 1; j--)
        {
            if (a[i][j] == 1)
            {
                r1 = j;
                break;
            }
        }
        if (l1 == 0)
            continue;
        for (int j = l1; j <= r1; j++)
        {
            if ((a[i][j] == 0) && (!visited[i][j]))
            {
                if (!dfs(i, j, 0))
                    block++;
            }
        }
    }
    if (block > 0)
        return false;
    else
        return true;
}

int main()
{
    int t;
    while (~scanf("%d%d", &n, &m))
    {

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                scanf("%1d", &a[i][j]);
            }
        }
        if (pd1())
        {
            printf("0\n");
        }
        else
        {
            if (pd2())
            {
                printf("1\n");
            }
            else
            {
                printf("-1\n");
            }
        }
    }
    system("pause");
    return 0;
}