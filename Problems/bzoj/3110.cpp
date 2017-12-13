#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef unsigned int ll;

struct TREE
{
    int lazy, lson, rson;
    ll sum;
} tree[30000000];

int tot, n, m, root[200010];

void pushdown(int rt, int l, int r)
{
    if (tree[rt].lazy == 0)
        return;
=======
typedef long long ll;

struct TREE
{
    int lazy, sum, lson, rson;
} tree[30000000];

int tot, n, m, cases, a, b, c, root[200010];

void pushdown(int rt, int l, int r)
{

>>>>>>> e53e6aad192c05db996fc16c40cb0968ea05a541
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

<<<<<<< HEAD
ll query_in(int &rt, int l, int r, int L, int R)
{
    //printf("query_in:rt=%d l=%d r=%d L=%d R=%d\n", rt, l, r, L, R);
    if (l > R || r < L)
        return 0;
    if (rt == 0)
        rt = ++tot;
    if (L <= l && r <= R)
        return tree[rt].sum;
=======
int query_in(int rt, int l, int r, int L, int R)
{
    printf("query_in:rt=%d l=%d r=%d L=%d R=%d\n", rt, l, r, L, R);
    if (L <= l && r <= R)
        return tree[rt].sum;
    if (l > R || r < L)
        return 0;
>>>>>>> e53e6aad192c05db996fc16c40cb0968ea05a541
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    return query_in(tree[rt].lson, l, mid, L, R) + query_in(tree[rt].rson, mid + 1, r, L, R);
}

<<<<<<< HEAD
void update_in(int &rt, int l, int r, int L, int R)
{
    //printf("update_in:rt=%d l=%d r=%d L=%d R=%d\n", rt, l, r, L, R);
    if (l > R || r < L)
        return;
    if (rt == 0)
        rt = ++tot;
=======
void update_in(int rt, int l, int r, int L, int R)
{
    printf("update_in:rt=%d l=%d r=%d L=%d R=%d\n", rt, l, r, L, R);
>>>>>>> e53e6aad192c05db996fc16c40cb0968ea05a541
    if (L <= l && r <= R)
    {
        tree[rt].lazy += 1;
        tree[rt].sum += (r - l + 1);
        return;
    }
<<<<<<< HEAD

    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    tree[rt].sum += min(r, R) - max(l, L) + 1;
=======
    if (l > R || r < L)
        return;
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
>>>>>>> e53e6aad192c05db996fc16c40cb0968ea05a541
    update_in(tree[rt].lson, l, mid, L, R);
    update_in(tree[rt].rson, mid + 1, r, L, R);
}

void update_out(int rt, int l, int r, int x, int L, int R)
{
<<<<<<< HEAD
    //printf("update_out:rt=%d l=%d r=%d x=%d L=%d R=%d\n", rt, l, r, x, L, R);
=======
    printf("update_out:rt=%d l=%d r=%d x=%d L=%d R=%d\n", rt, l, r, x, L, R);
>>>>>>> e53e6aad192c05db996fc16c40cb0968ea05a541
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

<<<<<<< HEAD
int ans, cases[100010], a[50010], b[50010], c[50010], Hash[50010], insertnum, tn;

void work(int a, int b, ll c)
{
    int l = 1, r = tn, rt = 1, omid = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (mid == omid)
            return;
        ll Rank = query_in(root[rt * 2 + 1], 1, n, a, b);
        if (c > Rank)
            ans = mid, rt = rt * 2, r = mid, c -= Rank;
        else
            rt = rt * 2 + 1, l = mid + 1;
        omid = mid;
    }
=======
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
>>>>>>> e53e6aad192c05db996fc16c40cb0968ea05a541
}

int main()
{
<<<<<<< HEAD

    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d%d", &cases[i], &a[i], &b[i], &c[i]);
        if (cases[i] == 1)
            Hash[++insertnum] = c[i];
    }
    sort(Hash + 1, Hash + 1 + insertnum);
    tn = unique(Hash + 1, Hash + 1 + insertnum) - Hash - 1;
    for (int i = 1; i <= m; i++)
        if (cases[i] == 1)
            c[i] = lower_bound(Hash + 1, Hash + 1 + tn, c[i]) - Hash;
    for (int i = 1; i <= m; i++)
    {
        if (cases[i] == 1)
            update_out(1, 1, tn, c[i], a[i], b[i]);
        else
        {
            ans = 0;
            work(a[i], b[i], c[i]);
            printf("%d\n", Hash[ans]);
        }
=======
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d%d", &cases, &a, &b, &c);
        if (cases == 1)
            update_out(1, 1, 50010, c, a, b);
        else
            printf("%d\n", work(a, b, c));
>>>>>>> e53e6aad192c05db996fc16c40cb0968ea05a541
    }
    system("pause");
    return 0;
}