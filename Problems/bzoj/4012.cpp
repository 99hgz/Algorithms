#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
using namespace std;
typedef long long ll;
#define G greater<int>
int n, k, u, v, w;
vector<int> vec[100010];
int size[100010], f[100010], root, ans, father[100010], deep[100010];
bool vis[100010];

int st[100010][20];
struct TREE
{
    int sum, lson, rson;
} Tree[2000000];
int tot, Root, val[100010], Troot[100010][2], cases;
void addedge(int u, int v)
{
    vec[u].push_back(v);
}

void getroot(int treesize, int x, int fa)
{
    size[x] = 1, f[x] = 0;
    for (int i = 0; i < vec[x].size(); i++)
    {
        int P = vec[x][i];
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
    for (int i = 0; i < vec[x].size(); i++)
    {
        int P = vec[x][i];
        if ((P != fa) && (!vis[P]))
            res += getsize(P, x);
    }
    return res;
}

void solve(int x, int fa)
{
    father[x] = fa;
    vis[x] = true;
    for (int i = 0; i < vec[x].size(); i++)
    {
        int P = vec[x][i];
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
    st[x][0] = fa;
    deep[x] = depth;
    for (int i = 0; i < vec[x].size(); i++)
    {
        int P = vec[x][i];
        if (P != fa)
            lca_dfs(P, x, depth + 1);
    }
}

void init_st()
{
    int deep = floor(log(n) / log(2));
    for (int j = 1; j <= deep; j++)
        for (int i = 1; i <= n; i++)
            if (st[i][j - 1] != -1)
                st[i][j] = st[st[i][j - 1]][j - 1];
}

int _lca(int a, int b)
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

int lca(int a, int b)
{
    int tmp = _lca(a, b);
    //printf("lca %d %d=%d\n", a, b, tmp);
    return tmp;
}

void Tmodify(int &rt, int l, int r, int pos, int v)
{
    //printf("%d %d %d %d %d\n", rt, l, r, pos, v);
    if (v < 0)
        return;
    if (!rt)
        rt = ++tot;
    int mid = (l + r) >> 1;
    Tree[rt].sum += v;
    if (l == r)
        return;
    if (pos <= mid)
        Tmodify(Tree[rt].lson, l, mid, pos, v);
    else
        Tmodify(Tree[rt].rson, mid + 1, r, pos, v);
}

int Tquery(int rt, int l, int r, int L, int R)
{
    if (!rt)
        return 0;
    int mid = (l + r) >> 1;
    if (L <= l && r <= R)
        return Tree[rt].sum;
    if (r < L || l > R)
        return 0;
    return Tquery(Tree[rt].lson, l, mid, L, R) + Tquery(Tree[rt].rson, mid + 1, r, L, R);
}

void modify(int source, int x, int val)
{
    Tmodify(Troot[x][0], 1, tn, val, lca(source, x));
    if (father[x])
        Tmodify(Troot[x][1], 1, tn, val, lca(source, father[x]));
    if (x != Root)
        modify(source, father[x], val);
}

void getans(int source, int x, int L, int R)
{
    int tmp = lca(x, source);
    Node res = Tquery(Troot[x][0], 1, tn, L, R);
    ans += res.sum + res.num * tmp;
}

int main()
{
    int m;
    scanf("%d%d%d", &n, &m, &A);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &val[i]);
        Hash[i] = val[i];
    }

    sort(Hash + 1, Hash + 1 + n);
    int tn = unique(Hash + 1, Hash + 1 + n) - Hash - 1;
    for (int i = 1; i <= n; i++)
        val[i] = lower_bound(Hash + 1, Hash + 1 + tn, val[i]) - Hash;

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

    for (int i = 1; i <= n; i++)
        modify(i, i, val[i]);

    system("pause");
}
