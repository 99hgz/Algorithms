#include <cstdio>
#include <algorithm>
using namespace std;

int opt, n, u, v;
int ch[100010][2], st[100010], size[100010], fa[100010], Root, sz, m, y;
bool rev[100010];

struct SUM
{
    double xs[17];
};

SUM val[100010], sum[100010];
SUM operator+(SUM a, SUM b)
{
    SUM tmp;
    for (int i = 0; i <= 16; i++)
        tmp.xs[i] = a.xs[i] + b.xs[i];
    return tmp;
}

double C[30][30], fac[30], A[30], B[30];
struct CT
{
    int f;
    double a, b;
} ct[100010];

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

SUM calc(CT a)
{
    SUM res;
    B[0] = A[0] = 1.0;
    for (int i = 0; i <= 16; i++)
        res.xs[i] = 0;
    for (int i = 1; i <= 16; i++)
        B[i] = B[i - 1] * a.b, A[i] = A[i - 1] * a.a;
    double tmp = 1.0;
    if (a.f == 3)
        res.xs[0] = a.b, res.xs[1] = a.a;
    else if (a.f == 1)
    {
        for (int i = 1; i <= 8; i++)
            for (int j = 0; j <= 2 * i - 1; j++)
                res.xs[j] = res.xs[j] + C[2 * i - 1 - j][2 * i - 1] * A[j] * B[2 * i - 1 - j] * ((i % 2 == 1) ? 1.0 : -1.0) / fac[2 * i - 1];
    }
    else
    {
        res.xs[0] = 1.0;
        for (int i = 1; i <= 16; i++)
            for (int j = 0; j <= i; j++)
                res.xs[j] = res.xs[j] + C[i - j][i] * A[j] * B[i - j] / fac[i];
    }
    return res;
}

SUM query(int x, int y)
{
    rever(x), access(y), splay(y);
    return sum[y];
}

void modify(int x)
{
    rever(x);
    val[x] = calc(ct[x]);
    //update(x);
}

void init()
{
    C[0][1] = C[1][1] = 1.0;
    for (int i = 2; i <= 20; i++)
    {
        C[0][i] = 1.0;
        for (int j = 1; j <= i; j++)
            C[j][i] = C[j][i - 1] + C[j - 1][i - 1];
    }
    fac[0] = 1.0;
    for (int i = 1; i <= 16; i++)
        fac[i] = fac[i - 1] * (double)i;
}

double F(SUM a, double x)
{
    double res = 0, now = 1.0;
    for (int i = 0; i <= 16; i++)
        res += a.xs[i] * now, now = now * x;
    return res;
}

double a, b, x;
int c, f;

char cases[20];
int main()
{
    //freopen("x:/b1.in","r",stdin);
    scanf("%d%d%s", &n, &m, cases);
    init();
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%lf%lf", &ct[i].f, &ct[i].a, &ct[i].b);
        val[i] = calc(ct[i]);
        //printf("%.8lf\n", F(val[i], 1));
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%s", cases);
        if (cases[0] == 'a')
        {
            scanf("%d%d", &u, &v);
            u++, v++;
            link(u, v);
        }
        else if (cases[0] == 'd')
        {
            scanf("%d%d", &u, &v);
            u++, v++;
            cut(u, v);
        }
        else if (cases[0] == 'm')
        {
            scanf("%d%d%lf%lf", &c, &f, &a, &b);
            c++;
            ct[c] = (CT){f, a, b};
            modify(c);
        }
        else
        {
            scanf("%d%d%lf", &u, &v, &x);
            v++, u++;
            int fa = find(u), fb = find(v);
            if (fa != fb)
                printf("unreachable\n");
            else
            {
                SUM tmp = query(u, v);
                printf("%.10le\n", F(tmp, x));
            }
        }
    }
    system("pause");
}