#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <map>
using namespace std;
typedef long long ll;
int opt, n, x, q;
int ch[400010][2], st[400010], fa[400010], sz, m, y, val1[400010], val2[400010], mn[400010], mx[400010];
struct EDGE
{
    int u, v, a, b;
} Edge[400010];
struct QUERY
{
    int u, v, a, b, id;
    bool exista, existb;
} qry[100010];
int L[200010], R[200010];
int id, l, u, v;
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
    if (ch[x][0] && val1[mx[ch[x][0]]] > val1[mx[x]])
        mx[x] = mx[ch[x][0]];
    if (ch[x][1] && val1[mx[ch[x][1]]] > val1[mx[x]])
        mx[x] = mx[ch[x][1]];
    mn[x] = x;
    if (ch[x][0] && val2[mn[ch[x][0]]] < val2[mn[x]])
        mn[x] = mn[ch[x][0]];
    if (ch[x][1] && val2[mn[ch[x][1]]] < val2[mn[x]])
        mn[x] = mn[ch[x][1]];
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

inline int querym(int x, int y)
{
    rever(x), access(y), splay(y);
    return mn[y] - n;
}

void addedge(int id)
{
    val1[id + n] = val2[id + n] = id;
    mx[id + n] = mn[id + n] = id + n;
    int ta = find(Edge[id].u), tb = find(Edge[id].v);
    if (ta != tb)
    {
        link(Edge[id].u, id + n), link(Edge[id].v, id + n);
        printf("edge:%d link:%d %d\n", id, Edge[id].u, Edge[id].v);
    }
    else
    {
        int tid = querym(Edge[id].u, Edge[id].v);
        printf("edge:%d cut:%d %d\n", tid, Edge[tid].u, Edge[tid].v);
        cut(tid + n, Edge[tid].u),
            cut(tid + n, Edge[tid].v);
        link(Edge[id].u, id + n), link(id + n, Edge[id].v);
        printf("edge:%d link:%d %d\n", id, Edge[id].u, Edge[id].v);
    }
}

bool query1(int u, int v, int L, int R)
{
    int ta = find(u), tb = find(v);
    if (ta != tb)
        return false;
    else
        return true;
    int tmp = query(u, v);
    printf("edge:%d linked (%d,%d) range is [%d,%d]\n", tmp, u, v, L, R);
    if (L <= tmp && tmp <= R)
        return true;
    else
        return false;
}

bool ecmpa(EDGE a, EDGE b)
{
    return a.a < b.a;
}
bool ecmpb(EDGE a, EDGE b)
{
    return a.b < b.b;
}
bool qcmpa(QUERY a, QUERY b)
{
    return a.a < b.a;
}
bool qcmpb(QUERY a, QUERY b)
{
    return a.b < b.b;
}
bool qcmpid(QUERY a, QUERY b)
{
    return a.id < b.id;
}
int Hash[200010], htot;
int main()
{
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++)
        val2[i] = 0x3f3f3f3f;

    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d%d", &Edge[i].u, &Edge[i].v, &Edge[i].a, &Edge[i].b);
        Hash[++htot] = Edge[i].a;
        Hash[++htot] = Edge[i].b;
    }
    sort(Hash + 1, Hash + 1 + htot);
    int tn = unique(Hash + 1, Hash + 1 + htot) - Hash - 1;
    for (int i = 1; i <= m; i++)
        Edge[i].a = lower_bound(Hash + 1, Hash + 1 + tn, Edge[i].a) - Hash,
        Edge[i].b = lower_bound(Hash + 1, Hash + 1 + tn, Edge[i].b) - Hash;

    scanf("%d", &q);
    for (int i = 1; i <= q; i++)
    {
        scanf("%d%d%d%d", &qry[i].u, &qry[i].v, &qry[i].a, &qry[i].b);
        qry[i].id = i;
    }
    sort(Edge + 1, Edge + 1 + m, ecmpa);
    sort(qry + 1, qry + 1 + q, qcmpa);
    memset(L, 0x3f3f3f3f, sizeof L);
    int head = 1;
    for (int i = 1; i <= q; i++)
    {
        while (head <= m && Edge[head].a <= qry[i].a)
        {
            addedge(head);
            L[Edge[head].a] = min(L[Edge[head].a], head);
            R[Edge[head].a] = max(R[Edge[head].a], head);
            head++;
        }
        qry[i].exista = query1(qry[i].u, qry[i].v, L[qry[i].a], R[qry[i].a]);
    }
    printf("work for b\n");
    memset(ch, 0, sizeof ch);
    memset(fa, 0, sizeof fa);
    memset(val1, 0, sizeof val1);
    memset(L, 0x3f3f3f3f, sizeof L);
    memset(R, 0, sizeof R);
    memset(mx, 0, sizeof mx);
    memset(rev, 0, sizeof rev);
    for (int i = 1; i <= n; i++)
        val2[i] = 0x3f3f3f3f;
    sort(Edge + 1, Edge + 1 + m, ecmpb);
    sort(qry + 1, qry + 1 + q, qcmpb);
    head = 1;
    for (int i = 1; i <= q; i++)
    {
        while (head <= m && Edge[head].b <= qry[i].b)
        {
            addedge(head);
            L[Edge[head].b] = min(L[Edge[head].b], head);
            R[Edge[head].b] = max(R[Edge[head].b], head);
            head++;
        }
        qry[i].existb = query1(qry[i].u, qry[i].v, L[qry[i].b], R[qry[i].b]);
    }

    sort(qry + 1, qry + 1 + q, qcmpid);
    for (int i = 1; i <= q; i++)
        printf("%d %d %s\n", qry[i].exista, qry[i].existb, (qry[i].exista && qry[i].existb) ? "YES" : "NO");
    system("pause");
}