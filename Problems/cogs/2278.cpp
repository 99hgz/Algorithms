#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;

int n, m, u, v, w;
struct PATH
{
    int v, w;
};
vector<PATH> vec[200010];
int size[200010], f[200010], root, ans;
bool vis[200010];
int f1[200010][2], st[200010][20], deep[200010], Dis[200010][20], cnt[200010], Root, father[200010];
int color[200010];
void addedge(int u, int v, int w)
{
    vec[u].push_back((PATH){v, w});
}

//*********************LCA

void lca_dfs(int x, int fa, int depth)
{
    st[x][0] = fa;
    deep[x] = depth;
    for (auto P : vec[x])
        if (P.v != fa)
        {
            lca_dfs(P.v, x, depth + 1);
            Dis[P.v][0] = P.w;
        }
}

void init_st()
{
    int deep = floor(log(n) / log(2));
    for (int j = 1; j <= deep; j++)
        for (int i = 1; i <= n; i++)
            if (st[i][j - 1] != -1)
            {
                st[i][j] = st[st[i][j - 1]][j - 1];
                Dis[i][j] = Dis[i][j - 1] + Dis[st[i][j - 1]][j - 1];
            }
}

int lca(int a, int b)
{
    if (deep[a] < deep[b])
        swap(a, b);
    int res = 0;
    int depth = floor(log(deep[a] - 1) / log(2));
    for (int i = depth; i >= 0; i--)
        if (deep[a] - (1 << i) >= deep[b])
        {
            res += Dis[a][i];
            a = st[a][i];
        }
    if (a == b)
        return res;
    for (int i = depth; i >= 0; i--)
        if ((st[a][i] != -1) && (st[a][i] != st[b][i]))
        {
            res += Dis[a][i] + Dis[b][i];
            a = st[a][i];
            b = st[b][i];
        }
    return res + Dis[a][0] + Dis[b][0];
}

//*************************

void getroot(int treesize, int x, int fa)
{
    size[x] = 1, f[x] = 0;
    for (auto P : vec[x])
        if ((P.v != fa) && (!vis[P.v]))
        {
            getroot(treesize, P.v, x);
            size[x] += size[P.v];
            f[x] = max(f[x], size[P.v]);
        }
    f[x] = max(f[x], treesize - size[x]);
    if (f[x] < f[root])
        root = x;
}

int getsize(int x, int fa)
{
    int res = 1;
    for (auto P : vec[x])
        if ((P.v != fa) && (!vis[P.v]))
            res += getsize(P.v, x);
    return res;
}

void solve(int x, int fa)
{
    //printf("split:%d->%d\n", x, fa);
    father[x] = fa;
    vis[x] = true;
    for (auto P : vec[x])
        if (!vis[P.v])
        {
            root = 0;
            getroot(getsize(P.v, x), P.v, 0);
            solve(root, x);
        }
}

void modify(int source, int x, int base)
{
    cnt[x] += base;
    //printf("dis:%d->%d = %d\n", source, x, lca(source, x));
    f1[x][0] += base * lca(source, x);
    f1[x][1] += base * lca(source, father[x]);
    if (x != father[x])
        modify(source, father[x], base);
}

int up(int source, int pre, int now)
{
    //printf("%d %d %d %d\n", source, pre, now, lca(now, source));
    ans += (f1[now][0] - f1[pre][1]) + (cnt[now] - cnt[pre]) * lca(now, source);
    if (now != father[now])
        up(source, now, father[now]);
}

int main()
{
    memset(st, -1, sizeof st);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n - 1; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        addedge(u, v, w);
        addedge(v, u, w);
    }
    lca_dfs(1, 0, 1);
    init_st();
    root = 0;
    f[0] = 0x3f3f3f3f;
    getroot(n, 1, 0);
    Root = root;
    solve(root, root);
    //printf("lca=%d\n", lca(3, 1));
    char CASE[10];
    for (int i = 1; i <= m; i++)
    {
        int x;
        scanf("%s%d", CASE, &x);
        if (CASE[0] == 'M')
        {
            modify(x, x, color[x] == 0 ? 1 : -1);
            color[x] = 1 - color[x];
        }
        else
        {
            ans = f1[x][0];
            up(x, x, father[x]);
            printf("%d\n", ans);
        }
    }
    //vis[5] = true;
    //getroot(4, 1, 5);
    //printf("%d\n", root);

    system("pause");
    return 0;
}