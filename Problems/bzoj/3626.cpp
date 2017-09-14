#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int mo = 201314, N = 50010;
int n, q, head[N], tot, label, Next[N], tree[N], fa[N], dep[N], son[N], size[N], top[N];
int tid[N], Tree[N * 4], lazy[N * 4], ans[N][2];
bool visit[N];
struct node
{
    int u, v, w;
} a[N * 2];
bool cmp(node a, node b)
{
    if (a.u < b.u)
        return true;
    return false;
}
void add(int x, int y)
{
    tot++;
    Next[tot] = head[x];
    head[x] = tot;
    tree[tot] = y;
}
void dfs1(int u, int father, int depth)
{
    visit[u] = true;
    fa[u] = father;
    dep[u] = depth;
    son[u] = -1;
    size[u] = 1;
    int maxsize = 0;
    for (int i = head[u]; i != -1; i = Next[i])
        if (!visit[tree[i]])
        {
            dfs1(tree[i], u, depth + 1);
            size[u] += size[tree[i]];
            if (size[tree[i]] > maxsize)
                maxsize = size[tree[i]], son[u] = tree[i];
        }
}
void dfs2(int u, int ancestor)
{
    visit[u] = true;
    top[u] = ancestor;
    label++;
    tid[u] = label;
    if (son[u] != -1)
        dfs2(son[u], ancestor);
    for (int i = head[u]; i != -1; i = Next[i])
        if (!visit[tree[i]])
            dfs2(tree[i], tree[i]);
}
void down(int id, int x)
{
    if (x == 1)
        return;
    if (lazy[id] != 0)
    {
        Tree[id * 2] = (Tree[id * 2] + lazy[id] * (x - x / 2)) % mo;
        Tree[id * 2 + 1] = (Tree[id * 2 + 1] + lazy[id] * (x / 2)) % mo;
        lazy[id * 2] = (lazy[id * 2] + lazy[id]) % mo;
        lazy[id * 2 + 1] = (lazy[id * 2 + 1] + lazy[id]) % mo;
        lazy[id] = 0;
    }
}
void up(int id)
{
    Tree[id] = (Tree[id * 2] + Tree[id * 2 + 1]) % mo;
}
void Change(int x, int y, int id, int l, int r, int d)
{
    if (l > y || r < x)
        return;
    down(id, r - l + 1);
    if (x <= l && r <= y)
    {
        Tree[id] = (Tree[id] + (r - l + 1) * d) % mo;
        lazy[id] += d;
        return;
    }
    int mid = (l + r) / 2;
    Change(x, y, id * 2, l, mid, d);
    Change(x, y, id * 2 + 1, mid + 1, r, d);
    up(id);
}
int Query(int x, int y, int id, int l, int r)
{
    if (l > y || r < x)
        return 0;
    down(id, r - l + 1);
    if (x <= l && r <= y)
        return Tree[id];
    int mid = (l + r) / 2;
    return (Query(x, y, id * 2, l, mid) + Query(x, y, id * 2 + 1, mid + 1, r)) % mo;
}
void change(int u, int v)
{
    while (top[u] != top[v])
    {
        Change(tid[top[u]], tid[u], 1, 1, n, 1);
        u = fa[top[u]];
    }
    Change(tid[v], tid[u], 1, 1, n, 1);
}
int query(int u, int v)
{
    int ans = 0;
    while (top[u] != top[v])
    {
        ans = (ans + Query(tid[top[u]], tid[u], 1, 1, n)) % mo;
        u = fa[top[u]];
    }
    ans = (ans + Query(tid[v], tid[u], 1, 1, n)) % mo;
    return ans;
}
int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 0; i <= n; i++)
        head[i] = -1;
    tot = label = 0;
    for (int i = 1; i <= n - 1; i++)
    {
        int x;
        scanf("%d", &x);
        add(x, i);
    }
    for (int i = 0; i < n; i++)
        visit[i] = false;
    dfs1(0, 0, 0);
    for (int i = 0; i < n; i++)
        visit[i] = false;
    dfs2(0, 0);
    int num = 0;
    for (int i = 1; i <= q; i++)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        a[++num].u = x - 1;
        a[num].v = i;
        a[num].w = z;
        a[++num].u = y;
        a[num].v = i;
        a[num].w = z;
        ans[i][0] = ans[i][1] = -1;
    }
    sort(a + 1, a + num + 1, cmp);
    int j = -1;
    for (int i = 1; i <= num; i++)
    {
        if (a[i].u == -1)
        {
            ans[a[i].v][0] = 0;
            continue;
        }
        while (a[i].u > j)
        {
            j++, change(j, 0);
            // query(a[i].w, 0);
        }
        if (ans[a[i].v][0] == -1)
            ans[a[i].v][0] = query(a[i].w, 0);
        else
            ans[a[i].v][1] = query(a[i].w, 0);
    }
    for (int i = 1; i <= q; i++)
        printf("%d\n", (ans[i][1] - ans[i][0] + mo) % mo);
    //system("pause");
    return 0;
}
