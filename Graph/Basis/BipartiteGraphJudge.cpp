/*
 * @key word:二分图判定
 * @已测试:http://hihocoder.com/problemset/problem/1121
 * @Author: hgz 
 * @Date: 2017-07-11 22:15:44 
 * @Last Modified by: hgz
 * @Last Modified time: 2017-07-11 22:16:13
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int a, b, n, m;
bool visited[10010], color[10010];
struct EDGE
{
    int to, w;
};
vector<EDGE> vec[10010];
bool dfs(int x)
{
    visited[x] = true;
    for (int i = 0; i < vec[x].size(); i++)
    {
        int v = vec[x][i].to;
        if (vec[x][i].w == 0)
            continue;
        if (!visited[v])
        {
            color[v] = !color[x];
            if (!dfs(v))
                return false;
        }
        else
        {
            if (color[v] == color[x])
                return false;
        }
    }
    return true;
}

bool check()
{
    memset(visited, 0, sizeof(visited));
    memset(color, 0, sizeof(color));
    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            color[i] = true;
            if (!dfs(i))
                return false;
        }
    }
    return true;
}

int main()
{
    int t;
    scanf("%d", &t);
    while (~scanf("%d%d", &n, &m))
    {
        for (int i = 1; i <= n; i++)
        {
            vec[i].clear();
        }
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d", &a, &b);
            vec[a].push_back((EDGE){b, 1});
            vec[b].push_back((EDGE){a, 1});
        }
        if (check())
            printf("Correct\n");
        else
            printf("Wrong\n");
    }

    system("pause");
    return 0;
}