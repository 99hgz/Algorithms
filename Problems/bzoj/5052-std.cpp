#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
const int maxn = 2000010, oo = 0x3f3f3f3f;
int rd()
{
    int x = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x;
}
set<int> s[maxn];
vector<int> qry[maxn], v[maxn];
int mn[maxn], a[maxn], l[maxn], r[maxn], ans[maxn],
    n, q;
void build(int u, int L, int R)
{
    mn[u] = oo;
    for (int i = L; i <= R; i++)
        s[u].insert(a[i]);
    if (L == R)
        return;
    int mid = (L + R) >> 1;
    build(u << 1, L, mid);
    build(u << 1 | 1, mid + 1, R);
}
int query(int u, int L, int R, int l, int r)
{
    if (l <= L && R <= r)
        return mn[u];
    int mid = (L + R) >> 1;
    int ret = oo;
    if (l <= mid)
        ret = min(ret, query(u << 1, L, mid, l, r));
    if (r > mid)
        ret = min(ret, query(u << 1 | 1, mid + 1, R, l, r));
    return ret;
}
void modify(int u, int L, int R, int l, int r, int x, int &res)
{
    set<int>::iterator i1 = s[u].lower_bound(x), i2;
    if (i1 != s[u].begin())
    {
        i2 = i1;
        i2--;
    }
    if ((i1 == s[u].end() || *i1 - x >= res) && (i1 == s[u].begin() || x - *i2 >= res))
    {
        res = min(res, query(u, L, R, l, r));
        return;
    }
    if (L == R)
    {
        int tmp = abs(a[L] - x);
        mn[u] = min(mn[u], tmp == 0 ? mn[u] : tmp);
        res = min(res, mn[u]);
        return;
    }
    int mid = (L + R) >> 1;
    if (l <= mid)
        modify(u << 1, L, mid, l, r, x, res);
    if (r > mid)
        modify(u << 1 | 1, mid + 1, R, l, r, x, res);
    mn[u] = min(mn[u << 1], mn[u << 1 | 1]);
}
int main()
{
    int res;
    n = rd();
    q = rd();
    for (int i = 1; i <= n; i++)
        a[i] = rd();
    for (int i = 1; i <= q; i++)
    {
        l[i] = rd();
        r[i] = rd();
        qry[l[i]].push_back(i);
    }
    build(1, 1, n);
    for (int i = n - 1; i; i--)
    {
        res = oo;
        modify(1, 1, n, i + 1, n, a[i], res);
        for (vector<int>::iterator it = qry[i].begin(); it != qry[i].end(); ++it)
            ans[*it] = query(1, 1, n, i + 1, r[*it]);
    }
    for (int i = 1; i <= q; i++)
        printf("%d\n", ans[i]);
}