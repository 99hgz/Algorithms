#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;
#define G greater<int>
int n, k, u, v, w;
int size[100010], f[100010], root, ans, father[100010], deep[100010];
bool vis[100010];
int MAXDEP;
int st[100010][20];
int tot2, Head[100010], To[200010], Next[200010];

struct TREE
{
    int sum, lson, rson;
} Tree[8000000];
int tot, Root, val[100010], Troot[100010][2];
inline void addedge(int u, int v)
{
    tot2++;
    Next[tot2] = Head[u];
    Head[u] = tot2;
    To[tot2] = v;
}

void getroot(int treesize, int x, int fa)
{
    size[x] = 1, f[x] = 0;
    for (int i = Head[x]; i; i = Next[i])
    {
        int P = To[i];
        if ((P != fa) && (!vis[P]))
        {
            getroot(treesize, P, x);
            size[x] += size[P];
            f[x] = max(f[x], size[P]);
        }
    }
    f[x] = max(f[x], treesize - size[x]);
    if (f[x] < f[root])
        root = x;
}

int getsize(int x, int fa)
{
    int res = 1;
    for (int i = Head[x]; i; i = Next[i])
    {
        int P = To[i];
        if ((P != fa) && (!vis[P]))
            res += getsize(P, x);
    }
    return res;
}

void solve(int x, int fa)
{
    father[x] = fa;
    vis[x] = true;
    for (int i = Head[x]; i; i = Next[i])
    {
        int P = To[i];
        if (!vis[P])
        {
            root = 0;
            getroot(getsize(P, x), P, 0);
            solve(root, x);
        }
    }
}

//*********************LCA

void lca_dfs(int x, int fa, int depth)
{
    MAXDEP = max(MAXDEP, depth);
    st[x][0] = fa;
    deep[x] = depth;
    for (int i = Head[x]; i; i = Next[i])
    {
        int P = To[i];
        if (P != fa)
            lca_dfs(P, x, depth + 1);
    }
}

inline void init_st()
{
    int deep = floor(log(n) / log(2));
    for (int j = 1; j <= deep; j++)
        for (int i = 1; i <= n; i++)
            if (st[i][j - 1] != -1)
                st[i][j] = st[st[i][j - 1]][j - 1];
}

inline int lca(int a, int b)
{
    int ua = a, ub = b;
    if (deep[a] < deep[b])
        swap(a, b);
    int depth = floor(log(deep[a] - 1) / log(2));
    for (int i = depth; i >= 0; i--)
        if (deep[a] - (1 << i) >= deep[b])
            a = st[a][i];
    if (a == b)
        return deep[ua] + deep[ub] - 2 * deep[a];
    for (int i = depth; i >= 0; i--)
        if ((st[a][i] != -1) && (st[a][i] != st[b][i]))
        {
            a = st[a][i];
            b = st[b][i];
        }
    return deep[ua] + deep[ub] - 2 * deep[st[b][0]];
}

void pushdown(int rt)
{
    if (Tree[rt].sum)
    {
        if (!Tree[rt].lson)
            Tree[rt].lson = ++tot;
        if (!Tree[rt].rson)
            Tree[rt].rson = ++tot;
        Tree[Tree[rt].lson].sum += Tree[rt].sum;
        Tree[Tree[rt].rson].sum += Tree[rt].sum;
        Tree[rt].sum = 0;
    }
}

void Tmodify(int &rt, int l, int r, int L, int R, int v)
{
    if (r < L || l > R)
        return;
    if (!rt)
        rt = ++tot;
    if (L <= l && r <= R)
    {
        Tree[rt].sum += v;
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt);
    Tmodify(Tree[rt].lson, l, mid, L, R, v);
    Tmodify(Tree[rt].rson, mid + 1, r, L, R, v);
}

int Tquery(int rt, int l, int r, int x)
{
    if (!rt)
        return 0;
    int mid = (l + r) >> 1;
    if (l == r)
        return Tree[rt].sum;
    pushdown(rt);
    if (x <= mid)
        return Tquery(Tree[rt].lson, l, mid, x);
    else
        return Tquery(Tree[rt].rson, mid + 1, r, x);
}

void modify(int source, int x, int dis, int val)
{
    Tmodify(Troot[x][0], 1, n, 1, dis - lca(x, source), val);
    if (father[x])
        Tmodify(Troot[x][1], 1, n, 1, dis - lca(father[x], source), val);
    if (x != Root)
        modify(source, father[x], dis, val);
}

int getans(int source, int x)
{
    ans += Tquery(Troot[x][0], 1, n, lca(source, x));
    if (father[x])
        ans -= Tquery(Troot[x][1], 1, n, lca(source, father[x]));
    if (x != Root)
        getans(source, father[x]);
}

int main()
{
    int m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n - 1; i++)
    {
        scanf("%d%d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }
    lca_dfs(1, 0, 1);
    init_st();

    root = 0;
    f[0] = 0x3f3f3f3f;
    getroot(n, 1, 0);
    Root = root;
    solve(root, 0);

    char cases[10];
    for (int i = 1; i <= m; i++)
    {
        int x, d, w;
        scanf("%s", cases);
        if (cases[0] == 'M')
        {
            scanf("%d%d%d", &x, &d, &w);
            modify(x, x, d, w);
        }
        else
        {
            scanf("%d", &x);
            ans = 0;
            getans(x, x);
            printf("%d\n", ans);
        }
    }
    //system("pause");
}
