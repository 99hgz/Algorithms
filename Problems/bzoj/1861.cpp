#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

typedef pair<int, int> Rootpair;
#define mp make_pair
int tot, opt, x, Root, n, pos[100010], m, id[100010], y;
char cases[110];
struct TREENODE
{
    int val, fix, size, fa, ch[2];
} Tree[100010];

int newnode(int x)
{
    tot++;
    Tree[tot] = (TREENODE){x, rand(), 1, 0};
    Tree[tot].ch[0] = Tree[tot].ch[1] = 0;
    return tot;
}

void up(int rt)
{
    Tree[rt].size = Tree[Tree[rt].ch[0]].size + Tree[Tree[rt].ch[1]].size + 1;
}

void merge(int &rt, int L, int R)
{
    if (!L || !R)
    {
        rt = L + R;
        return;
    }
    if (Tree[L].fix < Tree[R].fix)
        rt = L, Tree[Tree[rt].ch[1]].fa = 0, Tree[R].fa = 0, merge(Tree[rt].ch[1], Tree[rt].ch[1], R), Tree[Tree[rt].ch[1]].fa = rt;
    else
        rt = R, Tree[L].fa = 0, Tree[Tree[rt].ch[0]].fa = 0, merge(Tree[rt].ch[0], L, Tree[rt].ch[0]), Tree[Tree[rt].ch[0]].fa = rt;
    up(rt);
}

Rootpair split(int rt, int kth)
{
    if (!kth)
        return mp(0, rt);
    int ls = Tree[rt].ch[0], rs = Tree[rt].ch[1];
    if (kth == Tree[ls].size)
    {
        Tree[Tree[rt].ch[0]].fa = 0;
        Tree[rt].ch[0] = 0;
        up(rt);
        return mp(ls, rt);
    }
    if (kth == Tree[ls].size + 1)
    {
        Tree[Tree[rt].ch[1]].fa = 0;
        Tree[rt].ch[1] = 0;
        up(rt);
        return mp(rt, rs);
    }
    if (kth < Tree[ls].size)
    {
        Rootpair tmp = split(ls, kth);
        Tree[Tree[rt].ch[0]].fa = 0;
        Tree[rt].ch[0] = tmp.second;
        Tree[Tree[rt].ch[0]].fa = rt;
        up(rt);
        return mp(tmp.first, rt);
    }
    Rootpair tmp = split(rs, kth - Tree[ls].size - 1);
    Tree[Tree[rt].ch[1]].fa = 0;
    Tree[rt].ch[1] = tmp.first;
    Tree[Tree[rt].ch[1]].fa = rt;
    up(rt);
    return mp(rt, tmp.second);
}

int getrank(int rt)
{
    int res = 1 + Tree[Tree[rt].ch[0]].size;
    while (rt)
    {
        if (rt == Tree[Tree[rt].fa].ch[1])
            res += Tree[Tree[Tree[rt].fa].ch[0]].size + 1;
        rt = Tree[rt].fa;
    }
    return res;
}

int findkth(int val)
{
    int rt = Root;
    while (1)
    {
        if (Tree[Tree[rt].ch[0]].size + 1 == val)
            return rt;
        if (Tree[Tree[rt].ch[0]].size > val - 1)
            rt = Tree[rt].ch[0];
        else
            val -= Tree[Tree[rt].ch[0]].size + 1, rt = Tree[rt].ch[1];
    }
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
    debug(Tree[rt].ch[0]);
    printf("%d ", Tree[rt].val);
    debug(Tree[rt].ch[1]);
}

void top(int x)
{
    int Rank = getrank(x);
    Rootpair tmp1 = split(Root, Rank);
    Rootpair tmp2 = split(tmp1.first, Rank - 1);
    merge(Root, tmp2.second, tmp2.first);
    merge(Root, Root, tmp1.second);
}

void bottom(int x)
{
    int Rank = getrank(x);
    Rootpair tmp1 = split(Root, Rank);
    Rootpair tmp2 = split(tmp1.first, Rank - 1);
    merge(Root, tmp2.first, tmp1.second);
    merge(Root, Root, tmp2.second);
}

void Insert(int x, int t)
{
    if (t == 0)
        return;
    int Rank = getrank(x);
    if (t == 1)
    {
        Rootpair tmp1 = split(Root, Rank + 1);
        Rootpair tmp2 = split(tmp1.first, Rank);
        Rootpair tmp3 = split(tmp2.first, Rank - 1);
        merge(Root, tmp3.first, tmp2.second);
        merge(Root, Root, tmp3.second);
        merge(Root, Root, tmp1.second);
    }
    else
    {
        Rootpair tmp1 = split(Root, Rank);
        Rootpair tmp2 = split(tmp1.first, Rank - 1);
        Rootpair tmp3 = split(tmp2.first, Rank - 2);
        merge(Root, tmp3.first, tmp2.second);
        merge(Root, Root, tmp3.second);
        merge(Root, Root, tmp1.second);
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &id[i]);
        pos[id[i]] = i;
        insert(id[i]);
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%s%d", cases, &x);
        if (cases[0] == 'Q')
            printf("%d\n", Tree[findkth(x)].val);
        else if (cases[0] == 'T')
            top(pos[x]);
        else if (cases[0] == 'I')
        {
            scanf("%d", &y);
            Insert(pos[x], y);
        }
        else if (cases[0] == 'A')
            printf("%d\n", getrank(pos[x]) - 1);
        else if (cases[0] == 'B')
            bottom(pos[x]);
        //debug(Root);
        //printf("\n");
    }
    //system("pause");
    return 0;
}