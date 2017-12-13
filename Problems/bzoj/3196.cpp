#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

typedef pair<int, int> Rootpair;
#define mp make_pair
int tot, opt, x, Root[50010 * 4], n, a[100010], m;
struct TREENODE
{
    int val, fix, size, ch[2];
} Tree[5000000];

int newnode(int x)
{
    tot++;
    Tree[tot] = (TREENODE){x, rand(), 1};
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
        rt = L, merge(Tree[rt].ch[1], Tree[rt].ch[1], R);
    else
        rt = R, merge(Tree[rt].ch[0], L, Tree[rt].ch[0]);
    up(rt);
}

Rootpair split(int rt, int kth)
{
    if (!kth)
        return mp(0, rt);
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

int getrank(int rt, int val)
{
    int res = 0, tmp = 0x7f7f7f7f;
    while (rt)
    {
        if (val == Tree[rt].val)
            tmp = min(tmp, res + Tree[Tree[rt].ch[0]].size + 1);
        if (val > Tree[rt].val)
            res += Tree[Tree[rt].ch[0]].size + 1, rt = Tree[rt].ch[1];
        else
            rt = Tree[rt].ch[0];
    }
    return tmp == 0x7f7f7f7f ? res : tmp;
}

int findkth(int rt, int val)
{
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

int pre(int rt, int val)
{
    int res = 0x3f3f3f3f;
    while (rt)
    {
        if (Tree[rt].val > val)
            res = min(res, Tree[rt].val), rt = Tree[rt].ch[0];
        else
            rt = Tree[rt].ch[1];
    }
    return res;
}

int suc(int rt, int val)
{
    int res = -0x3f3f3f3f;
    while (rt)
    {
        if (Tree[rt].val < val)
            res = max(res, Tree[rt].val), rt = Tree[rt].ch[1];
        else
            rt = Tree[rt].ch[0];
    }
    return res;
}

void insert(int &Rt, int val)
{
    int rt = newnode(val);
    int Rank = getrank(Rt, val);
    Rootpair tmp = split(Rt, Rank);
    merge(Rt, tmp.first, rt);
    merge(Rt, Rt, tmp.second);
}

void del(int &Rt, int val)
{
    int Rank = getrank(Rt, val);
    Rootpair tmp1 = split(Rt, Rank);
    Rootpair tmp2 = split(tmp1.first, Rank - 1);
    merge(Rt, tmp2.first, tmp1.second);
}

void insert_out(int rt, int l, int r, int x, int val)
{
    insert(Root[rt], val);
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (x <= mid)
        insert_out(rt * 2, l, mid, x, val);
    else
        insert_out(rt * 2 + 1, mid + 1, r, x, val);
}

int rank_out(int rt, int l, int r, int L, int R, int val)
{
    if (L <= l && r <= R)
    {
        int tmp = getrank(Root[rt], val - 1);
        //printf("rank_out gx l=%d r=%d val=%d res=%d\n", l, r, val, tmp);
        return tmp;
    }
    if (l > R || r < L)
        return 0;
    int mid = (l + r) >> 1;
    return rank_out(rt * 2, l, mid, L, R, val) + rank_out(rt * 2 + 1, mid + 1, r, L, R, val);
}

int kth_out(int rt, int l, int r, int L, int R, int val)
{
    int l1 = 1, r1 = n, ans = 0;
    while (l1 <= r1)
    {
        int mid = (l1 + r1) >> 1;
        int V = Tree[findkth(Root[rt], mid)].val;
        int tmp = rank_out(rt, l, r, L, R, V);
        //printf("rank_out(%d,%d,%d,%d,%d,%d)=%d\n", rt, l, r, L, R, V, tmp);
        if (tmp + 1 <= val)
            l1 = mid + 1, ans = V;
        else
            r1 = mid - 1;
    }
    return ans;
}

void modify_out(int rt, int l, int r, int x, int f, int val)
{
    del(Root[rt], f);
    insert(Root[rt], val);
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (x <= mid)
        modify_out(rt * 2, l, mid, x, f, val);
    else
        modify_out(rt * 2 + 1, mid + 1, r, x, f, val);
}

int suc_out(int rt, int l, int r, int L, int R, int val)
{
    if (L <= l && r <= R)
        return suc(Root[rt], val);
    if (l > R || r < L)
        return 0;
    int mid = (l + r) >> 1;
    return max(suc_out(rt * 2, l, mid, L, R, val), suc_out(rt * 2 + 1, mid + 1, r, L, R, val));
}

int pre_out(int rt, int l, int r, int L, int R, int val)
{
    if (L <= l && r <= R)
        return pre(Root[rt], val);
    if (l > R || r < L)
        return 0x3f3f3f3f;
    int mid = (l + r) >> 1;
    return min(pre_out(rt * 2, l, mid, L, R, val), pre_out(rt * 2 + 1, mid + 1, r, L, R, val));
}

void dfsintreap(int rt)
{
    if (rt == 0)
        return;
    dfsintreap(Tree[rt].ch[0]);
    printf("%d ", Tree[rt].val);
    dfsintreap(Tree[rt].ch[1]);
}

void debug(int rt, int l, int r)
{
    int mid = (l + r) >> 1;
    printf("Treep Seg_Root=%d Treap_Root=%d l=%d r=%d\n", rt, Root[rt], l, r);
    dfsintreap(Root[rt]);
    printf("\n");
    printf("--------------------\n");
    if (l == r)
        return;
    debug(rt * 2, l, mid);
    debug(rt * 2 + 1, mid + 1, r);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++)
    {
        insert_out(1, 1, n, i, a[i]);
        insert(Root[0], a[i]);
    }
    for (int i = 1; i <= m; i++)
    {
        int opt, l, r, k;
        scanf("%d", &opt);
        if (opt == 1)
        {
            scanf("%d%d%d", &l, &r, &k);
            printf("%d\n", rank_out(1, 1, n, l, r, k) + 1);
        }
        else if (opt == 2)
        {
            scanf("%d%d%d", &l, &r, &k);
            printf("%d\n", kth_out(1, 1, n, l, r, k));
        }
        else if (opt == 3)
        {
            scanf("%d%d", &l, &k);
            modify_out(1, 1, n, l, a[l], k);
            del(Root[0], a[l]);
            insert(Root[0], k);
            a[l] = k;
        }
        else if (opt == 4)
        {
            scanf("%d%d%d", &l, &r, &k);
            printf("%d\n", suc_out(1, 1, n, l, r, k));
        }
        else
        {
            scanf("%d%d%d", &l, &r, &k);
            printf("%d\n", pre_out(1, 1, n, l, r, k));
        }
        //debug(1, 1, n);
    }
    //system("pause");
    return 0;
}