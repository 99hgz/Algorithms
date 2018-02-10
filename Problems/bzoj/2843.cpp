#include <cstdio>
#include <algorithm>
using namespace std;

int opt, n, x, u, v;
int ch[100010][2], st[100010], size[100010], fa[100010], key[100010], Root, sz, m, y, sum[100010], val[100010];
bool rev[100010];
char cases[100];
bool isroot(int rt)
{
    return ch[fa[rt]][0] != rt && ch[fa[rt]][1] != rt;
}

void pushdown(int rt)
{
    int lson = ch[rt][0], rson = ch[rt][1];
    if (rev[rt])
    {
        rev[rt] = 0, rev[lson] ^= 1, rev[rson] ^= 1;
        swap(ch[rt][0], ch[rt][1]);
    }
}

int get(int x)
{
    return ch[fa[x]][1] == x;
}

void update(int x)
{
    sum[x] = sum[ch[x][0]] + sum[ch[x][1]] + val[x];
}

void rotate(int x)
{
    int f = fa[x], f2 = fa[f], which = get(x);
    if (!isroot(f))
        ch[f2][ch[f2][1] == f] = x;
    ch[f][which] = ch[x][which ^ 1];
    fa[ch[f][which]] = f;
    fa[x] = f2;
    ch[x][which ^ 1] = f;
    fa[f] = x;
    update(f), update(x);
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
        int f = fa[x], f2 = fa[f];
        if (!isroot(f))
        {
            if (ch[f][0] == x ^ ch[f2][0] == f)
                rotate(x);
            else
                rotate(f);
        }
        rotate(x);
    }
}

void access(int x)
{
    int t = 0;
    while (x)
        splay(x), ch[x][1] = t, update(x), t = x, x = fa[x];
}

void rever(int x)
{
    access(x), splay(x), rev[x] ^= 1;
}

void link(int x, int y)
{
    rever(x), fa[x] = y, splay(x);
}

void cut(int x, int y)
{
    rever(x), access(y), splay(y), fa[x] = ch[y][0] = 0, update(y);
}

int find(int x)
{
    access(x), splay(x);
    while (ch[x][0])
        x = ch[x][0];
    return x;
}

int query(int x, int y)
{
    rever(x), access(y), splay(y);
    return sum[y];
}

int modify(int x, int y)
{
    rever(x);
    val[x] = y;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &val[i]);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%s%d%d", cases, &u, &v);
        if (cases[0] == 'e')
        {
            int ta = find(u), tb = find(v);
            if (ta != tb)
                printf("impossible\n");
            else
                printf("%d\n", query(u, v));
        }
        else if (cases[0] == 'b')
        {
            int ta = find(u), tb = find(v);
            if (ta == tb)
                printf("no\n");
            else
            {
                link(u, v);
                printf("yes\n");
            }
        }
        else
            modify(u, v);
    }
}