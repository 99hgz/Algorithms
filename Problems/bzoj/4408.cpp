#include <cstdio>
using namespace std;

struct TREE
{
    int num, lson, rson;
} Tree[100010 * 35];

int tot, n, Root[100010], val[100010], m, l, r;
int inf = 1000000000;

void modify(int &rt, int l, int r, int x, int base)
{
    int thisrt = ++tot;
    Tree[thisrt] = Tree[rt];
    rt = thisrt;
    int mid = (l + r) >> 1;
    Tree[thisrt].num += base;
    if (l == r)
        return;
    if (x <= mid)
        modify(Tree[thisrt].lson, l, mid, x, base);
    else
        modify(Tree[thisrt].rson, mid + 1, r, x, base);
}

int query(int rt1, int rt2, int l, int r, int L, int R)
{
    if (L <= l && r <= R)
        return Tree[rt2].num - Tree[rt1].num;
    if (r < L || l > R)
        return 0;
    int mid = (l + r) >> 1;
    return query(Tree[rt1].lson, Tree[rt2].lson, l, mid, L, R) + query(Tree[rt1].rson, Tree[rt2].rson, mid + 1, r, L, R);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        Root[i] = Root[i - 1];
        scanf("%d", &val[i]);
        modify(Root[i], 0, inf, val[i], val[i]);
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &l, &r);
        int ans = 1;
        while (1)
        {
            int tmp = query(Root[l - 1], Root[r], 0, inf, 0, ans);
            if (tmp < ans)
            {
                printf("%d\n", ans);
                break;
            }
            ans = tmp + 1;
        }
    }
}