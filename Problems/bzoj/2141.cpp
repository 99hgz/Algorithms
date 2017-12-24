#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int tot, Root[20010 * 4], Hash[20010];
struct TREE
{
    int num, lson, rson;
} Tree[200010 * 100];
int n, val[20010], ans, tn, m, l, r;
void insert_in(int &rt, int l, int r, int x, int base)
{
    if (rt == 0)
        rt = ++tot;
    Tree[rt].num += base;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (x <= mid)
        insert_in(Tree[rt].lson, l, mid, x, base);
    else
        insert_in(Tree[rt].rson, mid + 1, r, x, base);
}

int query_in(int rt, int l, int r, int L, int R)
{
    if (L > R)
        return 0;
    if (rt == 0)
        return 0;
    if (L <= l && r <= R)
        return Tree[rt].num;
    if (r < L || l > R)
        return 0;
    int mid = (l + r) >> 1;
    return query_in(Tree[rt].lson, l, mid, L, R) + query_in(Tree[rt].rson, mid + 1, r, L, R);
}

void insert_out(int rt, int l, int r, int x, int val, int base)
{
    insert_in(Root[rt], 1, tn, val, base);
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (x <= mid)
        insert_out(rt * 2, l, mid, x, val, base);
    else
        insert_out(rt * 2 + 1, mid + 1, r, x, val, base);
}

int query_out(int rt, int l, int r, int L, int R, int inl, int inr)
{
    //printf("query_out:%d %d %d %d %d %d %d\n", rt, l, r, L, R, inl, inr);
    if (L > R)
        return 0;
    if (L <= l && r <= R)
        return query_in(Root[rt], 1, tn, inl, inr);
    if (r < L || l > R)
        return 0;
    int mid = (l + r) >> 1;
    return query_out(rt * 2, l, mid, L, R, inl, inr) + query_out(rt * 2 + 1, mid + 1, r, L, R, inl, inr);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &val[i]);
        Hash[i] = val[i];
    }
    sort(Hash + 1, Hash + 1 + n);
    tn = unique(Hash + 1, Hash + 1 + n) - Hash - 1;
    for (int i = 1; i <= n; i++)
    {
        val[i] = lower_bound(Hash + 1, Hash + 1 + tn, val[i]) - Hash;
        //printf("true:%d\n", val[i]);
        insert_out(1, 1, n, i, val[i], 1);
        ans += query_out(1, 1, n, 1, i - 1, val[i] + 1, tn);
    }
    printf("%d\n", ans);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &l, &r);
        if (l > r)
            swap(l, r);
        ans -= query_out(1, 1, n, l + 1, r - 1, val[r] + 1, tn) + query_out(1, 1, n, l + 1, r - 1, 1, val[l] - 1);
        //printf("step1:%d\n", ans);
        ans += query_out(1, 1, n, l + 1, r - 1, 1, val[r] - 1) + query_out(1, 1, n, l + 1, r - 1, val[l] + 1, tn);
        //printf("step2:%d %d\n", query_out(1, 1, n, l + 1, r - 1, 1, val[r] - 1), query_out(1, 1, n, l + 1, r - 1, val[l] + 1, tn));
        insert_out(1, 1, n, l, val[l], -1);
        insert_out(1, 1, n, r, val[r], -1);
        if (val[l] < val[r])
            ans++;
        if (val[l] > val[r])
            ans--;
        swap(val[l], val[r]);
        insert_out(1, 1, n, l, val[l], 1);
        insert_out(1, 1, n, r, val[r], 1);
        printf("%d\n", ans);
    }
    // system("pause");
    return 0;
}