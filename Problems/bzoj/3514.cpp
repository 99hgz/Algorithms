#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <map>
using namespace std;
typedef long long ll;
int opt, n, x, q;
int ch[400010][2], st[400010], size[400010], fa[400010], key[400010], sz, m, y, val1[400010], mx[400010], tot;
struct EDGE
{
    int u, v, t;
} Edge[400010];
int id, l, u, v;
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

int kick[200010], k, type;

void addedge(int id)
{
    val1[id + n] = id;
    int ta = getfather(Edge[id].u), tb = getfather(Edge[id].v);
    if (ta != tb)
        link(Edge[id].u, id + n), link(Edge[id].v, id + n), ufs_fa[ta] = tb, kick[id] = 0;
    else
    {
        int tid = query(Edge[id].u, Edge[id].v);
        if (Edge[tid].t < Edge[id].t)
        {
            cut(tid + n, Edge[tid].u), cut(tid + n, Edge[tid].v);
            link(Edge[id].u, id + n), link(id + n, Edge[id].v);
            kick[id] = tid;
        }
    }
}
int Root[200010];
struct TREE
{
    int lson, rson, num;
} Tree[200010 * 20];
int r;
void modify(int &rt, int l, int r, int x, int base)
{
    int thisrt = ++tot;
    Tree[thisrt] = Tree[rt];
    rt = thisrt;
    int mid = (l + r) >> 1;
    Tree[thisrt].num += base;
    if (l == r)
        return;
    if (x <= mid)
        modify(Tree[thisrt].lson, l, mid, x, base);
    else
        modify(Tree[thisrt].rson, mid + 1, r, x, base);
}

int query(int rt1, int rt2, int l, int r, int L, int R)
{
    if (L <= l && r <= R)
        return Tree[rt2].num - Tree[rt1].num;
    if (r < L || l > R)
        return 0;
    int mid = (l + r) >> 1;
    return query(Tree[rt1].lson, Tree[rt2].lson, l, mid, L, R) + query(Tree[rt1].rson, Tree[rt2].rson, mid + 1, r, L, R);
}

int main()
{
    scanf("%d%d%d%d", &n, &m, &k, &type);
    for (int i = 1; i <= n + m; i++)
        mx[i] = i;
    for (int i = 1; i <= n; i++)
        val1[i] = 0x3f3f3f3f;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &Edge[i].u, &Edge[i].v);
        Edge[i].t = i;
        if (Edge[i].u != Edge[i].v)
            addedge(i);
        else
            kick[i] = i;
    }
    for (int i = 1; i <= m; i++)
    {
        Root[i] = Root[i - 1];
        modify(Root[i], 0, m, kick[i], 1);
        //printf("kick:%d\n", kick[i]);
    }
    int lastans = 0;
    for (int i = 1; i <= k; i++)
    {
        scanf("%d%d", &l, &r);
        if (type == 1)
            l ^= lastans, r ^= lastans;
        lastans = n - query(Root[l - 1], Root[r], 0, m, 0, l - 1);
        printf("%d\n", lastans);
    }
    //system("pause");
    return 0;
}