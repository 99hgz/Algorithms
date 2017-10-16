#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;

int bh, n, tn, m, l, r, k, v, u, lastans;
int root[100010];
vector<int> vec[100010];
int a[100011], Hash[100011];
int st[100011][20], deep[100010];
struct NODe
{
    int lson, rson, v;
} tree[2000010];

void addedge(int u, int v)
{
    vec[u].push_back(v);
}

int build(int l, int r)
{
    bh++;
    //printf("build:%d %d %d\n", l, r, bh);
    int tbh = bh;
    if (l == r)
    {
        tree[bh].v = 0;
        return bh;
    }
    tree[tbh].lson = build(l, (l + r) >> 1);
    tree[tbh].rson = build(((l + r) >> 1) + 1, r);
    return tbh;
}

int update(int i, int l, int r, int old)
{

    if (l == r)
    {
        bh++;
        tree[bh].v = tree[old].v + 1;
        return bh;
    }
    int tbh;
    int mid = (l + r) >> 1;
    if (i > mid)
    {
        bh++;
        tbh = bh;
        tree[bh].v = tree[old].v + 1;
        tree[bh].lson = tree[old].lson;
        tree[tbh].rson = update(i, mid + 1, r, tree[old].rson);
    }
    else
    {
        bh++;
        tbh = bh;
        tree[bh].v = tree[old].v + 1;
        tree[bh].rson = tree[old].rson;
        tree[tbh].lson = update(i, l, mid, tree[old].lson);
    }
    //printf("%d %d %d %d", i, l, r, old);
    //printf(" change->%d\n", tbh);
    //printf("lson=%d rson=%d\n", tree[tbh].lson, tree[tbh].rson);
    return tbh;
}

void dfs(int x, int fa, int depth)
{
    st[x][0] = fa;
    deep[x] = depth;
    int val = lower_bound(Hash + 1, Hash + tn + 1, a[x]) - Hash;
    //printf("update:%d %d %d\n", a[x], fa, val);
    root[x] = update(val, 1, tn, root[fa]);
    for (int i = 0; i < vec[x].size(); i++)
    {
        if (vec[x][i] != fa)
            dfs(vec[x][i], x, depth + 1);
    }
}

int query(int G, int u, int v, int lca, int lcafa, int l, int r)
{
    //printf("%d %d %d %d %d %d %d %d\n", G, u, v, lca, lcafa, l, r);
    if (l == r)
    {
        return l;
    }
    int mid = (l + r) >> 1;
    int lsl = tree[tree[u].lson].v + tree[tree[v].lson].v - tree[tree[lca].lson].v - tree[tree[lcafa].lson].v;
    //printf("%d %d %d %d num<=%d =%d\n", tree[tree[u].lson].v, tree[tree[v].lson].v, tree[tree[lca].lson].v, tree[tree[lcafa].lson].v, mid, lsl);
    if (G <= lsl)
    {
        return query(G, tree[u].lson, tree[v].lson, tree[lca].lson, tree[lcafa].lson, l, mid);
    }
    else
    {
        return query(G - lsl, tree[u].rson, tree[v].rson, tree[lca].rson, tree[lcafa].rson, mid + 1, r);
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

int lca(int a, int b)
{
    if (deep[a] < deep[b])
        swap(a, b);
    int depth = floor(log(deep[a] - 1) / log(2));
    for (int i = depth; i >= 0; i--)
        if (deep[a] - (1 << i) >= deep[b])
        {
            a = st[a][i];
        }
    if (a == b)
        return a;
    for (int i = depth; i >= 0; i--)
        if ((st[a][i] != -1) && (st[a][i] != st[b][i]))
        {
            a = st[a][i];
            b = st[b][i];
        }
    return st[a][0];
}

int main()
{
    memset(st, -1, sizeof st);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        Hash[i] = a[i];
    }
    sort(Hash + 1, Hash + n + 1);
    tn = unique(Hash + 1, Hash + n + 1) - Hash - 1;
    //printf("%d\n", tn);
    root[0] = build(1, tn);
    for (int i = 1; i <= n - 1; i++)
    {
        scanf("%d%d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }
    dfs(1, 0, 1);
    init_st();
    lastans = 0;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d %d %d", &u, &v, &k);
        //u ^= lastans;
        int LCA = lca(u, v);
        //printf("lca:%d\n", LCA);
        //printf("%d %d %d %d\n", LCA, st[LCA][0], u, v);
        lastans = Hash[query(k, root[u], root[v], root[LCA], root[st[LCA][0]], 1, tn)];
        printf("%d\n", lastans);
    }
    system("pause");
    //scanf("%d", &n);
    return 0;
}