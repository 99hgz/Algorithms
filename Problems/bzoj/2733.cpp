#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, m, imp[100010], reimp[100010], rt[100010], a1, b1, father[100010], Q;
char CASE[10];
int tot;
struct TREE
{
    int lson, rson, val;
} Tree[5000100];

int getfather(int x)
{
    return father[x] == 0 ? x : father[x] = getfather(father[x]);
}

void build(int rt, int l, int r, int val)
{
    //printf("build:%d %d %d %d\n", rt, l, r, val);
    if (l == r)
    {
        Tree[rt].val = 1;
        return;
    }
    int mid = (l + r) >> 1;
    Tree[rt].val++;
    if (mid >= val)
    {
        if (Tree[rt].lson == 0)
            Tree[rt].lson = ++tot;
        build(Tree[rt].lson, l, mid, val);
    }
    else
    {

        if (Tree[rt].rson == 0)
            Tree[rt].rson = ++tot;
        build(Tree[rt].rson, mid + 1, r, val);
    }
}

int merge(int rt1, int rt2)
{
    if (!rt1 || !rt2)
        return rt1 ^ rt2;
    Tree[rt1].lson = merge(Tree[rt1].lson, Tree[rt2].lson);
    Tree[rt1].rson = merge(Tree[rt1].rson, Tree[rt2].rson);
    Tree[rt1].val = Tree[Tree[rt1].lson].val + Tree[Tree[rt1].rson].val;
    //printf("merge:%d val=%d\n", rt1, Tree[rt1].val);
    return rt1;
}

int query(int rt, int val, int l, int r)
{
    if (l == r)
        return l;
    int mid = (l + r) >> 1;
    //printf("query rt=%d val=%d\n", rt, Tree[Tree[rt].rson].val);
    if (Tree[Tree[rt].rson].val >= val)
        return query(Tree[rt].rson, val, mid + 1, r);
    else
        return query(Tree[rt].lson, val - Tree[Tree[rt].rson].val, l, mid);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        int k;
        scanf("%d", &k);
        imp[i] = n - k + 1;
        reimp[imp[i]] = i;
    }
    for (int i = 1; i <= n; i++)
    {
        rt[i] = ++tot;
        build(rt[i], 1, n, imp[i]);
    }
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        int fa = getfather(u);
        int fb = getfather(v);
        if (fa != fb)
        {
            father[fa] = fb;
            rt[fb] = merge(rt[fa], rt[fb]);
        }
    }
    scanf("%d", &Q);
    for (int i = 1; i <= Q; i++)
    {
        scanf("%s", CASE);
        if (CASE[0] == 'Q')
        {
            int u, v;
            scanf("%d%d", &u, &v);
            //printf("sign:%d\n", getfather(u));
            if (Tree[rt[getfather(u)]].val < v)
                printf("-1\n");
            else
                printf("%d\n", reimp[query(rt[getfather(u)], v, 1, n)]);
        }
        else
        {
            int u, v;
            scanf("%d%d", &u, &v);
            int fa = getfather(u);
            int fb = getfather(v);
            if (fa != fb)
            {
                father[fa] = fb;
                rt[fb] = merge(rt[fa], rt[fb]);
            }
        }
    }
    system("pause");
    return 0;
}