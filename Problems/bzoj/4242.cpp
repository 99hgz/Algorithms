#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int h, w, p, q;
char A[2010];
int x, y;
struct POS
{
    int x, y, dis;
};
queue<POS> Q;
struct BUILDING
{
    int id, dis;
} belong[2010][2010];
bool vis[2010][2010];
bool map[2010][2010];
struct BID
{
    int x, y, dis;
};
vector<BID> D[2010 * 2010];
int cx[5] = {0, 0, 0, -1, 1};
int cy[5] = {0, 1, -1, 0, 0};

struct GraphNode
{
    int v, w;
};

vector<GraphNode> vec2[200010];
int deep[200010], father[200010][20], st[200010][20], n, m, k, u, v;
int UnionFindSets_fa[200010];
int get_father(int x)
{
    return UnionFindSets_fa[x] == 0 ? x : UnionFindSets_fa[x] = get_father(UnionFindSets_fa[x]);
}

void ins(int x, int y, int dis)
{
    //printf("%d %d %d\n", dis, x, y);
    D[dis].push_back((BID){x, y, dis});
}

void addedgeTree(int u, int v, int w)
{
    vec2[u].push_back((GraphNode){v, w});
}

void dfs(int x, int fa, int w, int dep)
{
    deep[x] = dep;
    father[x][0] = fa;
    st[x][0] = w;
    for (int i = 0; i < vec2[x].size(); i++)
    {
        int v = vec2[x][i].v;
        if (fa != v)
        {
            dfs(v, x, vec2[x][i].w, dep + 1);
        }
    }
}

void init()
{
    for (int i = 1; i <= 15; i++)
    {
        for (int j = 1; j <= p; j++)
        {
            father[j][i] = -1;
        }
    }
    for (int i = 1; i <= 15; i++)
    {
        for (int j = 1; j <= p; j++)
        {
            if (father[j][i - 1] != -1)
            {
                father[j][i] = father[father[j][i - 1]][i - 1];
                st[j][i] = max(st[j][i - 1], st[father[j][i - 1]][i - 1]);
            }
        }
    }
}

int lca(int a, int b)
{
    if (get_father(a) != get_father(b))
        return -1;
    int res = 0;
    if (deep[a] < deep[b])
        swap(a, b);
    int st2 = floor(log(deep[a] - 1) / log(2));
    for (int i = st2; i >= 0; i--)
        if (deep[a] - (1 << i) >= deep[b])
        {
            res = max(res, st[a][i]);
            a = father[a][i];
        }
    if (a == b)
        return res;
    for (int i = st2; i >= 0; i--)
        if ((father[a][i] != -1) && (father[a][i] != father[b][i]))
        {
            res = max(res, st[a][i]);
            res = max(res, st[b][i]);
            a = father[a][i];
            b = father[b][i];
        }
    return max(st[b][0], max(res, st[a][0]));
}

int main()
{
    scanf("%d%d%d%d", &h, &w, &p, &q);
    for (int i = 1; i <= h; i++)
    {
        scanf("%s", A + 1);
        for (int j = 1; j <= w; j++)
            map[i][j] = (A[j] == '.');
    }
    for (int i = 1; i <= p; i++)
    {
        scanf("%d%d", &x, &y);
        Q.push((POS){x, y, 0});
        vis[x][y] = true;
        belong[x][y] = (BUILDING){i, 0};
    }
    while (!Q.empty())
    {
        POS from = Q.front();
        Q.pop();
        for (int i = 1; i <= 4; i++)
        {
            int tx = from.x + cx[i], ty = from.y + cy[i];
            if (!map[tx][ty])
                continue;
            //printf("%d %d %d %d\n", from.x, from.y, tx, ty);
            if (!vis[tx][ty])
            {
                vis[tx][ty] = true;
                belong[tx][ty] = (BUILDING){belong[from.x][from.y].id, from.dis + 1};
                Q.push((POS){tx, ty, from.dis + 1});
            }
            else if (belong[tx][ty].id != belong[from.x][from.y].id)
            {
                ins(belong[tx][ty].id, belong[from.x][from.y].id, from.dis + belong[tx][ty].dis);
            }
        }
    }

    int buildingblock = p;
    for (int i = 0; i <= h * w; i++)
    {
        if (buildingblock == 1)
            break;
        for (int j = 0; j < D[i].size(); j++)
        {
            int fax = get_father(D[i][j].x);
            int fay = get_father(D[i][j].y);
            if (fax != fay)
            {
                UnionFindSets_fa[fax] = fay;
                buildingblock--;
                addedgeTree(D[i][j].x, D[i][j].y, D[i][j].dis);
                addedgeTree(D[i][j].y, D[i][j].x, D[i][j].dis);
            }
        }
    }
    for (int i = 1; i <= p; i++)
    {
        if (!deep[i])
            dfs(i, 0, 0, 1);
    }

    init();

    for (int i = 1; i <= q; i++)
    {
        scanf("%d%d", &u, &v);
        printf("%d\n", lca(u, v));
    }

    system("pause");
    return 0;
}