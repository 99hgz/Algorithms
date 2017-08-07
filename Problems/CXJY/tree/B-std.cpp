#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <set>
#define N 1000010
#define xrf 707185547
using namespace std;
int fa[N], a[N];
int to[N], nxt[N], pre[N], cnt;
void ae(int ff, int tt)
{
    cnt++;
    to[cnt] = tt;
    nxt[cnt] = pre[ff];
    pre[ff] = cnt;
}
struct ppp
{
    int mx, num;
} b[N];
bool cmp(ppp x, ppp y) { return x.mx < y.mx; }
bool chs[N];
int cn;
int mx[N];
void build(int x, int maxn)
{
    if (!a[x])
    {
        cn++;
        b[cn] = (ppp){maxn, x};
    }
    int i, j;
    for (i = pre[x]; i; i = nxt[i])
    {
        j = to[i];
        if (a[j] != 0)
            build(j, a[j]);
        else
            build(j, mx[maxn - 1]);
    }
}
int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree2.out", "w", stdout);

    int n;
    scanf("%d", &n);
    int i, j, x, y, root;
    for (i = 1; i <= n; i++)
    {
        scanf("%d%d", &fa[i], &a[i]);
        chs[a[i]] = true;
        if (fa[i] != i)
            ae(fa[i], i);
        else
            root = i;
    }
    for (i = 1; i <= n; i++)
        if (chs[i])
            mx[i] = mx[i - 1];
        else
            mx[i] = i;
    build(root, n);
    sort(b + 1, b + cn + 1, cmp);
    int now = 0, tot = 0;
    j = 1;
    for (i = 1; i <= n; i++)
    {
        if (chs[i])
            tot++;
        else
        {
            int ths = 0;
            while (b[j].mx == i)
                j++, ths++;
            if (ths == 1 && now + tot == i - 1)
                a[b[j - 1].num] = i;
            now += ths;
        }
    }
    for (i = 1; i <= n; i++)
        printf("%d\n", a[i]);
}