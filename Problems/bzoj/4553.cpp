#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int tree[100010], f[100010], MIN[100010], MAX[100010], a[100010], n, m, x, y;
struct Node
{
    int val, id, isl;
} tmp[100010];

bool cmp(Node a, Node b)
{
    if (a.val == b.val)
        return a.isl;
    else
        return a.val < b.val;
}

void add(int x, int val)
{
    if (val == 0)
        for (; x <= 100000; x += x & -x)
            tree[x] = 0;
    else
        for (; x <= 100000; x += x & -x)
            tree[x] = max(tree[x], val);
}

int getmax(int x)
{
    int res = 0;
    for (; x; x -= x & -x)
        res = max(res, tree[x]);
    return res;
}

void cdq(int l, int r)
{
    if (l == r)
        return;
    int cnt = 0;
    int mid = (l + r) / 2;
    cdq(l, mid);
    for (int i = l; i <= mid; i++)
        tmp[++cnt] = (Node){a[i], i, 1};
    for (int i = mid + 1; i <= r; i++)
        tmp[++cnt] = (Node){MIN[i], i, 0};
    sort(tmp + 1, tmp + 1 + cnt, cmp);
    for (int i = 1; i <= cnt; i++)
        if (tmp[i].isl)
            add(MAX[tmp[i].id], f[tmp[i].id]);
        else
            f[tmp[i].id] = max(f[tmp[i].id], getmax(a[tmp[i].id]) + 1);
    for (int i = 1; i <= cnt; i++)
        if (tmp[i].isl)
            add(MAX[tmp[i].id], 0);
    cdq(mid + 1, r);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        MIN[i] = MAX[i] = a[i];
        f[i] = 1;
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &x, &y);
        MIN[x] = min(MIN[x], y);
        MAX[x] = max(MAX[x], y);
    }
    cdq(1, n);
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans = max(ans, f[i]);
    }
    printf("%d\n", ans);
    system("pause");
    return 0;
}