#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

typedef pair<int, int> Rootpair;
#define mp make_pair
int tot, opt, x, Root, n;
struct TREENODE
{
    int val, fix, size, rev, MIN, ch[2];
} Tree[100005];

int newnode(int x)
{
    tot++;
    Tree[tot] = (TREENODE){x, rand(), 1, 0, x};
    Tree[tot].ch[0] = Tree[tot].ch[1] = 0;
    return tot;
}

void doreverse(int rt)
{
    Tree[rt].rev ^= 1;
    swap(Tree[rt].ch[0], Tree[rt].ch[1]);
}

void pushdown(int rt)
{
    if (Tree[rt].rev)
    {
        doreverse(Tree[rt].ch[0]);
        doreverse(Tree[rt].ch[1]);
        Tree[rt].rev = 0;
    }
}

void up(int rt)
{
    Tree[rt].size = Tree[Tree[rt].ch[0]].size + Tree[Tree[rt].ch[1]].size + 1;
    Tree[rt].MIN = Tree[rt].val;
    if (Tree[rt].ch[0])
        Tree[rt].MIN = min(Tree[rt].MIN, Tree[Tree[rt].ch[0]].MIN);
    if (Tree[rt].ch[1])
        Tree[rt].MIN = min(Tree[rt].MIN, Tree[Tree[rt].ch[1]].MIN);
}

void merge(int &rt, int L, int R)
{
    if (!L || !R)
    {
        rt = L + R;
        //up(rt);
        return;
    }
    if (Tree[L].fix < Tree[R].fix)
        pushdown(L), rt = L, merge(Tree[rt].ch[1], Tree[rt].ch[1], R);
    else
        pushdown(R), rt = R, merge(Tree[rt].ch[0], L, Tree[rt].ch[0]);
    up(rt);
}

Rootpair split(int rt, int kth)
{
    pushdown(rt);
    if (!kth)
    {
        //up(rt);
        return mp(0, rt);
    }
    int ls = Tree[rt].ch[0], rs = Tree[rt].ch[1];
    if (kth == Tree[ls].size)
    {
        Tree[rt].ch[0] = 0;
        up(rt);
        return mp(ls, rt);
    }
    if (kth == Tree[ls].size + 1)
    {
        Tree[rt].ch[1] = 0;
        up(rt);
        return mp(rt, rs);
    }
    if (kth < Tree[ls].size)
    {
        Rootpair tmp = split(ls, kth);
        Tree[rt].ch[0] = tmp.second;
        up(rt);
        return mp(tmp.first, rt);
    }
    Rootpair tmp = split(rs, kth - Tree[ls].size - 1);
    Tree[rt].ch[1] = tmp.first;
    up(rt);
    return mp(rt, tmp.second);
}

int getrank(int val)
{
    int res = 0, tmp = 0x7f7f7f7f, rt = Root;
    while (rt)
    {
        pushdown(rt);
        if (val == Tree[rt].val)
            tmp = min(tmp, res + Tree[Tree[rt].ch[0]].size + 1);
        if (val == Tree[Tree[rt].ch[1]].MIN)
            res += Tree[Tree[rt].ch[0]].size + 1, rt = Tree[rt].ch[1];
        else if (val == Tree[Tree[rt].ch[0]].MIN)
            rt = Tree[rt].ch[0];
        else
            break;
    }
    return tmp == 0x7f7f7f7f ? res : tmp;
}

void insert(int val)
{
    int rt = newnode(val);
    merge(Root, Root, rt);
}

void debug(int rt)
{
    if (rt == 0)
        return;
    pushdown(rt);
    debug(Tree[rt].ch[0]);
    printf("%d ", Tree[rt].val);
    debug(Tree[rt].ch[1]);
    up(rt);
}

void reverse(int l, int r)
{
    Rootpair tmp1 = split(Root, l - 1);
    Rootpair tmp2 = split(tmp1.second, r - l + 1);
    doreverse(tmp2.first);
    int rt;
    merge(rt, tmp1.first, tmp2.first);
    merge(Root, rt, tmp2.second);
}

struct HASH
{
    int val, id;
} Hash[100010];
bool cmp(HASH a, HASH b)
{
    if (a.val == b.val)
        return a.id < b.id;
    return a.val < b.val;
}
int a[100010];

int main()
{
    int m, l, r;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        Hash[i].val = a[i];
        Hash[i].id = i;
    }
    sort(Hash + 1, Hash + 1 + n, cmp);
    for (int i = 1; i <= n; i++)
        a[Hash[i].id] = i;
    for (int i = 1; i <= n; i++)
        insert(a[i]);

    //printf("\n");
    for (int i = 1; i <= n; i++)
    {
        int tmp = getrank(i);
        printf("%d ", i + tmp - 1);
        reverse(1, tmp);
        Rootpair tmp1 = split(Root, 1);
        Root = tmp1.second;
    }
    system("pause");
    return 0;
}