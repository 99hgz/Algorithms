//HDU 2665
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

int bh, n, tn, m, l, r, G;
int root[100010];
int a[100011], Hash[100011];
struct NODe
{
    int lson, rson, v;
} tree[2000010];

int build(int l, int r)
{
    bh++;
    //printf("build:%d %d %d\n", l, r, bh);
    int tbh = bh;
    if (l == r)
    {
        tree[bh].v = 0;
        return bh;
    }
    tree[tbh].lson = build(l, (l + r) >> 1);
    tree[tbh].rson = build(((l + r) >> 1) + 1, r);
    return tbh;
}

int update(int i, int l, int r, int old)
{

    if (l == r)
    {
        bh++;
        tree[bh].v = tree[old].v + 1;
        return bh;
    }
    int tbh;
    int mid = (l + r) >> 1;
    if (i > mid)
    {
        bh++;
        tbh = bh;
        tree[bh].v = tree[old].v + 1;
        tree[bh].lson = tree[old].lson;
        tree[tbh].rson = update(i, mid + 1, r, tree[old].rson);
    }
    else
    {
        bh++;
        tbh = bh;
        tree[bh].v = tree[old].v + 1;
        tree[bh].rson = tree[old].rson;
        tree[tbh].lson = update(i, l, mid, tree[old].lson);
    }
    //printf("%d %d %d %d", i, l, r, old);
    //printf(" change->%d\n", tbh);
    //printf("lson=%d rson=%d\n", tree[tbh].lson, tree[tbh].rson);
    return tbh;
}

int query(int G, int bh1, int bh2, int l, int r)
{
    //printf("%d %d %d %d %d\n", G, bh1, bh2, l, r);
    if (l == r)
    {
        return l;
    }
    int mid = (l + r) >> 1;
    int lsl = tree[tree[bh2].lson].v - tree[tree[bh1].lson].v;
    if (G <= lsl)
    {
        return query(G, tree[bh1].lson, tree[bh2].lson, l, mid);
    }
    else
    {
        return query(G - lsl, tree[bh1].rson, tree[bh2].rson, mid + 1, r);
    }
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        bh = 0;
        scanf("%d%d", &n, &m);
        a[0] = -1054;
        memset(tree, 0, sizeof(tree));
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &a[i]);
            Hash[i] = a[i];
        }
        sort(Hash + 1, Hash + n + 1);
        int tn = unique(Hash + 1, Hash + n + 1) - Hash - 1;
        //int tn = n;
        root[0] = build(1, tn);
        for (int i = 1; i <= n; i++)
        {
            int x = lower_bound(Hash + 1, Hash + tn + 1, a[i]) - Hash;
            root[i] = update(x, 1, tn, root[i - 1]);
            //root[i] = update(a[i], 1, tn, root[i - 1]);
        }
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d%d", &l, &r, &G);
            printf("%d\n", Hash[query(G, root[l - 1], root[r], 1, tn)]);
            //printf("%d\n", query(G, root[l - 1], root[r], 1, tn));
        }
    }
    //system("pause");
    //scanf("%d", &n);
    return 0;
}