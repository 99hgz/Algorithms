#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

typedef pair<int, int> Rootpair;
#define mp make_pair
int tot, opt, x, Root, n, pos[200010], m, id[200010], y;

int cnt, Head[200010], Next[200010], To[200010];
void addedge(int u, int v)
{
    cnt++;
    Next[cnt] = Head[u];
    Head[u] = cnt;
    To[cnt] = v;
}

int in[200010], out[200010], timestamp, val[200010], init[200010], fa, solved;
char cases[110];
struct TREENODE
{
    ll sum;
    int val, fix, size, fa, lazy, negative, zs, ch[2];
} Tree[200010];
int isin[200010];
inline int newnode(int x)
{
    tot++;
    Tree[tot] = (TREENODE){val[x], val[x], rand(), 1, 0, 0, isin[x] ? 1 : -1, isin[x]};
    Tree[tot].ch[0] = Tree[tot].ch[1] = 0;
    return tot;
}

inline void doplus(int rt, int lazy)
{
    Tree[rt].lazy += lazy;
    Tree[rt].val += lazy * Tree[rt].negative;
    Tree[rt].sum += (ll)lazy * Tree[rt].zs - (ll)lazy * (Tree[rt].size - Tree[rt].zs);
}

inline void pushdown(int rt)
{
    if (Tree[rt].lazy != 0)
    {
        if (Tree[rt].ch[0])
            doplus(Tree[rt].ch[0], Tree[rt].lazy);
        if (Tree[rt].ch[1])
            doplus(Tree[rt].ch[1], Tree[rt].lazy);
        Tree[rt].lazy = 0;
    }
}

inline void up(int rt)
{
    Tree[rt].size = Tree[Tree[rt].ch[0]].size + Tree[Tree[rt].ch[1]].size + 1;
    Tree[rt].sum = Tree[Tree[rt].ch[0]].sum + Tree[Tree[rt].ch[1]].sum + (ll)Tree[rt].val;
    Tree[rt].zs = Tree[Tree[rt].ch[0]].zs + Tree[Tree[rt].ch[1]].zs + (Tree[rt].negative == 1);
}

void merge(int &rt, int L, int R)
{
    if (!L || !R)
    {
        rt = L + R;
        return;
    }
    pushdown(L), pushdown(R);
    if (Tree[L].fix < Tree[R].fix)
        rt = L, Tree[Tree[rt].ch[1]].fa = 0, Tree[R].fa = 0, merge(Tree[rt].ch[1], Tree[rt].ch[1], R), Tree[Tree[rt].ch[1]].fa = rt;
    else
        rt = R, Tree[L].fa = 0, Tree[Tree[rt].ch[0]].fa = 0, merge(Tree[rt].ch[0], L, Tree[rt].ch[0]), Tree[Tree[rt].ch[0]].fa = rt;
    up(rt);
}

Rootpair split(int rt, int kth)
{
    pushdown(rt);
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

int dfsinsert(int tot)
{
    if (tot == 0)
        return 0;
    if (tot == 1)
    {
        solved++;
        return newnode(solved);
    }
    int m = tot >> 1;
    int newrt1 = dfsinsert(m), newrt2 = dfsinsert(tot - m);
    merge(newrt1, newrt1, newrt2);
    return newrt1;
}

void debug(int rt)
{
    if (rt == 0)
        return;
    debug(Tree[rt].ch[0]);
    printf("%d ", Tree[rt].val);
    debug(Tree[rt].ch[1]);
}

void dfs(int x)
{
    in[x] = ++timestamp;
    val[timestamp] = init[x];
    isin[timestamp] = 1;
    for (int it = Head[x]; it; it = Next[it])
        dfs(To[it]);
    out[x] = ++timestamp;
    val[timestamp] = -init[x];
}

void changefather(int u, int v)
{
    int uinrank = getrank(in[u]);
    int uoutrank = getrank(out[u]);
    Rootpair tmp1 = split(Root, uoutrank);
    Rootpair treeu = split(tmp1.first, uinrank - 1);
    merge(Root, treeu.first, tmp1.second);
    int voutrank = getrank(out[v]);
    //printf("%d %d\n", voutrank, out[v]);
    Rootpair treev = split(Root, voutrank - 1);
    merge(Root, treev.first, treeu.second);
    merge(Root, Root, treev.second);
}

void addson(int l, int r, int val)
{
    l = getrank(l), r = getrank(r);
    //printf("addson:%d %d\n", l, r);
    Rootpair tmp1 = split(Root, l - 1);
    Rootpair tmp2 = split(tmp1.second, r - l + 1);
    doplus(tmp2.first, val);
    //printf("addson:%d\n", Tree[tmp2.first].sum);
    int rt;
    merge(rt, tmp1.first, tmp2.first);
    merge(Root, rt, tmp2.second);
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

ll query(int l, int r)
{
    l = getrank(l), r = getrank(r);
    //printf("query:%d %d\n", l, r);
    Rootpair tmp1 = split(Root, l - 1);
    Rootpair tmp2 = split(tmp1.second, r - l + 1);
    ll res = Tree[tmp2.first].sum;
    int rt;
    merge(rt, tmp1.first, tmp2.first);
    merge(Root, rt, tmp2.second);
    return res;
}

int main()
{
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
    {
        int fa;
        scanf("%d", &fa);
        addedge(fa, i);
    }
    for (int i = 1; i <= n; i++)
        scanf("%d", &init[i]);

    dfs(1);
    Root = dfsinsert(2 * n);
    scanf("%d", &m);
    char cases[10];
    /*debug(Root);
    printf("\n");*/
    for (int i = 1; i <= m; i++)
    {
        scanf("%s", cases);
        if (cases[0] == 'Q')
        {
            scanf("%d", &x);
            printf("%lld\n", query(1, in[x]));
        }
        else if (cases[0] == 'F')
        {
            scanf("%d%d", &x, &y);
            addson(in[x], out[x], y);
        }
        else if (cases[0] == 'C')
        {
            scanf("%d%d", &x, &y);
            changefather(x, y);
        }
        /*debug(Root);
        printf("\n");*/
    }
    //  system("pause");
    return 0;
}