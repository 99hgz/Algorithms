#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>
#include <set>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef pair<int, int> pr;
int n, q, type, c[100010], u, v, ts, in[100010], out[100010];
vector<int> vec[100010], cvec[100010];
vector<int> son[100010];
set<pr> st[100010];
int deep[100010], ST[100010][20];

void addedge(int u, int v)
{
    vec[u].push_back(v);
}

void dfs(int rt, int fa, int depth)
{
    ST[rt][0] = fa;
    deep[rt] = depth;
    in[rt] = ++ts;
    for (int i = 0; i < vec[rt].size(); i++)
    {
        int v = vec[rt][i];
        if (v != fa)
        {
            dfs(v, rt, depth + 1);
            son[rt].push_back(v);
        }
    }
    out[rt] = ts;
}

/****************LCA**************/
void init_st()
{
    int deep = floor(log(n) / log(2));
    for (int j = 1; j <= deep; j++)
        for (int i = 1; i <= n; i++)
            if (ST[i][j - 1] != -1)
                ST[i][j] = ST[ST[i][j - 1]][j - 1];
}

int lca(int a, int b)
{
    int ua = a, ub = b;
    if (deep[a] < deep[b])
        swap(a, b);
    int depth = floor(log(deep[a] - 1) / log(2));
    for (int i = depth; i >= 0; i--)
        if (deep[a] - (1 << i) >= deep[b])
            a = ST[a][i];
    if (a == b)
        return a;
    for (int i = depth; i >= 0; i--)
        if ((ST[a][i] != -1) && (ST[a][i] != ST[b][i]))
        {
            a = ST[a][i];
            b = ST[b][i];
        }
    return ST[a][0];
}
/**********************************/

/******相同颜色dfs序排序******/
bool cmp(int a, int b)
{
    return in[a] < in[b];
}

int tot, Root[20010 * 4];
struct TREE
{
    int num, lson, rson;
} Tree[200010 * 100];
/******树套树******/
void insert_in(int &rt, int l, int r, int x, int base)
{
    if (rt == 0)
        rt = ++tot;
    Tree[rt].num += base;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (x <= mid)
        insert_in(Tree[rt].lson, l, mid, x, base);
    else
        insert_in(Tree[rt].rson, mid + 1, r, x, base);
}

int query_in(int rt, int l, int r, int L, int R)
{
    if (L > R)
        return 0;
    if (rt == 0)
        return 0;
    if (L <= l && r <= R)
        return Tree[rt].num;
    if (r < L || l > R)
        return 0;
    int mid = (l + r) >> 1;
    return query_in(Tree[rt].lson, l, mid, L, R) + query_in(Tree[rt].rson, mid + 1, r, L, R);
}

void insert_out(int rt, int l, int r, int x, int val, int base)
{
    insert_in(Root[rt], 1, n, val, base);
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (x <= mid)
        insert_out(rt * 2, l, mid, x, val, base);
    else
        insert_out(rt * 2 + 1, mid + 1, r, x, val, base);
}

int query_out(int rt, int l, int r, int L, int R, int inl, int inr)
{
    if (L > R)
        return 0;
    if (L <= l && r <= R)
        return query_in(Root[rt], 1, n, inl, inr);
    if (r < L || l > R)
        return 0;
    int mid = (l + r) >> 1;
    return query_out(rt * 2, l, mid, L, R, inl, inr) + query_out(rt * 2 + 1, mid + 1, r, L, R, inl, inr);
}

void add(int st, int c, int base)
{
    insert_out(1, 1, n, st, c, base);
}

void init()
{
    for (int i = 1; i <= n; i++)
    {
        sort(cvec[i].begin(), cvec[i].end(), cmp);
        for (int j = 0; j < cvec[i].size(); j++)
        {
            if (j)
                add(in[lca(cvec[i][j], cvec[i][j - 1])], i, -1);
            add(in[cvec[i][j]], i, 1);
            st[i].insert(make_pair(in[cvec[i][j]], cvec[i][j]));
        }
    }
}

void work()
{
    int cases, u, l, r, color;
    int lastans = 0;
    for (int i = 1; i <= q; i++)
    {
        scanf("%d", &cases);
        if (cases == 1)
        {
            scanf("%d%d%d", &u, &l, &r);
            if (type)
                u ^= lastans, l ^= lastans, r ^= lastans;
            lastans = query_out(1, 1, n, in[u], out[u], l, r);
            printf("%d\n", lastans);
        }
        else
        {
            scanf("%d%d", &u, &color);
            if (type)
                u ^= lastans, color ^= lastans;
            set<pr>::iterator it = st[c[u]].lower_bound(make_pair(in[u], u));
            if (it != st[c[u]].begin())
            {
                set<pr>::iterator front = it;
                front--;
                add(in[lca((*front).second, u)], c[u], 1);
            }
            set<pr>::iterator it2 = it;
            it2++;
            if (it2 != st[c[u]].end())
                add(in[lca(u, (*it2).second)], c[u], 1);

            if ((it != st[c[u]].begin()) && (it2 != st[c[u]].end()))
            {
                set<pr>::iterator front = it;
                front--;
                add(in[lca((*front).second, (*it2).second)], c[u], -1);
            }
            //printf("line 185\n");
            add(in[u], c[u], -1);
            st[c[u]].erase(it);

            c[u] = color;

            st[c[u]].insert(make_pair(in[u], u));
            it = st[c[u]].lower_bound(make_pair(in[u], u));
            if (it != st[c[u]].begin())
            {
                set<pr>::iterator front = it;
                front--;
                add(in[lca((*front).second, u)], c[u], -1);
            }
            it2 = it;
            it2++;
            if (it2 != st[c[u]].end())
                add(in[lca(u, (*it2).second)], c[u], -1);

            if ((it != st[c[u]].begin()) && (it2 != st[c[u]].end()))
            {
                set<pr>::iterator front = it;
                front--;
                add(in[lca((*front).second, (*it2).second)], c[u], 1);
            }

            add(in[u], c[u], 1);
        }
    }
}
int main()
{
    //freopen("x:/xmastree2.in", "r", stdin);
    //freopen("x:/xmastree2.out", "w", stdout);
    scanf("%d%d%d", &n, &q, &type);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &c[i]);
        cvec[c[i]].push_back(i);
    }
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }
    dfs(1, 1, 1);
    init_st();
    init();
    work();
    //printf("%d\n", tot);
    //system("pause");
}
