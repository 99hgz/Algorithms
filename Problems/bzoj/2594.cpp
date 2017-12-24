#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <map>
using namespace std;
typedef long long ll;
int opt, n, x, q;
int ch[1100010][2], st[1100010], size[1100010], fa[1100010], key[1100010], Root, sz, m, y, val[1100010], mx[1100010], tot;

struct PATH
{
    int u, v, t, deleted, id;
} Edge[1000010], Edge2[1000010];
bool cmp(PATH a, PATH b)
{
    return a.t < b.t;
}

bool cmp2(PATH a, PATH b)
{
    if (a.u == b.u)
        return a.v < b.v;
    else
        return a.u < b.u;
}

bool cmp3(PATH a, PATH b)
{
    return a.id < b.id;
}

int cnt;
struct OP
{
    int k, x, y, id;
} op[1000010];
bool rev[1100010];
inline bool isroot(int rt)
{
    return ch[fa[rt]][0] != rt && ch[fa[rt]][1] != rt;
}

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

inline void pushdown(int rt)
{
    int lson = ch[rt][0], rson = ch[rt][1];
    if (rev[rt])
    {
        rev[rt] = 0, rev[lson] ^= 1, rev[rson] ^= 1;
        swap(ch[rt][0], ch[rt][1]);
    }
}

inline int get(int x)
{
    return ch[fa[x]][1] == x;
}

inline void update(int x)
{
    mx[x] = x;
    if (ch[x][0] && val[mx[ch[x][0]]] > val[mx[x]])
        mx[x] = mx[ch[x][0]];
    if (ch[x][1] && val[mx[ch[x][1]]] > val[mx[x]])
        mx[x] = mx[ch[x][1]];
}

void rotate(int x)
{
    int old = fa[x], oldf = fa[old], which = get(x);
    if (!isroot(old))
        ch[oldf][ch[oldf][1] == old] = x;
    ch[old][which] = ch[x][which ^ 1];
    fa[ch[old][which]] = old;
    fa[old] = x;
    ch[x][which ^ 1] = old;
    fa[x] = oldf;
    update(old), update(x);
}

void splay(int x)
{
    int top = 0;
    st[++top] = x;
    for (int i = x; !isroot(i); i = fa[i])
        st[++top] = fa[i];
    for (int i = top; i; i--)
        pushdown(st[i]);
    while (!isroot(x))
    {
        int y = fa[x], z = fa[y];
        if (!isroot(y))
        {
            if (ch[y][0] == x ^ ch[z][0] == y)
                rotate(x);
            else
                rotate(y);
        }
        rotate(x);
    }
}

inline void access(int x)
{
    int t = 0;
    while (x)
        splay(x), ch[x][1] = t, update(x), t = x, x = fa[x];
}

inline void rever(int x)
{
    access(x), splay(x), rev[x] ^= 1;
}

inline void link(int x, int y)
{
    rever(x), fa[x] = y, splay(x);
}

inline void cut(int x, int y)
{
    rever(x), access(y), splay(y), ch[y][0] = fa[x] = 0, update(y);
}

inline int find(int x)
{
    access(x), splay(x);
    int y = x;
    while (ch[y][0])
        y = ch[y][0];
    return y;
}

inline int query(int x, int y)
{
    rever(x), access(y), splay(y);
    //printf("query:%d %d %d\n", x, y, mx[y]);
    return mx[y] - n;
}

int ufs_fa[1500010];

int getfather(int x)
{
    return ufs_fa[x] == 0 ? x : ufs_fa[x] = getfather(ufs_fa[x]);
}

void addedge(int id)
{
    val[id + n] = Edge[id].t;
    int ta = getfather(Edge[id].u), tb = getfather(Edge[id].v);
    if (ta != tb)
        link(Edge[id].u, id + n), link(Edge[id].v, id + n), ufs_fa[ta] = tb;
    else
    {
        int tid = query(Edge[id].u, Edge[id].v);
        if (Edge[tid].t > Edge[id].t)
        {
            cut(tid + n, Edge[tid].u), cut(tid + n, Edge[tid].v);
            link(Edge[id].u, id + n), link(id + n, Edge[id].v);
        }
    }
}
int ans[1500010];

void Kruskal()
{
    for (int id = 1; id <= cnt; id++)
    {
        val[Edge2[id].id + n] = Edge2[id].t;
        int ta = getfather(Edge2[id].u), tb = getfather(Edge2[id].v);
        if (ta != tb)
            link(Edge2[id].u, Edge2[id].id + n), link(Edge2[id].v, Edge2[id].id + n), ufs_fa[ta] = tb;
    }
}

int findkey(int u, int v)
{
    int l = 1, r = m;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (Edge[mid].u < u || (Edge[mid].u == u && Edge[mid].v < v))
            l = mid + 1;
        else if (Edge[mid].u == u && Edge[mid].v == v)
            return mid;
        else
            r = mid - 1;
    }
}

int main()
{
    //scanf("%d%d%d", &n, &m, &q);
    n = read(), m = read(), q = read();
    for (int i = 1; i <= n + m; i++)
        mx[i] = i;
    for (int i = 1; i <= m; i++)
    {
        //scanf("%d%d%d", &Edge[i].u, &Edge[i].v, &Edge[i].t);
        Edge[i].u = read(), Edge[i].v = read(), Edge[i].t = read();
        if (Edge[i].u > Edge[i].v)
            swap(Edge[i].u, Edge[i].v);
        Edge[i].id = i;
    }

    sort(Edge + 1, Edge + 1 + m, cmp2);

    for (int i = 1; i <= q; i++)
    {
        //scanf("%d%d%d", &op[i].k, &op[i].x, &op[i].y);
        op[i].k = read(), op[i].x = read(), op[i].y = read();
        if (op[i].x > op[i].y)
            swap(op[i].x, op[i].y);
        int tmp = findkey(op[i].x, op[i].y);
        op[i].id = Edge[tmp].id;
        if (op[i].k == 2)
            Edge[tmp].deleted = 1;
    }

    sort(Edge + 1, Edge + 1 + m, cmp3);

    for (int i = 1; i <= m; i++)
        if (Edge[i].deleted == 0)
            Edge2[++cnt] = Edge[i], Edge2[cnt].id = i;

    sort(Edge2 + 1, Edge2 + 1 + cnt, cmp);
    Kruskal();

    for (int i = q; i >= 1; i--)
        if (op[i].k == 2)
        {
            int id = op[i].id;
            if (Edge[id].deleted)
                addedge(id);
        }
        else
            ans[++tot] = Edge[query(op[i].x, op[i].y)].t;
    for (int i = tot; i >= 1; i--)
        printf("%d\n", ans[i]);
    // system("pause");
    return 0;
}