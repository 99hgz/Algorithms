#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
int arr[50010];

int n, val[50010], Hash[50010], ans[300][50010], m, l, r;
struct B
{
    void clear()
    {
        memset(arr, 0, sizeof arr);
    }
    void insert(int x, int val)
    {
        for (; x <= n; x += x & (-x))
            arr[x] += val;
    }
    int query(int x)
    {
        int res = 0;
        for (; x; x -= x & (-x))
            res += arr[x];
        return res;
    }
} BIT;

struct TREE
{
    int lson, rson, num;
} Tree[50000 * 20];
int Root[50010], lastans, tot;

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
    int blocksize = sqrt(n), blocknum = n / blocksize;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &val[i]);
        Hash[i] = val[i];
    }
    sort(Hash + 1, Hash + 1 + n);
    int tn = unique(Hash + 1, Hash + 1 + n) - Hash - 1;
    for (int i = 1; i <= n; i++)
    {
        val[i] = lower_bound(Hash + 1, Hash + 1 + tn, val[i]) - Hash;
        Root[i] = Root[i - 1];
        modify(Root[i], 1, tn, val[i], 1);
    }

    for (int i = 0; i <= blocknum; i++)
    {
        BIT.clear();
        int R = (i + 1) * blocksize;
        for (int j = R; j <= n; j++)
        {
            ans[i][j] = ans[i][j - 1] + (j - R - BIT.query(val[j]));
            BIT.insert(val[j], 1);
        }
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &l, &r);
        l ^= lastans, r ^= lastans;
        int inblock = l / blocksize;
        lastans = 0;
        for (int j = l; j <= min((inblock + 1) * blocksize - 1, n); j++)
            lastans += query(Root[j], Root[r], 1, tn, 1, val[j] - 1);
        lastans += ans[inblock][r];
        printf("%d\n", lastans);
    }
    system("pause");
    return 0;
}