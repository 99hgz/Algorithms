#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;

typedef pair<int, int> Rootpair;
#define mp make_pair
int tot, opt, x, Root, n, m;
queue<int> Q;
struct TREENODE
{
    int val, fix, size, rev, makesame, sum, rmax, rsum, lsum, ch[2];
} Tree[1500010];

void doreverse(int rt)
{
    if (rt == 0)
        return;
    Tree[rt].rev ^= 1;
    swap(Tree[rt].ch[0], Tree[rt].ch[1]);
    swap(Tree[Tree[rt].ch[0]].rsum, Tree[Tree[rt].ch[0]].lsum);
    swap(Tree[Tree[rt].ch[1]].rsum, Tree[Tree[rt].ch[1]].lsum);
}

int newnode(int x)
{
    int newnodeid = 0;
    if (!Q.empty())
        newnodeid = Q.front(), Q.pop();
    else
        newnodeid = ++tot;
    Tree[newnodeid] = (TREENODE){x, rand(), 1, 0, -1001, x, x, x, x};
    Tree[newnodeid].ch[0] = Tree[newnodeid].ch[1] = 0;
    return newnodeid;
}

void up(int rt)
{
    if (rt == 0)
        return;
    int lson = Tree[rt].ch[0], rson = Tree[rt].ch[1];
    Tree[rt].size = Tree[lson].size + Tree[rson].size + 1;
    Tree[rt].sum = Tree[lson].sum + Tree[rson].sum + Tree[rt].val;
    Tree[rt].rmax = max(Tree[lson].rsum, 0) + Tree[rt].val + max(Tree[rson].lsum, 0);
    Tree[rt].rmax = max(Tree[rt].rmax, max(lson ? Tree[lson].rmax : -1001, rson ? Tree[rson].rmax : -1001));
    Tree[rt].lsum = max(lson ? Tree[lson].lsum : -1001, Tree[lson].sum + Tree[rt].val + max(Tree[rson].lsum, 0));
    Tree[rt].rsum = max(rson ? Tree[rson].rsum : -1001, Tree[rson].sum + Tree[rt].val + max(Tree[lson].rsum, 0));
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
            Tree[Tree[rt].ch[0]].lsum = Tree[Tree[rt].ch[0]].rsum = Tree[Tree[rt].ch[0]].rmax = max(Tree[Tree[rt].ch[0]].sum, Tree[Tree[rt].ch[0]].val);
        }
        if (Tree[rt].ch[1])
        {
            Tree[Tree[rt].ch[1]].val = Tree[rt].makesame;
            Tree[Tree[rt].ch[1]].makesame = Tree[rt].makesame;
            Tree[Tree[rt].ch[1]].sum = Tree[rt].makesame * Tree[Tree[rt].ch[1]].size;
            Tree[Tree[rt].ch[1]].lsum = Tree[Tree[rt].ch[1]].rsum = Tree[Tree[rt].ch[1]].rmax = max(Tree[Tree[rt].ch[1]].sum, Tree[Tree[rt].ch[1]].val);
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

void insert(int &Root, int pos, int val)
{
    pos--;
    int rt = newnode(val);
    Rootpair tmp = split(Root, pos);
    merge(Root, tmp.first, rt);
    merge(Root, Root, tmp.second);
}

int dfsinsert(int tot)
{
    if (tot == 0)
        return 0;
    if (tot == 1)
    {
        int d, newrt;
        scanf("%d", &d);
        return newnode(d);
    }
    int m = tot >> 1;
    int newrt1 = dfsinsert(m), newrt2 = dfsinsert(tot - m);

    merge(newrt1, newrt1, newrt2);
    return newrt1;
}

void insertxl(int pos, int tot)
{
    int rt = 0;
    rt = dfsinsert(tot);
    Rootpair tmp1 = split(Root, pos);

    merge(rt, tmp1.first, rt);
    merge(Root, rt, tmp1.second);
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
    Tree[tmp2.first].lsum = Tree[tmp2.first].rsum = Tree[tmp2.first].rmax = max(Tree[tmp2.first].sum, d);
    pushdown(tmp2.first);
    int rt;
    merge(rt, tmp1.first, tmp2.first);
    merge(Root, rt, tmp2.second);
}

void dfsdel(int rt)
{
    if (rt == 0)
        return;
    Q.push(rt);
    dfsdel(Tree[rt].ch[0]);
    dfsdel(Tree[rt].ch[1]);
}

void del(int l, int r)
{
    Rootpair tmp1 = split(Root, l - 1);
    Rootpair tmp2 = split(tmp1.second, r - l + 1);
    dfsdel(tmp2.first);
    merge(Root, tmp1.first, tmp2.second);
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
    printf("Tree[%d] l=%d r=%d val=%d makesame=%d rmax=%d lsum=%d rsum=%d\n", rt, Tree[rt].ch[0], Tree[rt].ch[1], Tree[rt].val, Tree[rt].makesame, Tree[rt].rmax, Tree[rt].lsum, Tree[rt].rsum);
    debug(Tree[rt].ch[1]);
}

void builddfsid(int rt)
{
    in[rt] = ++timestamp;
    data[timestamp] = val[rt];
    for (int i = 0; i < vec[rt].size(); i++)
        builddfsid(vec[rt][i]);
    out[rt] = ++timestamp;
    data[timestamp] = -val[rt];
    linki2o[in[rt]] = out[rt];
}

int main()
{
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
    {
        scanf("%d", &fa[i]);
        vec[fa[i]].push_back(i);
    }
    builddfsid(1);
    insertxl(0, n);
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
            insertxl(x, y);
        }
        else if (CASES[0] == 'D')
        {
            scanf("%d%d", &x, &y);
            del(x, x + y - 1);
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
        else if (CASES[2] == 'X')
        {
            if (Root == 0)
                printf("0\n");
            else
                printf("%d\n", Tree[Root].rmax);
        }
    }
    //system("pause");
    return 0;
}