#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <vector>
#include <cmath>
#define maxn 800000
using namespace std;
typedef long long ll;

int n, m, len, k;
int range_min[100];
set<int> st[maxn];
int inf = 0x7f7f7f7f;
int res, c[maxn];
struct Node
{
    int l, r;
} que[maxn];
vector<int> qry[maxn];

void build(int id, int l, int r)
{
    printf("%d %d %d\n", id, l, r);
    range_min[id] = inf;
    for (int i = l; i <= r; i++)
    {
        st[id].insert(c[i]);
    }
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
}

int query(int id, int L, int R, int l, int r)
{
    printf("%d %d %d %d %d\n", id, L, R, l, r);
    if (l <= L && R <= r)
        return range_min[id];
    int mid = (L + R) >> 1;
    int res = inf;
    if (l < mid)
        res = min(res, query(id * 2, L, mid, l, r));
    if (r > mid)
        res = min(res, query(id * 2 + 1, mid + 1, R, l, r));
    return res;
}

void push_up(int id)
{
    range_min[id] = min(range_min[id * 2], range_min[id * 2 + 1]);
}

void modify(int id, int L, int R, int l, int r, int x, int &res)
{
    printf("%d %d %d\n", id, L, x);
    //int items;
    set<int>::iterator it;
    printf("vals:");
    for (it = st[id].begin(); it != st[id].end(); it++)
    {
        printf("%d ", *it);
    }
    printf("\n");
    set<int>::iterator right = st[id].lower_bound(x), left;
    if (right != st[id].begin())
    {
        left = right;
        left--;
    }
    if ((right == st[id].end() || x + res <= *right) && ((right == st[id].begin()) || (*left + res <= x)))
    {
        res = min(res, query(id, L, R, l, r));
        return;
    }
    if (L == R)
    {
        int tmp = abs(x - c[L]);
        range_min[id] = min(range_min[id], tmp == 0 ? range_min[id] : tmp);
        res = min(res, range_min[id]);
        return;
    }
    int mid = (L + R) >> 1;
    if (l < mid)
        modify(id * 2, L, mid, l, r, x, res);
    if (r > mid)
        modify(id * 2 + 1, mid + 1, R, l, r, x, res);
    push_up(id);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &c[i]);
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &que[i].l, &que[i].r);
        qry[que[i].l].push_back(i);
    }
    build(1, 1, n);
    for (int i = n - 1; i >= 1; i--)
    {
        res = inf;
        modify(1, 1, n, i + 1, n, c[i], res);
        for (int j = 0; j < qry[i].size(); j++)
        {
            printf("%d\n", query(1, 1, n, i + 1, que[qry[i][j]].r));
        }
    }
    return 0;
}