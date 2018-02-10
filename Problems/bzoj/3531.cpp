#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

int fa[100010], size[100010], timestamp, maxsonid[100010], dep[100010], in[100010], top[100010], init[100010], val[100010], out[100010];
vector<int> vec[100010];
int tot, Root[100010], c[100010], w[100010];
struct Node
{
    int sum, mx;
};
struct TREE
{
    int lson, rson;
    Node val;
} Tree[100010 * 20];
int n, m, u, v, x, y;

Node operator+(Node a, Node b)
{
    Node tmp;
    tmp.sum = a.sum + b.sum;
    tmp.mx = max(a.mx, b.mx);
    return tmp;
}

void addedge(int u, int v)
{
    vec[u].push_back(v);
}

void dfs1(int x, int father, int depth)
{
    fa[x] = father, size[x] = 1, maxsonid[x] = 0, dep[x] = depth;
    int maxsize = 0;
    for (int i = 0; i < vec[x].size(); i++)
    {
        int v = vec[x][i];
        if (v != father)
        {
            dfs1(v, x, depth + 1);
            size[x] += size[v];
            if (maxsize < size[v])
                maxsize = size[v],
                maxsonid[x] = v;
        }
    }
}

void dfs2(int x, int father, int ancestor)
{
    in[x] = ++timestamp, top[x] = ancestor;
    if (maxsonid[x])
        dfs2(maxsonid[x], x, ancestor);
    for (int i = 0; i < vec[x].size(); i++)
    {
        int v = vec[x][i];
        if (v != father && v != maxsonid[x])
            dfs2(v, x, v);
    }
    out[x] = timestamp;
}

void up(int rt)
{
    Tree[rt].val = Tree[Tree[rt].lson].val + Tree[Tree[rt].rson].val;
}

void modify(int &rt, int l, int r, int pos, int v)
{
    if (!rt)
        rt = ++tot;
    if (l == r)
    {
        Tree[rt].val.sum = Tree[rt].val.mx = v;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        modify(Tree[rt].lson, l, mid, pos, v);
    else
        modify(Tree[rt].rson, mid + 1, r, pos, v);
    up(rt);
}

Node query(int rt, int l, int r, int L, int R)
{
    if (!rt)
        return (Node){0, 0};
    if (L <= l && r <= R)
        return Tree[rt].val;
    if (r < L || l > R)
        return (Node){0, 0};
    int mid = (l + r) >> 1;
    return query(Tree[rt].lson, l, mid, L, R) + query(Tree[rt].rson, mid + 1, r, L, R);
}
Node Query(int x, int y)
{
    int belief = c[x];
    Node res;
    res.sum = res.mx = 0;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        res = res + query(Root[belief], 1, n, in[top[x]], in[x]);
        x = fa[top[x]];
    }
    if (dep[x] < dep[y])
        swap(x, y);
    res = res + query(Root[belief], 1, n, in[y], in[x]);
    return res;
}
char cases[10];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &w[i], &c[i]);
    for (int i = 1; i <= n - 1; i++)
    {
        scanf("%d%d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }
    dfs1(1, 1, 1);
    dfs2(1, 1, 1);

    for (int i = 1; i <= n; i++)
        modify(Root[c[i]], 1, n, in[i], w[i]);

    for (int i = 1; i <= m; i++)
    {
        scanf("%s%d%d", &cases, &x, &y);
        if (cases[1] == 'C')
        {
            modify(Root[c[x]], 1, n, in[x], 0);
            c[x] = y;
            modify(Root[c[x]], 1, n, in[x], w[x]);
        }
        else if (cases[1] == 'W')
            w[x] = y, modify(Root[c[x]], 1, n, in[x], y);
        else if (cases[1] == 'S')
            printf("%d\n", Query(x, y).sum);
        else
            printf("%d\n", Query(x, y).mx);
    }
    system("pause");
    return 0;
}