#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

struct Node
{
    int val, pos;
} S[300010];
int tot;
struct TREE
{
    int num, lson, rson;
} Tree[300010 * 60];
int n, m, type, a[300010], Root[300010], l, r;
vector<int> vec[300010];

void init()
{
    int top = 0;
    for (int i = 1; i <= n; i++)
    {
        bool had = 0;
        while (top && S[top].val <= a[i])
        {
            vec[S[top].pos].push_back(i);
            if (S[top].val == a[i])
                had = 1;
            top--;
        }
        if (top && !had)
            vec[S[top].pos].push_back(i);
        S[++top] = (Node){a[i], i};
    }
}

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
    scanf("%d%d%d", &n, &m, &type);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    init();
    for (int i = 1; i <= n; i++)
    {
        Root[i] = Root[i - 1];
        for (int j = 0; j < vec[i].size(); j++)
            modify(Root[i], 1, n, vec[i][j], 1);
        /*if (i < n)
            modify(Root[i], 1, n, i + 1, 1);*/
    }
    int lastans = 0;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &l, &r);
        if (type)
        {
            int u = (l + lastans - 1) % n + 1;
            int v = (r + lastans - 1) % n + 1;
            l = min(u, v), r = max(u, v);
        }
        lastans = query(Root[l - 1], Root[r], 1, n, l, r);
        printf("%d\n", lastans);
    }
    //system("pause");
    return 0;
}