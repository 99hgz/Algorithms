#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <set>
#include <vector>
using namespace std;
typedef long long ll;
int bh, in[100010], depth, deep[100010], sttable[100010][20], out[100010], n, m, c[100010], fa[100010], timesta;
set<int> st[100010];
vector<int> depp[100010];
int redfn[100010];
vector<int> vec[100010];
int root[100010];
struct NODe
{
    int lson, rson, v;
} tree[2000010];

int build(int l, int r)
{
    bh++;
    int tbh = bh;
    if (l == r)
    {
        tree[bh].v = 0;
        return bh;
    }
    tree[tbh].lson = build(l, (l + r) >> 1);
    tree[tbh].rson = build(((l + r) >> 1) + 1, r);
    return tbh;
}

int modify(int old, int l, int r, int i, int val)
{
    //printf("modify:%d %d %d %d %d\n", old, l, r, i, val);
    if (l == r)
    {
        bh++;
        tree[bh].v = tree[old].v + val;
        return bh;
    }
    int tbh;
    int mid = (l + r) >> 1;
    if (i > mid)
    {
        bh++;
        tbh = bh;
        tree[bh].v = tree[old].v + val;
        tree[bh].lson = tree[old].lson;
        tree[tbh].rson = modify(tree[old].rson, mid + 1, r, i, val);
    }
    else
    {
        bh++;
        tbh = bh;
        tree[bh].v = tree[old].v + val;
        tree[bh].rson = tree[old].rson;
        tree[tbh].lson = modify(tree[old].lson, l, mid, i, val);
    }
    return tbh;
}

int query(int rt, int l, int r, int L, int R)
{
    //printf("query:%d %d %d %d %d\n", rt, l, r, L, R);
    if (L <= l && r <= R)
        return tree[rt].v;
    if (L > r || R < l)
        return 0;
    int mid = (l + r) >> 1;
    return query(tree[rt].lson, l, mid, L, R) + query(tree[rt].rson, mid + 1, r, L, R);
}

void dfs(int x, int dep)
{
    in[x] = ++timesta;
    redfn[in[x]] = x;
    depth = max(dep, depth);
    deep[x] = dep;
    depp[dep].push_back(x);
    for (int i = 0; i < vec[x].size(); i++)
        dfs(vec[x][i], dep + 1);
    out[x] = timesta;
}

void init_st()
{
    int deep = floor(log(n) / log(2));
    for (int j = 1; j <= deep; j++)
        for (int i = 1; i <= n; i++)
            if (sttable[i][j - 1] != -1)
                sttable[i][j] = sttable[sttable[i][j - 1]][j - 1];
}

int lca(int a, int b)
{
    if (deep[a] < deep[b])
        swap(a, b);
    int depth = floor(log(deep[a] - 1) / log(2));
    for (int i = depth; i >= 0; i--)
        if (deep[a] - (1 << i) >= deep[b])
            a = sttable[a][i];

    if (a == b)
    {
        //printf("lca1=%d\n", a);
        return a;
    }
    for (int i = depth; i >= 0; i--)
        if ((sttable[a][i] != -1) && (sttable[a][i] != sttable[b][i]))
        {
            a = sttable[a][i];
            b = sttable[b][i];
        }

    //printf("lca2=%d\n", sttable[b][0]);
    return sttable[b][0];
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        memset(sttable, -1, sizeof sttable);
        bh = 0;
        depth = 0;
        timesta = 0;
        for (int i = 1; i <= n; i++)
        {
            st[i].clear();
            depp[i].clear();
            vec[i].clear();
        }
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            scanf("%d", &c[i]);
        for (int i = 2; i <= n; i++)
        {
            scanf("%d", &fa[i]);
            sttable[i][0] = fa[i];
            vec[fa[i]].push_back(i);
        }
        sttable[1][0] = 1;
        dfs(1, 1);
        root[0] = build(1, timesta);
        init_st();
        for (int i = 1; i <= depth; i++)
        {
            root[i] = root[i - 1];
            for (int j = 0; j < depp[i].size(); j++)
            {
                int point = depp[i][j];
                int last = 0;
                st[c[point]].insert(in[point]);
                set<int>::iterator it = st[c[point]].lower_bound(in[point]);
                set<int>::iterator lit, rit;
                lit = rit = it;
                rit++;
                if (it != st[c[point]].begin() && rit != st[c[point]].end())
                {
                    lit--;
                    root[i] = modify(root[i], 1, timesta, lca(redfn[*lit], redfn[*rit]), 1);
                    root[i] = modify(root[i], 1, timesta, lca(point, redfn[*lit]), -1);
                    root[i] = modify(root[i], 1, timesta, lca(point, redfn[*rit]), -1);
                }
                else if (it != st[c[point]].begin())
                {
                    lit--;
                    root[i] = modify(root[i], 1, timesta, lca(point, redfn[*lit]), -1);
                }
                else if (rit != st[c[point]].end())
                {
                    root[i] = modify(root[i], 1, timesta, lca(point, redfn[*rit]), -1);
                }
                root[i] = modify(root[i], 1, timesta, in[point], 1);
            }
        }
        //printf("debug:%d\n", tree[tree[root[2]].lson].v);
        int lastans = 0;
        for (int i = 1; i <= m; i++)
        {
            int x, d;
            scanf("%d%d", &x, &d);
            x ^= lastans;
            d ^= lastans;
            //printf("true:%d %d\n", x, d);
            int right = min(depth, deep[x] + d);
            printf("%d\n", lastans = query(root[right], 1, timesta, in[x], out[x]));
        }
    }
    system("pause");
    return 0;
}