#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

typedef pair<int, int> Rootpair;
#define mp make_pair
int tot, opt, x, Root, n, m;
ll base[100010];
ll MOD = 233333333;
int len;
struct TREENODE
{
    int val, fix, size;
    ll Hash;
    int ch[2];
} Tree[250010];

inline int newnode(int x)
{
    tot++;
    Tree[tot] = (TREENODE){x, rand(), 1, x};
    Tree[tot].ch[0] = Tree[tot].ch[1] = 0;
    return tot;
}

inline void up(int rt)
{
    if (rt == 0)
        return;
    Tree[rt].size = Tree[Tree[rt].ch[0]].size + Tree[Tree[rt].ch[1]].size + 1;
    Tree[rt].Hash = ((((Tree[Tree[rt].ch[0]].Hash * base[Tree[Tree[rt].ch[1]].size + 1]) +
                       (Tree[rt].val * base[Tree[Tree[rt].ch[1]].size]))) +
                     Tree[Tree[rt].ch[1]].Hash);
}

inline void merge(int &rt, int L, int R)
{
    if (!L || !R)
    {
        rt = L + R;
        return;
    }
    if (Tree[L].fix < Tree[R].fix)
        rt = L, merge(Tree[rt].ch[1], Tree[rt].ch[1], R);
    else
        rt = R, merge(Tree[rt].ch[0], L, Tree[rt].ch[0]);
    up(rt);
}

inline Rootpair split(int rt, int kth)
{
    //printf("split rt=%d kth=%d\n", rt, kth);
    if (kth <= 0)
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

inline void insert(int pos, int val)
{
    pos--;
    int rt = newnode(val);
    Rootpair tmp = split(Root, pos);
    merge(Root, tmp.first, rt);
    merge(Root, Root, tmp.second);
}

inline void del(int pos)
{
    Rootpair tmp1 = split(Root, pos);
    Rootpair tmp2 = split(tmp1.first, pos - 1);
    merge(Root, tmp2.first, tmp1.second);
}

inline int getHash(int l, int r)
{
    if (l < r)
        return 0;
    Rootpair tmp1 = split(Root, l - 1);
    Rootpair tmp2 = split(tmp1.second, r - l + 1);
    int res = Tree[tmp2.first].Hash;
    //printf("point=%lld\n", tmp2.first);
    int rt;
    merge(rt, tmp1.first, tmp2.first);
    merge(Root, rt, tmp2.second);
    return res;
}

inline int query(int l1, int l2)
{
    int l = 0, r = min(len - l1 + 1, len - l2 + 1), ans = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (getHash(l1, l1 + mid - 1) == getHash(l2, l2 + mid - 1))
            ans = mid, l = mid + 1;
        else
            r = mid - 1;
    }
    return ans;
}

inline void PUSHDOWNLAZY(int rt)
{
    if (rt == 0)
        return;
    //pushdown(rt);
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

char st[100010];
int main()
{
    scanf("%s", st + 1);
    len = strlen(st + 1);
    base[0] = 1;
    for (int i = 1; i <= 100000; i++)
        base[i] = base[i - 1] * 29;
    for (int i = 1; i <= len; i++)
        insert(i, st[i] - 'a' + 1);
    PUSHDOWNLAZY(Root);
    scanf("%d", &m);
    //printf("Hash=%lld\n", getHash(10, 10));
    char CASES[10];
    char c[10];
    int x, y, d;
    for (int i = 1; i <= m; i++)
    {
        scanf("%s", CASES);
        if (CASES[0] == 'I')
        {
            scanf("%d%s", &x, c);
            insert(x + 1, c[0] - 'a' + 1);
            len++;
        }
        else if (CASES[0] == 'R')
        {
            scanf("%d%s", &x, c);
            del(x);
            insert(x, c[0] - 'a' + 1);
        }
        else
        {
            scanf("%d%d", &x, &y);
            printf("%d\n", query(x, y));
        }
    }
    //system("pause");
    return 0;
}