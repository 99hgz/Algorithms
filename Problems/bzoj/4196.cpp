#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

int fa[100010], size[100010], timestamp, maxsonid[100010], dep[100010], in[100010], top[100010], init[100010], val[100010], out[100010];
vector<int> vec[100010];

struct TREE
{
    int lazy, num[2];
} Tree[100010 * 4];
int n, m, u, v, x, y;

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
    in[x] = ++timestamp, top[x] = ancestor, init[timestamp] = val[x];
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
    Tree[rt].num[0] = Tree[rt * 2].num[0] + Tree[rt * 2 + 1].num[0];
    Tree[rt].num[1] = Tree[rt * 2].num[1] + Tree[rt * 2 + 1].num[1];
}

void make(int rt, int l, int r, int v)
{
    Tree[rt].lazy = v;
    Tree[rt].num[v] = r - l + 1;
    Tree[rt].num[v ^ 1] = 0;
}

void pushdown(int rt, int l, int r)
{
    if (Tree[rt].lazy != -1)
    {
        int mid = (l + r) >> 1;
        make(rt * 2, l, mid, Tree[rt].lazy);
        make(rt * 2 + 1, mid + 1, r, Tree[rt].lazy);
        Tree[rt].lazy = -1;
    }
}

void build(int rt, int l, int r)
{
    Tree[rt].lazy = -1;
    if (l == r)
    {
        Tree[rt].num[0] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(rt * 2, l, mid);
    build(rt * 2 + 1, mid + 1, r);
    up(rt);
}

int modify(int rt, int l, int r, int L, int R, int v)
{
    if (L <= l && r <= R)
    {
        int res = Tree[rt].num[v ^ 1];
        make(rt, l, r, v);
        return res;
    }
    if (r < L || l > R)
        return 0;
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    int res = modify(rt * 2, l, mid, L, R, v) + modify(rt * 2 + 1, mid + 1, r, L, R, v);
    up(rt);
    return res;
}

int Modify(int x, int y, int k)
{
    int res = 0;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        res += modify(1, 1, n, in[top[x]], in[x], k);
        x = fa[top[x]];
    }
    if (dep[x] < dep[y])
        swap(x, y);
    res += modify(1, 1, n, in[y], in[x], k);
    return res;
}

char cases[20];
int main()
{
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
    {
        scanf("%d", &u);
        u++;
        addedge(u, i);
        addedge(i, u);
    }
    dfs1(1, 1, 1);
    dfs2(1, 1, 1);
    build(1, 1, n);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%s", cases);
        scanf("%d", &u);
        u++;
        if (cases[0] == 'i')
            printf("%d\n", Modify(1, u, cases[0] == 'i'));
        else
            printf("%d\n", modify(1, 1, n, in[u], out[u], cases[0] == 'i'));
    }
    system("pause");
    return 0;
}