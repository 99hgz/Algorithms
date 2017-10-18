#include <cmath>
#include <vector>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
using namespace std;

vector<int> hmap[500010];
int parent[500010];
bool vis[500010];
int deep[500010];
int p[500010][20];
void init(int n)
{
    int st;
    st = floor(log(n) / log(2));
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= st; j++)
            p[i][j] = -1;
    for (int i = 1; i <= n; i++)
        p[i][0] = parent[i];
    for (int j = 1; j <= st; j++)
        for (int i = 1; i <= n; i++)
            if (p[i][j - 1] != -1) //!
                p[i][j] = p[p[i][j - 1]][j - 1];
}
int lca(int a, int b)
{
    if (deep[a] < deep[b])
        swap(a, b);
    int st = floor(log(deep[a] - 1) / log(2));
    /*printf("%d \n", st);
    printf("%d %d\n", a, b);*/
    for (int i = st; i >= 0; i--)
        if (deep[a] - (1 << i) >= deep[b])
        {
            a = p[a][i];
            //printf("%d %d\n", a, b);
        }
    if (a == b)
        return a;
    //printf("%d %d", a, b);
    for (int i = st; i >= 0; i--)
        if ((p[a][i] != -1) && (p[a][i] != p[b][i]))
        {
            a = p[a][i];
            b = p[b][i];
        }
    return parent[a];
}

void dfs(int p, int deep1)
{
    deep[p] = deep1;
    for (int it = 0; it < hmap[p].size(); it++)
    {
        if (!vis[hmap[p][it]])
        {
            vis[hmap[p][it]] = true;
            parent[hmap[p][it]] = p;
            dfs(hmap[p][it], deep1 + 1);
        }
    }
}

int get_dis(int a, int b)
{
    int LCA = lca(a, b);
    return deep[a] + deep[b] - 2 * deep[LCA];
}

int main()
{
    int n, m, a, b, k;
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &a, &b);
        hmap[a].push_back(b);
        hmap[b].push_back(a);
    }
    vis[1] = true;
    dfs(1, 1);
    init(n);
    int c;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        int tmp1 = lca(a, b), tmp2 = lca(b, c), tmp3 = lca(a, c);
        int lca1 = tmp1, lca2;
        if (tmp2 != lca1)
            lca2 = tmp2;
        else
            lca2 = tmp3;
        int dis1 = get_dis(lca1, a) + get_dis(lca1, b) + get_dis(lca1, c);
        int dis2 = get_dis(lca2, a) + get_dis(lca2, b) + get_dis(lca2, c);
        printf("%d %d\n", dis1 < dis2 ? lca1 : lca2, min(dis1, dis2));
    }
    system("pause");
}