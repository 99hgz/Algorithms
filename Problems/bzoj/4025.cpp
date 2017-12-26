#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
typedef long long ll;
int opt, n, x, q, T;
int ch[400010][2], st[400010], size[400010], fa[400010], key[400010], Root, cnt, sz, m, y, val1[400010], val2[400010], mx[400010], tot, mark[400010];
struct EDGE
{
    int u, v, t, start;
} Edge[400010];

bool cmp(EDGE a, EDGE b)
{
    return a.start < b.start;
}

int id, l, u, v, sum[400010];
char cases[10];
bool rev[400010], ontree[400010];
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

int ufs_fa[1500010];

int getfather(int x)
{
    return ufs_fa[x] == 0 ? x : ufs_fa[x] = getfather(ufs_fa[x]);
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
    rever(x), val2[x] = l;
}

void step2(int id)
{
    int tmp = query2(Edge[id].u, Edge[id].v);
    if (tmp % 2 == 0)
        mark[id] = 1, cnt++;
}

void addedge(int id)
{
    if (Edge[id].u == Edge[id].v)
    {
        mark[id] = 1, cnt++;
        return;
    }
    val1[id + n] = Edge[id].t;
    sum[id + n] = 1;
    int ta = getfather(Edge[id].u), tb = getfather(Edge[id].v);
    if (ta != tb)
        link(Edge[id].u, id + n), link(Edge[id].v, id + n), ufs_fa[ta] = tb, ontree[id] = true;
    else
    {
        int tid = query(Edge[id].u, Edge[id].v);
        if (Edge[tid].t >= Edge[id].t)
            step2(id);
        else
        {
            ontree[id] = true;
            cut(tid + n, Edge[tid].u), cut(tid + n, Edge[tid].v);
            link(Edge[id].u, id + n), link(id + n, Edge[id].v);
            step2(tid);
            ontree[tid] = false;
        }
    }
}
vector<int> vec[400010];
int main()
{
    scanf("%d%d%d", &n, &m, &T);
    for (int i = 1; i <= n + m; i++)
        mx[i] = i;
    for (int i = 1; i <= n; i++)
        val1[i] = 0x3f3f3f3f;
    for (int i = 1; i <= m; i++)
        val2[n + i] = 1;
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d%d", &Edge[i].u, &Edge[i].v, &Edge[i].start, &Edge[i].t);
    sort(Edge + 1, Edge + 1 + m, cmp);
    for (int i = 1; i <= m; i++)
        vec[Edge[i].t].push_back(i);
    int head = 1;
    for (int i = 0; i <= T; i++)
    {
        while (head <= m && Edge[head].start == i)
        {
            addedge(head);
            head++;
        }
        for (int it = 0; it < vec[i].size(); it++)
            if (mark[vec[i][it]])
                cnt--;
            else if (ontree[vec[i][it]])
                cut(vec[i][it] + n, Edge[vec[i][it]].u), cut(vec[i][it] + n, Edge[vec[i][it]].v);
        //printf("cnt=%d\n", cnt);
        i != T &&printf("%s\n", cnt ? "No" : "Yes");
    }
    system("pause");
    return 0;
}