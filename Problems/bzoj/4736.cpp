#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <map>
using namespace std;
typedef long long ll;
int opt, n, x, q;
int ch[1100010][2], st[1100010], size[1100010], fa[1100010], key[1100010], Root, sz, m, y, val[1100010], mx[1100010], tot;

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
        if (Edge[tid].t < Edge[id].t)
        {
            cut(tid + n, Edge[tid].u), cut(tid + n, Edge[tid].v);
            link(Edge[id].u, id + n), link(id + n, Edge[id].v);
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%s", cases);
        if (cases[0] == 'f')
        {
            scanf("%d", &id);
            scanf("%d%d%d%d", &Edge[id].u, &Edge[id].v, &Edge[id].t, &Edge[id].l);
            addedge(id);
        }
        else if (cases[0] == 'm')
        {
            scanf("%d%d", &u, &v);
            printf("%d\n", query(u, v));
        }
        else
        {
            scanf("%d%d", &id, &l);
            modify(id, l);
            Edge[id].l = l;
        }
    }
    return 0;
}