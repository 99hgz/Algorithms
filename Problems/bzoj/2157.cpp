#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <map>
using namespace std;
typedef long long ll;
int opt, n, x, q;
int ch[400010][2], st[400010], size[400010], fa[400010], key[400010], Root, sz, m, y, val1[400010], val2[400010], mx[400010], tot;
struct EDGE
{
    int u, v, t, l;
} Edge[400010];
int id, l, u, v, sum[400010];
char cases[10];
bool rev[400010];

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
    if (ch[x][0] && val1[mx[ch[x][0]]] < val1[mx[x]])
        mx[x] = mx[ch[x][0]];
    if (ch[x][1] && val1[mx[ch[x][1]]] < val1[mx[x]])
        mx[x] = mx[ch[x][1]];
    sum[x] = val2[x];
    if (ch[x][0])
        sum[x] += sum[ch[x][0]];
    if (ch[x][1])
        sum[x] += sum[ch[x][1]];
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

inline int query2(int x, int y)
{
    if (x == y)
        return 0;
    int ta = getfather(x), tb = getfather(y);
    if (ta != tb)
        return -1;
    rever(x), access(y), splay(y);
    return sum[y];
}

void modify(int x, int l)
{
    rever(x),
        sum[id + n] = val1[id + n] = val2[id + n] = Edge[id].w = v,
                 , val2[x] = l;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n + m; i++)
        mx[i] = mn[i] = i;
    for (int i = 1; i <= n; i++)
        val1[i] = -2000, val2[i] = 2000;
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d%d", &Edge[i].u, &Edge[i].v, &Edge[i].w);
        Edge[i].u++, Edge[i].v++;
        val1[id + n] = val2[id + n] = Edge[id].w;
        sum[id + n] = Edge[id].w;
        link(Edge[id].u, id + n), link(Edge[id].v, id + n);
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%s", cases);
        if (cases[0] == 'C')
        {
            scanf("%d%d", &id, &v);
            modify(id + n, v);
        }
        else if (cases[0] == 'S')
        {
            scanf("%d%d", &u, &v);
            u++, v++;
            printf("%d\n", query2(u, v));
        }
        else
        {
            scanf("%d%d", &id, &l);
            id++, modify(id + n, l);
            Edge[id].l = l;
        }
    }
    return 0;
}