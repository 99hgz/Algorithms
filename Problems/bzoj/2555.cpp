#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int ch[1200005][2], fa[1200005], lazy[1200005], w[1200005];
char st[3000005], init123[3000005], op[20];
int a[1200005][26], sam_fa[1200005], last, root, cnt, len[1200005], stlen, Q;
int S[1200005];
bool isroot(int rt)
{
    return ch[fa[rt]][0] != rt && ch[fa[rt]][1] != rt;
}

void add(int x, int y)
{
    if (x)
        w[x] += y, lazy[x] += y;
}

void pushdown(int rt)
{
    int lson = ch[rt][0], rson = ch[rt][1];
    if (lazy[rt])
    {
        add(lson, lazy[rt]), add(rson, lazy[rt]);
        lazy[rt] = 0;
    }
}

int get(int x)
{
    return ch[fa[x]][1] == x;
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
}

void splay(int x)
{
    int top = 0;
    S[++top] = x;
    for (int i = x; !isroot(i); i = fa[i])
        S[++top] = fa[i];
    for (int i = top; i; i--)
        pushdown(S[i]);
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

void access(int x)
{
    int t = 0;
    while (x)
        splay(x), ch[x][1] = t, t = x, x = fa[x];
}

void link(int x, int f)
{
    fa[x] = f, access(f), splay(f), add(f, w[x]);
}

void cut(int x)
{
    access(x), splay(x), add(ch[x][0], -w[x]);
    fa[ch[x][0]] = 0, ch[x][0] = 0;
}

void init()
{
    last = root = ++cnt;
}

void extend(int ch)
{
    int p = last, np = last = ++cnt;
    w[np] = 1;
    len[np] = len[p] + 1;
    while (p && !a[p][ch])
        a[p][ch] = np, p = sam_fa[p];
    if (!p)
        sam_fa[np] = root, link(np, root);
    else
    {
        int q = a[p][ch];
        if (len[q] == len[p] + 1)
            sam_fa[np] = q, link(np, q);
        else
        {
            int nq = ++cnt;
            len[nq] = len[p] + 1;
            memcpy(a[nq], a[q], sizeof a[q]);
            sam_fa[nq] = sam_fa[q];
            link(nq, sam_fa[q]);
            sam_fa[q] = sam_fa[np] = nq;
            cut(q);
            link(q, nq), link(np, nq);
            while (p && a[p][ch] == q)
                a[p][ch] = nq, p = sam_fa[p];
        }
    }
}

inline void decode(int mask)
{
    for (int i = 0; i < stlen; i++)
    {
        mask = (mask * 131 + i) % stlen;
        swap(st[i], st[mask]);
    }
}

int query()
{
    int cur = root;
    for (int i = 0; i < stlen; i++)
        if (a[cur][st[i] - 'A'] == 0)
            return 0;
        else
            cur = a[cur][st[i] - 'A'];
    splay(cur);
    return w[cur];
}

int main()
{
    init();
    scanf("%d", &Q);
    scanf("%s", init123 + 1);
    int mask = 0;
    stlen = strlen(init123 + 1);
    for (int i = 1; i <= stlen; i++)
        extend(init123[i] - 'A');
    for (int i = 1; i <= Q; i++)
    {
        scanf("%s", op);
        scanf("%s", st);
        stlen = strlen(st);
        decode(mask);

        if (op[0] == 'Q')
        {
            int ans = query();
            mask = mask ^ ans;
            printf("%d\n", ans);
        }
        else
            for (int i = 0; i < stlen; i++)
                extend(st[i] - 'A');
    }
    system("pause");
    return 0;
}