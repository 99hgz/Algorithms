/*
p[i,j]表示i节点的2^j倍祖先
p[i,j]=t[i] (j=0)
p[i,j]=p[p[i,j-1],j-1]  (j>0)
*/
#include <cmath>
#include <vector>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
using namespace std;
struct edge
{
    int point, dis;
};
vector<edge> hmap[50001];
int parent[50001];
bool vis[50001];
int deep[50001];
int toroot[50001];
int p[50001][40];
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

void dfs(int p, int deep1, int dis)
{
    //printf("%d %d %d\n", p, deep1, dis);
    vector<edge>::iterator it;
    deep[p] = deep1;
    toroot[p] = dis;
    for (it = hmap[p].begin(); it != hmap[p].end(); it++)
    {
        if (!vis[(*it).point])
        {
            vis[(*it).point] = true;
            parent[(*it).point] = p;
            dfs((*it).point, deep1 + 1, dis + (*it).dis);
        }
    }
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        memset(vis, 0, sizeof(vis));
        memset(parent, 0, sizeof(parent));
        //memset(vis, 0, sizeof(vis));
        int n, m, a, b, k;
        edge tmp;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
        {
            hmap[i].clear();
        }
        for (int i = 1; i < n; i++)
        {
            scanf("%d%d%d", &a, &b, &k);
            tmp.point = b;
            tmp.dis = k;
            hmap[a].push_back(tmp);
            tmp.point = a;
            hmap[b].push_back(tmp);
        }
        vis[1] = true;
        dfs(1, 1, 0);
        init(n);
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d", &a, &b);
            int tmp = lca(a, b);
            //printf("lca=%d\n", tmp);
            printf("%d\n", toroot[a] + toroot[b] - 2 * toroot[tmp]);
        }
    }
    //system("pause");
}