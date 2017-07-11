#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int a, b, n, m, PD, w;
bool visited[20010], color[20010];
struct EDGE
{
    int to, w;
};
vector<EDGE> vec[20010];
vector<int> edges;
bool dfs(int x)
{
    visited[x] = true;
    for (int i = 0; i < vec[x].size(); i++)
    {
        int v = vec[x][i].to;
        if (vec[x][i].w <= PD)
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
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &a, &b, &w);
        vec[a].push_back((EDGE){b, w});
        vec[b].push_back((EDGE){a, w});
        edges.push_back(w);
    }
    PD = 0;
    if (check())
    {
        printf("%d\n", 0);
        return 0;
    }
    sort(edges.begin(), edges.end());
    int l = 0, r = m - 1, mid;
    while (l < r)
    {
        mid = (l + r) / 2;
        PD = edges[mid];
        if (!check())
            l = mid + 1;
        else
            r = mid;
        //printf("%d %d\n", l, r);
    }
    mid = (l + r) / 2;
    PD = edges[mid];
    printf("%d\n", PD);
    system("pause");
    return 0;
}