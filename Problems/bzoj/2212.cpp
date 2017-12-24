#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

struct TREE
{
    int size, lson, rson;
} Tree[400005 * 19];
int tot, tot2, Root[400005], ch[400005][2], a[400005], n;
ll ans0, ans1, ans;

void build(int &rt, int l, int r, int x)
{
    if (rt == 0)
        rt = ++tot2;
    if (l == r)
    {
        Tree[rt].size = 1;
        return;
    }
    int mid = (l + r) >> 1;
    Tree[rt].size = 1;
    if (x <= mid)
        build(Tree[rt].lson, l, mid, x);
    else
        build(Tree[rt].rson, mid + 1, r, x);
}

int readTree()
{
    int id = ++tot;
    scanf("%d", &a[id]);
    build(Root[id], 1, n, a[id]);
    if (a[id] != 0)
        return id;
    ch[id][0] = readTree();
    ch[id][1] = readTree();
    return id;
}

int merge(int l, int r)
{
    if (!l || !r)
        return l + r;
    ans0 += (ll)Tree[Tree[l].rson].size * Tree[Tree[r].lson].size;
    ans1 += (ll)Tree[Tree[l].lson].size * Tree[Tree[r].rson].size;
    Tree[l].lson = merge(Tree[l].lson, Tree[r].lson);
    Tree[l].rson = merge(Tree[l].rson, Tree[r].rson);
    Tree[l].size = Tree[Tree[l].lson].size + Tree[Tree[l].rson].size;
    return l;
}

void solve(int rt)
{
    if (a[rt] != 0)
        return;
    solve(ch[rt][0]), solve(ch[rt][1]);
    ans0 = ans1 = 0;
    Root[rt] = merge(Root[ch[rt][0]], Root[ch[rt][1]]);
    ans += min(ans0, ans1);
}

int main()
{
    scanf("%d", &n);
    readTree();
    solve(1);
    printf("%lld\n", ans);
    system("pause");
    return 0;
}