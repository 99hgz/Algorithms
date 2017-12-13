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
    int val, fix, size, rev, lazy, MIN, ch[2];
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
    Tree[tot] = (TREENODE){x, rand(), 1, 0, 0, x};
    Tree[tot].ch[0] = Tree[tot].ch[1] = 0;
    return tot;
}

void up(int rt)
{
    if (rt == 0)
        return;
    Tree[rt].size = Tree[Tree[rt].ch[0]].size + Tree[Tree[rt].ch[1]].size + 1;
    Tree[rt].MIN = Tree[rt].val;
    if (Tree[rt].ch[0])
        Tree[rt].MIN = min(Tree[Tree[rt].ch[0]].MIN, Tree[rt].MIN);
    if (Tree[rt].ch[1])
        Tree[rt].MIN = min(Tree[Tree[rt].ch[1]].MIN, Tree[rt].MIN);
}

void pushdown(int rt)
{
    if (Tree[rt].rev)
    {
        doreverse(Tree[rt].ch[0]);
        doreverse(Tree[rt].ch[1]);
        Tree[rt].rev = 0;
    }
    if (Tree[rt].lazy)
    {
        if (Tree[rt].ch[0])
        {
            Tree[Tree[rt].ch[0]].lazy += Tree[rt].lazy;
            Tree[Tree[rt].ch[0]].val += Tree[rt].lazy;
            Tree[Tree[rt].ch[0]].MIN += Tree[rt].lazy;
        }
        if (Tree[rt].ch[1])
        {
            Tree[Tree[rt].ch[1]].lazy += Tree[rt].lazy;
            Tree[Tree[rt].ch[1]].val += Tree[rt].lazy;
            Tree[Tree[rt].ch[1]].MIN += Tree[rt].lazy;
        }
        Tree[rt].lazy = 0;
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

void add(int l, int r, int val)
{
    Rootpair tmp1 = split(Root, l - 1);
    Rootpair tmp2 = split(tmp1.second, r - l + 1);
    Tree[tmp2.first].lazy += val;
    Tree[tmp2.first].MIN += val;
    Tree[tmp2.first].val += val;
    merge(Root, tmp1.first, tmp2.first);
    merge(Root, Root, tmp2.second);
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

void revolve(int l, int r, int T)
{
    Rootpair tmp1 = split(Root, l - 1);
    Rootpair tmp2 = split(tmp1.second, r - l + 1);
    T = T % (r - l + 1);
    Rootpair tmp3 = split(tmp2.first, r - l + 1 - T);
    int rt;
    merge(rt, tmp3.second, tmp3.first);
    merge(rt, tmp1.first, rt);
    merge(Root, rt, tmp2.second);
}

void del(int pos)
{
    Rootpair tmp1 = split(Root, pos);
    Rootpair tmp2 = split(tmp1.first, pos - 1);
    merge(Root, tmp2.first, tmp1.second);
}

int getmin(int l, int r)
{
    Rootpair tmp1 = split(Root, l - 1);
    Rootpair tmp2 = split(tmp1.second, r - l + 1);
    //printf("%d\n", tmp2.first);
    int res = Tree[tmp2.first].MIN;
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
    /*freopen("z:/supermemo0.in", "r", stdin);
    freopen("z:/supermemo0.ans", "w", stdout);*/

    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &x);
        //printf("inserting... %d\n", i);
        insert(i, x);
    }
    //PUSHDOWNLAZY(Root);
    scanf("%d", &m);
    char CASES[10];
    int x, y, d;
    for (int i = 1; i <= m; i++)
    {
        //printf("doing %d\n", i);
        scanf("%s", CASES);
        if (CASES[0] == 'A')
        {
            scanf("%d%d%d", &x, &y, &d);
            add(x, y, d);
        }
        else if (CASES[0] == 'R' && CASES[3] == 'E')
        {
            scanf("%d%d", &x, &y);
            reverse(x, y);
        }
        else if (CASES[0] == 'R' && CASES[3] == 'O')
        {
            scanf("%d%d%d", &x, &y, &d);
            revolve(x, y, d);
        }
        else if (CASES[0] == 'I')
        {
            scanf("%d%d", &x, &y);
            insert(x + 1, y);
        }
        else if (CASES[0] == 'D')
        {
            scanf("%d", &x);
            del(x);
        }
        else
        {
            scanf("%d%d", &x, &y);
            printf("%d\n", getmin(x, y));
        }
        //PUSHDOWNLAZY(Root);
        /*printf("-----debug-----\n");
        debug(Root);
        printf("\n");
        printf("-----debug-----end\n");*/
    }
    //system("pause");
    return 0;
}