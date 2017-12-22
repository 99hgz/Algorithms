#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int opt, n, x;
int ch[100010][2], st[100010], size[100010], fa[100010], key[100010], Root, sz, m, y;
bool rev[100010];
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

void access(int x)
{
    int t = 0;
    while (x)
        splay(x), ch[x][1] = t, t = x, x = fa[x];
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
    rever(x), access(y), splay(y), ch[y][0] = fa[x] = 0;
}

int find(int x)
{
    access(x), splay(x);
    int y = x;
    while (ch[y][0])
        y = ch[y][0];
    return y;
}

int main()
{
    char ch[10];
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%s", ch);
        scanf("%d%d", &x, &y);
        if (ch[0] == 'C')
            link(x, y);
        else if (ch[0] == 'D')
            cut(x, y);
        else
        {
            if (find(x) == find(y))
                printf("Yes\n");
            else
                printf("No\n");
        }
    }
    system("pause");
    return 0;
}