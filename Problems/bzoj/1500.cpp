#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

typedef pair<int, int> Rootpair;
#define mp make_pair
int tot, opt, x, Root, n, m;
struct TREENODE
{
    int val, fix, size, rev, makesame, sum, ch[2];
} Tree[200010];

void doreverse(int rt)
{
    if (rt == 0)
        return;
    Tree[rt].rev ^= 1;
    swap(Tree[rt].ch[0], Tree[rt].ch[1]);
}

int newnode(int x)
{
    tot++;
    Tree[tot] = (TREENODE){x, rand(), 1, 0, -1001, x};
    Tree[tot].ch[0] = Tree[tot].ch[1] = 0;
    return tot;
}

void up(int rt)
{
    if (rt == 0)
        return;
    Tree[rt].size = Tree[Tree[rt].ch[0]].size + Tree[Tree[rt].ch[1]].size + 1;
    Tree[rt].sum = Tree[Tree[rt].ch[0]].sum + Tree[Tree[rt].ch[1]].sum + Tree[rt].val;
    Tree[rt].rmax = Tree[rt].val;
    Tree[rt].rmax=max(Tree[Tree[rt].ch[0]].rmax,
}

void pushdown(int rt)
{
    if (Tree[rt].rev)
    {
        doreverse(Tree[rt].ch[0]);
        doreverse(Tree[rt].ch[1]);
        Tree[rt].rev = 0;
    }
    if (Tree[rt].makesame != -1001)
    {
        if (Tree[rt].ch[0])
        {
            Tree[Tree[rt].ch[0]].val = Tree[rt].makesame;
            Tree[Tree[rt].ch[0]].makesame = Tree[rt].makesame;
            Tree[Tree[rt].ch[0]].sum = Tree[rt].makesame * Tree[Tree[rt].ch[0]].size;
        }
        if (Tree[rt].ch[1])
        {
            Tree[Tree[rt].ch[1]].val = Tree[rt].makesame;
            Tree[Tree[rt].ch[1]].makesame = Tree[rt].makesame;
            Tree[Tree[rt].ch[1]].sum = Tree[rt].makesame * Tree[Tree[rt].ch[1]].size;
        }
        Tree[rt].makesame = -1001;
    }
}

void merge(int &rt, int L, int R)
{
    if (!L || !R)
    {
        rt = L + R;
        //up(rt);
        return;
    }
    pushdown(L), pushdown(R);
    if (Tree[L].fix < Tree[R].fix)
        rt = L, merge(Tree[rt].ch[1], Tree[rt].ch[1], R);
    else
        rt = R, merge(Tree[rt].ch[0], L, Tree[rt].ch[0]);
    up(rt);
}

Rootpair split(int rt, int kth)
{
    //printf("split rt=%d kth=%d\n", rt, kth);
    pushdown(rt);
    if (!kth)
    {
        up(rt);
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

void insert(int pos, int val)
{
    pos--;
    int rt = newnode(val);
    Rootpair tmp = split(Root, pos);
    merge(Root, tmp.first, rt);
    merge(Root, Root, tmp.second);
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

void make_same(int l, int r, int d)
{
    Rootpair tmp1 = split(Root, l - 1);
    Rootpair tmp2 = split(tmp1.second, r - l + 1);
    Tree[tmp2.first].makesame = d;
    Tree[tmp2.first].val = d;
    Tree[tmp2.first].sum = Tree[tmp2.first].size * d;
    int rt;
    merge(rt, tmp1.first, tmp2.first);
    merge(Root, rt, tmp2.second);
}

void del(int pos)
{
    Rootpair tmp1 = split(Root, pos);
    Rootpair tmp2 = split(tmp1.first, pos - 1);
    merge(Root, tmp2.first, tmp1.second);
}

int getsum(int l, int r)
{
    Rootpair tmp1 = split(Root, l - 1);
    Rootpair tmp2 = split(tmp1.second, r - l + 1);
    //printf("%d\n", tmp2.first);
    int res = Tree[tmp2.first].sum;
    int rt;
    merge(rt, tmp1.first, tmp2.first);
    merge(Root, rt, tmp2.second);
    return res;
}

void PUSHDOWNLAZY(int rt)
{
    if (rt == 0)
        return;
    pushdown(rt);
    PUSHDOWNLAZY(Tree[rt].ch[0]);
    PUSHDOWNLAZY(Tree[rt].ch[1]);
    up(rt);
}

void debug(int rt)
{
    if (rt == 0)
        return;
    debug(Tree[rt].ch[0]);
    printf("%d ", Tree[rt].val);
    debug(Tree[rt].ch[1]);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &x);
        insert(i, x);
    }
    PUSHDOWNLAZY(Root);
    char CASES[10];
    int x, y, d;
    for (int i = 1; i <= m; i++)
    {
        scanf("%s", CASES);
        if (CASES[0] == 'R' && CASES[3] == 'E')
        {
            scanf("%d%d", &x, &y);
            reverse(x, x + y - 1);
        }
        else if (CASES[0] == 'I')
        {
            scanf("%d%d", &x, &y);
            int val;
            for (int i = 1; i <= y; i++)
            {
                scanf("%d", &val);
                insert(x + i, val);
            }
        }
        else if (CASES[0] == 'D')
        {
            scanf("%d%d", &x, &y);
            for (int i = 1; i <= y; i++)
                del(x);
        }
        else if (CASES[0] == 'G')
        {
            scanf("%d%d", &x, &y);
            printf("%d\n", getsum(x, x + y - 1));
        }
        else if (CASES[4] == '-')
        {
            scanf("%d%d%d", &x, &y, &d);
            make_same(x, x + y - 1, d);
        }
        /*PUSHDOWNLAZY(Root);
        printf("-----debug----\n");
        debug(Root);
        printf("\n");
        printf("-----debug end-----\n");*/
    }
    return 0;
}