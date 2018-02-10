#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

char cases[100];
int n, tot;
int tree[100010 * 4], t;
double ans, k[100010], b[100010];

bool pd(int x, int y, int pos)
{
    double tmp = pos;
    return b[x] + k[x] * (tmp - 1.0) > b[y] + k[y] * (tmp - 1.0);
}

double calc(int x, int pos)
{
    double tmp = pos;
    return b[x] + k[x] * (tmp - 1.0);
}

void insert(int rt, int l, int r, int id)
{
    if (l == r)
    {
        if (pd(id, tree[rt], l))
            tree[rt] = id;
        return;
    }
    int mid = (l + r) >> 1;
    if (k[id] > k[tree[rt]])
    {
        if (pd(id, tree[rt], mid))
            insert(rt * 2, l, mid, tree[rt]), tree[rt] = id;
        else
            insert(rt * 2 + 1, mid + 1, r, id);
    }
    else
    {
        if (pd(id, tree[rt], mid))
            insert(rt * 2 + 1, mid + 1, r, tree[rt]), tree[rt] = id;
        else
            insert(rt * 2, l, mid, id);
    }
}

double getans(int rt, int l, int r, int pos)
{
    if (l == r)
        return calc(tree[rt], pos);
    int mid = (l + r) >> 1;
    double res = calc(tree[rt], pos);
    if (pos <= mid)
        res = max(res, getans(rt * 2, l, mid, pos));
    else
        res = max(res, getans(rt * 2 + 1, mid + 1, r, pos));
    return res;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", cases);
        if (cases[0] == 'P')
        {
            tot++;
            scanf("%lf%lf", &b[tot], &k[tot]);
            insert(1, 1, n, tot);
        }
        else
        {
            scanf("%d", &t);
            printf("%d\n", floor(getans(1, 1, n, t) / 100.0));
        }
    }
    system("pause");
    return 0;
}