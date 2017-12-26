#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

struct TREE
{
    ll sum, rmax, lsum, rsum;
} Tree[1000010 * 2];
int n, m, f[1000010], w[1000010], last[1000010], nlast[1000010];
ll ans;

void pushup(int rt)
{
    if (rt == 0)
        return;
    int lson = rt * 2, rson = rt * 2 + 1;
    Tree[rt].sum = Tree[lson].sum + Tree[rson].sum;
    Tree[rt].rmax = max(Tree[lson].rsum, 0ll) + max(Tree[rson].lsum, 0ll);
    Tree[rt].rmax = max(Tree[rt].rmax, max(Tree[lson].rmax, Tree[rson].rmax));
    Tree[rt].lsum = max(Tree[lson].lsum, Tree[lson].sum + max(Tree[rson].lsum, 0ll));
    Tree[rt].rsum = max(Tree[rson].rsum, Tree[rson].sum + max(Tree[lson].rsum, 0ll));
}

void modify(int rt, int l, int r, int pos, ll x)
{
    if (l == r)
    {
        Tree[rt].sum = Tree[rt].lsum = Tree[rt].rsum = x;
        Tree[rt].rmax = max(x, 0ll);
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        modify(rt * 2, l, mid, pos, x);
    else
        modify(rt * 2 + 1, mid + 1, r, pos, x);
    pushup(rt);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &f[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d", &w[i]);
    ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (last[f[i]])
            modify(1, 1, n, last[f[i]], -w[f[i]]);
        if (nlast[f[i]])
            modify(1, 1, n, nlast[f[i]], 0);
        modify(1, 1, n, i, w[f[i]]);
        nlast[f[i]] = last[f[i]];
        last[f[i]] = i;
        ans = max(ans, Tree[1].rmax);
    }
    printf("%lld\n", ans);
    system("pause");
    return 0;
}