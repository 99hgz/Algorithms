/*
 * @key word:匈牙利算法
 * @已测试:https://www.luogu.org/problem/show?pid=1894#sub
 * @Author: hgz 
 * @Date: 2017-07-11 21:25:19 
 * @Last Modified by: hgz
 * @Last Modified time: 2017-07-11 21:29:53
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
bool used[210];
int belong[210];
bool line[210][210];
int ans, n, m, sl, b;
bool find(int x)
{
    for (int j = 1; j <= m; j++)
    {
        if (line[x][j] && (!used[j]))
        {
            used[j] = true;
            if ((belong[j] == 0) || (find(belong[j])))
            {
                belong[j] = x;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &sl);
        for (int j = 1; j <= sl; j++)
        {
            scanf("%d", &b);
            line[i][b] = true;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        memset(used, 0, sizeof(used));
        if (find(i))
            ans++;
    }
    printf("%d\n", ans);
    system("pause");
    return 0;
}