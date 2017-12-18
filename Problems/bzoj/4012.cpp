#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
using namespace std;
typedef long long ll;
typedef pair<int, int> pr;
int n, k, u, v, w, tn, L, R, Hash[100010], A;
struct Node
{
    int v, w;
};
vector<Node> vec[100010];
int size[100010], f[100010], root, ans, father[100010], deep[100010];
bool vis[100010];

int st[100010][20], dis[100010][20];
struct TREE
{
    int sum, lson, rson, num;
} Tree[2000000];
int tot, Root, val[100010], Troot[100010][2], cases;
void addedge(int u, int v, int w)
{
    vec[u].push_back((Node){v, w});
}

void getroot(int treesize, int x, int fa)
{
    size[x] = 1, f[x] = 0;
    for (int i = 0; i < vec[x].size(); i++)
    {
        int P = vec[x][i].v;
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
        int P = vec[x][i].v;
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
        int P = vec[x][i].v;
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
        int P = vec[x][i].v;
        if (P != fa)
        {
            lca_dfs(P, x, depth + 1);
            dis[P][0] = vec[x][i].w;
        }
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
                dis[i][j] = dis[st[i][j - 1]][j - 1] + dis[i][j - 1];
            }
}

int _lca(int a, int b)
{
    int ua = a, ub = b, res = 0;
    if (deep[a] < deep[b])
        swap(a, b);
    int depth = floor(log(deep[a] - 1) / log(2));
    for (int i = depth; i >= 0; i--)
        if (deep[a] - (1 << i) >= deep[b])
        {
            res += dis[a][i];
            a = st[a][i];
        }
    if (a == b)
        return res;
    for (int i = depth; i >= 0; i--)
        if ((st[a][i] != -1) && (st[a][i] != st[b][i]))
        {
            res += dis[a][i] + dis[b][i];
            a = st[a][i];
            b = st[b][i];
        }
    return res + dis[a][0] + dis[b][0];
}

int lca(int a, int b)
{
    int tmp = _lca(a, b);
    printf("lca %d %d=%d\n", a, b, tmp);
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
    Tree[rt].num++;
    if (l == r)
        return;
    if (pos <= mid)
        Tmodify(Tree[rt].lson, l, mid, pos, v);
    else
        Tmodify(Tree[rt].rson, mid + 1, r, pos, v);
}

pr Tquery(int rt, int l, int r, int L, int R)
{
    if (!rt)
        return make_pair(0, 0);
    int mid = (l + r) >> 1;
    if (L <= l && r <= R)
        return make_pair(Tree[rt].sum, Tree[rt].num);
    if (r < L || l > R)
        return make_pair(0, 0);
    pr res = Tquery(Tree[rt].lson, l, mid, L, R);
    pr res2 = Tquery(Tree[rt].rson, mid + 1, r, L, R);
    return make_pair(res.first + res2.first, res.second + res2.second);
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
    printf("getans:source=%d x=%d L=%d R=%d\n", source, x, L, R);
    int tmp = lca(x, source);
    pr res = Tquery(Troot[x][0], 1, tn, L, R);
    ans += res.first + res.second * tmp;
    if (father[x])
    {
        res = Tquery(Troot[x][1], 1, tn, L, R);
        ans -= res.first + res.second * lca(source, father[x]);
    }
    if (x != Root)
        getans(source, father[x], L, R);
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
    tn = unique(Hash + 1, Hash + 1 + n) - Hash - 1;
    for (int i = 1; i <= n; i++)
        val[i] = lower_bound(Hash + 1, Hash + 1 + tn, val[i]) - Hash;

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
    solve(root, 0);

    for (int i = 1; i <= n; i++)
        modify(i, i, val[i]);

    int lastans = 0;
    for (int i = 1; i <= m; i++)
    {
        int u, a, b;
        scanf("%d%d%d", &u, &a, &b);
        L = min((a + lastans) % A, (b + lastans) % A),
        R = max((a + lastans) % A, (b + lastans) % A);
        ans = 0;
        if (L > Hash[tn])
        {
            printf("0\n");
            continue;
        }
        L = *lower_bound(Hash + 1, Hash + 1 + tn, L);
        int it = lower_bound(Hash + 1, Hash + 1 + tn, R) - Hash;
        if (Hash[it] == R)
            R = Hash[it];
        else
            R = Hash[it - 1];
        getans(u, u, L, R);
        lastans = ans;
        printf("%d\n", ans);
    }
    system("pause");
}
