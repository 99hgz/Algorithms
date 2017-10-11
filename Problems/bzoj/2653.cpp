#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

int bh, n, m, ans, l, r;
int root[20100];
int a[20100];
int q[5];

struct NODe
{
    int lson, rson, all, lmax, rmax;
} tree[2010000];
pair<int, int> h[20100];

NODe operator+(const NODe &a, const NODe &b)
{
    NODe tmp;
    tmp.lson = 0;
    tmp.rson = 0;
    tmp.all = a.all + b.all;
    tmp.lmax = max(b.lmax, a.lmax + b.all);
    tmp.rmax = max(a.rmax, a.all + b.rmax);
    return tmp;
}

void push_up(int bh)
{
    int lson = tree[bh].lson, rson = tree[bh].rson;
    tree[bh].all = tree[lson].all + tree[rson].all;
    tree[bh].lmax = max(tree[rson].lmax, tree[lson].lmax + tree[rson].all);
    tree[bh].rmax = max(tree[lson].rmax, tree[lson].all + tree[rson].rmax);
}

int build(int l, int r)
{
    bh++;
    int tbh = bh;
    if (l == r)
    {
        tree[bh].all = tree[bh].lmax = tree[bh].rmax = 1;
        return bh;
    }
    tree[tbh].lson = build(l, (l + r) >> 1);
    tree[tbh].rson = build(((l + r) >> 1) + 1, r);
    push_up(tbh);
    return tbh;
}

int update(int i, int l, int r, int old)
{
    //printf("%d %d %d %d\n", i, l, r, old);
    if (l == r)
    {
        bh++;
        tree[bh].all = -1;
        tree[bh].lmax = tree[bh].rmax = -1;
        //push_up(bh);
        return bh;
    }
    int tbh;
    int mid = (l + r) >> 1;
    if (i > mid)
    {
        bh++;
        tbh = bh;
        //tree[bh].all = tree[old].v + 1;
        tree[bh].lson = tree[old].lson;
        tree[tbh].rson = update(i, mid + 1, r, tree[old].rson);
    }
    else
    {
        bh++;
        tbh = bh;
        tree[bh].rson = tree[old].rson;
        tree[tbh].lson = update(i, l, mid, tree[old].lson);
    }
    push_up(tbh);
    return tbh;
}

NODe query(int rt, int l, int r, int L, int R)
{
    int mid = (l + r) >> 1;
    if (l == L && R == r)
        return tree[rt];
    if (R <= mid)
        return query(tree[rt].lson, l, mid, L, R);
    else if (L > mid)
        return query(tree[rt].rson, mid + 1, r, L, R);
    else
        return query(tree[rt].lson, l, mid, L, mid) + query(tree[rt].rson, mid + 1, r, mid + 1, R);
}

bool judge(int x)
{
    //printf("%d\n", x);
    NODe TMPM;
    NODe TMPL = query(root[x], 0, n - 1, q[0], q[1]);
    if (q[1] + 1 <= q[2] - 1)
    {
        TMPM = query(root[x], 0, n - 1, q[1] + 1, q[2] - 1);
    }
    else
    {
        TMPM = (NODe){0, 0, 0, 0, 0};
    }
    NODe TMPR = query(root[x], 0, n - 1, q[2], q[3]);
    return (TMPL.lmax + TMPM.all + TMPR.rmax) >= 0;
}

int main()
{
    scanf("%d", &n);
    memset(tree, 0, sizeof(tree));
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        h[i] = make_pair(a[i], i);
    }
    sort(h, h + n);
    root[0] = build(0, n - 1);
    for (int i = 1; i < n; i++)
        root[i] = update(h[i - 1].second, 0, n - 1, root[i - 1]);
    int lastans = 0;
    scanf("%d", &m);
    int L, R;
    int MM = m;
    while (MM--)
    {
        scanf("%d%d%d%d", &q[0], &q[1], &q[2], &q[3]);
        for (int i = 0; i < 4; i++)
            q[i] = (q[i] + lastans) % n;
        sort(q, q + 4);
        L = 0;
        R = n - 1;
        ans = 0;
        while (L <= R)
        {
            int Mid = (L + R) >> 1;
            if (judge(Mid))
                ans = Mid, L = Mid + 1;
            else
                R = Mid - 1;
        }
        lastans = h[ans].first;
        printf("%d\n", lastans);
    }
    system("pause");
    return 0;
}