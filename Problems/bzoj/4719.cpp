#include <cmath>
#include <vector>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
using namespace std;

vector<int> hmap[300010];
int parent[300010];
bool vis[300010];
int deep[300010], ans[300010], w[300010], s[300010], t[300010];
int toroot[300010], fr[300010], se[300010], tot, bh, LCA[300010], tt[300010], now, root[3 * 300010];
struct NODe
{
    int lson, rson, sum;
} tree[10000100];
;
int p[300010][20];
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
            if (p[i][j - 1] != -1)
                p[i][j] = p[p[i][j - 1]][j - 1];
}
int lca(int a, int b)
{
    if (deep[a] < deep[b])
        swap(a, b);
    int st = floor(log(deep[a] - 1) / log(2));
    for (int i = st; i >= 0; i--)
        if (deep[a] - (1 << i) >= deep[b])
        {
            a = p[a][i];
        }
    if (a == b)
        return a;
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
    fr[p] = ++tot;
    vector<int>::iterator it;
    deep[p] = deep1;
    for (it = hmap[p].begin(); it != hmap[p].end(); it++)
    {
        if (!vis[(*it)])
        {
            vis[(*it)] = true;
            parent[(*it)] = p;
            dfs((*it), deep1 + 1);
        }
    }
    se[p] = tot;
}

void change(int &rt, int l, int r, int pos, int val)
{
    if (pos <= 0)
    {
        return;
    }
    if (!rt)
    {
        rt = ++bh;
    }
    tree[rt].sum += val;
    if (l == r)
    {
        return;
    }
    int mid = l + r >> 1;
    if (pos <= mid)
    {
        change(tree[rt].lson, l, mid, pos, val);
    }
    else
    {
        change(tree[rt].rson, mid + 1, r, pos, val);
    }
}
int query(int rt, int l, int r, int x, int y)
{
    if (!rt)
    {
        return 0;
    }
    if (l == x && r == y)
        return tree[rt].sum;
    int mid = l + r >> 1;
    if (y <= mid)
        return query(tree[rt].lson, l, mid, x, y);
    else if (x > mid)
        return query(tree[rt].rson, mid + 1, r, x, y);
    else
        return query(tree[rt].lson, l, mid, x, mid) + query(tree[rt].rson, mid + 1, r, mid + 1, y);
}

void clearval()
{
    bh = 0;
    memset(root, 0, sizeof root);
    memset(tree, 0, sizeof tree);
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
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &w[i]);
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &s[i], &t[i]);
        LCA[i] = lca(s[i], t[i]);
        printf("%d\n", LCA[i]);
    }
    for (int i = 1; i <= n; i++)
        tt[i] = w[i] + deep[i];
    for (int i = 1; i <= m; i++)
    {
        now = deep[s[i]];
        change(root[now], 1, n, fr[s[i]], 1);
        change(root[now], 1, n, fr[p[LCA[i]][0]], -1);
    }
    for (int i = 1; i <= n; i++)
    {
        ans[i] += query(root[tt[i]], 1, n, fr[i], se[i]);
    }
    clearval();
    for (int i = 1; i <= n; i++)
        tt[i] = w[i] - deep[i] + n + 1;
    for (int i = 1; i <= m; i++)
    {
        now = deep[s[i]] - (deep[LCA[i]] << 1) + n + 1;
        change(root[now], 1, n, fr[t[i]], 1);
        change(root[now], 1, n, fr[LCA[i]], -1);
    }
    for (int i = 1; i <= n; i++)
    {
        ans[i] += query(root[tt[i]], 1, n, fr[i], se[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", ans[i]);
    }
    system("pause");
}