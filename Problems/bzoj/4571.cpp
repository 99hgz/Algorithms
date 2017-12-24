#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
struct TREE
{
    int lson, rson, num;
} Tree[100010 * 17];
int Root[200010], tot;
int n, m, a[200010], b, x, l, r;
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
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        Root[i] = Root[i - 1];
        modify(Root[i], 1, 100000, a[i], 1);
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d%d", &b, &x, &l, &r);
        int pre = 0;
        for (int j = 3; j >= 0; j--)
        {
            int base = 1 << j;
            if (((b >> j) & 1) == 0)
            {
                int tmp = query(Root[l - 1], Root[r], 1, 100000, pre + base - x, pre + 2 * base - 1 - x);
                //printf("1query:%d %d %d %d\n", j, tmp, pre + base - x, pre + 2 * base - 1 - x);
                if (tmp)
                    pre |= base;
            }
            else
            {
                int tmp = query(Root[l - 1], Root[r], 1, 100000, pre - x, pre + base - 1 - x);
                //printf("0query:%d %d %d %d\n", j, tmp, pre - x, pre + base - 1 - x);
                if (tmp == 0)
                    pre |= base;
            }
        }
        printf("%d\n", b ^ pre);
    }
    system("pause");
    return 0;
}