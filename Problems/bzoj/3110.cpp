#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

struct TREE
{
    int lazy, sum, lson, rson;
} tree[30000000];

int tot, n, m, cases, a, b, c, root[200010];

void pushdown(int rt, int l, int r)
{

    if (!tree[rt].lson)
        tree[rt].lson = ++tot;
    if (!tree[rt].rson)
        tree[rt].rson = ++tot;
    if (tree[rt].lazy != 0)
    {
        int mid = (l + r) >> 1;
        tree[tree[rt].lson].lazy += tree[rt].lazy;
        tree[tree[rt].rson].lazy += tree[rt].lazy;
        tree[tree[rt].lson].sum += tree[rt].lazy * (mid - l + 1);
        tree[tree[rt].rson].sum += tree[rt].lazy * (r - mid);
        tree[rt].lazy = 0;
    }
}

int query_in(int rt, int l, int r, int L, int R)
{
    printf("query_in:rt=%d l=%d r=%d L=%d R=%d\n", rt, l, r, L, R);
    if (L <= l && r <= R)
        return tree[rt].sum;
    if (l > R || r < L)
        return 0;
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    return query_in(tree[rt].lson, l, mid, L, R) + query_in(tree[rt].rson, mid + 1, r, L, R);
}

void update_in(int rt, int l, int r, int L, int R)
{
    printf("update_in:rt=%d l=%d r=%d L=%d R=%d\n", rt, l, r, L, R);
    if (L <= l && r <= R)
    {
        tree[rt].lazy += 1;
        tree[rt].sum += (r - l + 1);
        return;
    }
    if (l > R || r < L)
        return;
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    update_in(tree[rt].lson, l, mid, L, R);
    update_in(tree[rt].rson, mid + 1, r, L, R);
}

void update_out(int rt, int l, int r, int x, int L, int R)
{
    printf("update_out:rt=%d l=%d r=%d x=%d L=%d R=%d\n", rt, l, r, x, L, R);
    if (!root[rt])
        root[rt] = ++tot;
    update_in(root[rt], 1, n, L, R);
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (x <= mid)
        update_out(rt * 2, l, mid, x, L, R);
    else
        update_out(rt * 2 + 1, mid + 1, r, x, L, R);
}

int query_out(int rt, int l, int r, int L, int R, int sL, int sR)
{
    printf("query_out:rt=%d l=%d r=%d L=%d R=%d sL=%d sR=%d\n", rt, l, r, L, R, sL, sR);
    if (L <= l && r <= R)
    {
        if (!root[rt])
            root[rt] = ++tot;
        return query_in(root[rt], 1, n, sL, sR);
    }
    if (l > R || r < L)
        return 0;
    int mid = (l + r) >> 1;
    return query_out(rt * 2, l, mid, L, R, sL, sR) + query_out(rt * 2 + 1, mid + 1, r, L, R, sL, sR);
}

int work(int a, int b, int c)
{
    int l = 1, r = 50010, ans = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        int tmp = query_out(1, 1, 50010, mid + 1, n, a, b);
        printf("query_out: val_range=%d~%d in [%d,%d] res=%d\n", mid + 1, n, a, b, tmp);
        if (tmp < c)
        {
            ans = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    return ans;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d%d", &cases, &a, &b, &c);
        if (cases == 1)
            update_out(1, 1, 50010, c, a, b);
        else
            printf("%d\n", work(a, b, c));
    }
    system("pause");
    return 0;
}