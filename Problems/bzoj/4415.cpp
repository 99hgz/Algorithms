#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

struct Node
{
    int sl;
} tree[700000 * 5];
int n, x, now, tmp;

void build(int l, int r, int rt)
{
    if (l == r)
    {
        tree[rt].sl = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, rt * 2);
    build(mid + 1, r, rt * 2 + 1);
    tree[rt].sl = tree[rt * 2].sl + tree[rt * 2 + 1].sl;
}

int query(int rt, int sl, int l, int r)
{
    tree[rt].sl--;
    if (l == r)
        return l;
    if (tree[rt * 2].sl >= sl)
        return query(rt * 2, sl, l, (l + r) >> 1);
    else
        return query(rt * 2 + 1, sl - tree[rt * 2].sl, ((l + r) >> 1) + 1, r);
}

int main()
{
    scanf("%d", &n);
    int tmpn = n;
    build(1, n, 1);
    int now = 0;
    while (n--)
    {
        scanf("%d", &x);
        (now += x) %= (n + 1);
        printf("%d\n", query(1, now + 1, 1, tmpn));
    }
    system("pause");
    return 0;
}