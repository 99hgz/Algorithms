#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
#define N 200005
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
int sum[N * 4];
int visit[N * 4];
int a[N], n, m, l[N], r[N], op[N], mid, q;
void pushUp(int rt)
{
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

void build(int l, int r, int rt)
{
    visit[rt] = 0;
    if (l == r)
    {
        sum[rt] = a[l] > mid ? 1 : 0;
        return;
    }
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    pushUp(rt);
}

void pushDown(int rt, int d)
{
    if (visit[rt] != 0)
    {
        visit[rt << 1] = visit[rt];
        visit[rt << 1 | 1] = visit[rt];
        if (visit[rt] == 1)
        {
            sum[rt << 1 | 1] = 0;
            sum[rt << 1] = 0;
        }
        else
        {
            sum[rt << 1 | 1] = (d >> 1);
            sum[rt << 1] = (d - (d >> 1));
        }
        visit[rt] = 0;
    }
}
void update(int L, int R, int c, int l, int r, int rt)
{
    //printf("update:%d %d %d %d %d %d\n", L, R, c, l, r, rt);
    if (visit[rt] == c + 1)
        return;
    if (L <= l && R >= r)
    {
        visit[rt] = c + 1;
        if (c == 0)
            sum[rt] = 0;
        else
            sum[rt] = (r - l + 1);
        return;
    }
    pushDown(rt, r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m)
        update(L, R, c, lson);
    if (R > m)
        update(L, R, c, rson);
    pushUp(rt);
}
int query(int L, int R, int l, int r, int rt)
{
    if (sum[rt] == 0)
        return 0;
    if (L <= l && R >= r)
    {
        return sum[rt];
    }
    pushDown(rt, r - l + 1);
    int m = (l + r) >> 1;
    int ret = 0;
    if (L <= m)
        ret += query(L, R, lson);
    if (R > m)
        ret += query(L, R, rson);
    return ret;
}

bool check(int x)
{
    //printf("check:%d\n", x);
    build(1, n, 1);
    for (int i = 1; i <= m; i++)
    {
        int tmp1 = query(l[i], r[i], 1, n, 1), tmp0 = r[i] - l[i] + 1 - tmp1;
        //printf("%d %d %d %d\n", l[i], r[i], tmp0, tmp1);
        if (op[i] == 0)
        {
            if (tmp0)
                update(l[i], l[i] + tmp0 - 1, 0, 1, n, 1);
            if (l[i] + tmp0 <= r[i])
                update(l[i] + tmp0, r[i], 1, 1, n, 1);
        }
        else
        {
            if (tmp1)
                update(l[i], l[i] + tmp1 - 1, 1, 1, n, 1);
            if (l[i] + tmp1 <= r[i])
                update(l[i] + tmp1, r[i], 0, 1, n, 1);
        }
    }
    return query(q, q, 1, n, 1) == 0;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &op[i], &l[i], &r[i]);
    }
    scanf("%d", &q);
    int l = 1, r = n, ans;
    while (l <= r)
    {
        mid = (l + r) >> 1;
        if (check(mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    printf("%d\n", ans);
    //system("pause");
    return 0;
}