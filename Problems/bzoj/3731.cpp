#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
typedef long long ll;
int n;
namespace IOStream
{
const int L = 1 << 15;
char buffer[L];
char *S, *T;
char Get_Char()
{
    if (S == T)
    {
        T = (S = buffer) + fread(buffer, 1, L, stdin);
        if (S == T)
            return EOF;
    }
    return *S++;
}
int Get_Int()
{
    int re = 0;
    char c;
    do
        c = Get_Char();
    while (c < '0' || c > '9');
    while (c >= '0' && c <= '9')
        re = (re << 1) + (re << 3) + (c - '0'), c = Get_Char();
    return re;
}
}
namespace CASE1
{
vector<int> vec[100010], bvec[100010], block[21000], blockid[100010], bbvec[100010];
int father[100010], belong[100010], blocksize, tot, lastans, val[100010], u, v, m, cases, x, Root[100010];
bool isroot[100010];
int lazy[100010];

void ori_addedge(int u, int v)
{
    vec[u].push_back(v);
    vec[v].push_back(u);
}

void push(int x, int val)
{
    block[x].insert(upper_bound(block[x].begin(), block[x].end(), val), val);
}

void addedge(int u, int v)
{
    bvec[u].push_back(v);
}

void init(int x, int fa)
{
    father[x] = fa;
    if (block[belong[fa]].size() < blocksize)
    {
        belong[x] = belong[fa];
        block[belong[x]].push_back(val[x]);
        blockid[belong[x]].push_back(x);
    }
    else
    {
        isroot[x] = true;
        belong[x] = ++tot;
        Root[tot] = x;
        block[tot].push_back(val[x]);
        blockid[tot].push_back(x);
    }
    if (belong[x] != belong[fa])
        addedge(belong[fa], belong[x]), bbvec[fa].push_back(belong[x]);
    for (int i = 0; i < vec[x].size(); i++)
    {
        int v = vec[x][i];
        if (v != fa)
            init(v, x);
    }
}

int dfs(int x, int val)
{
    lastans += block[x].end() - upper_bound(block[x].begin(), block[x].end(), val);
    int k = bvec[x].size();
    for (int i = 0; i < k; i++)
        dfs(bvec[x][i], val);
}

void dfs2(int x, int bl, int fa, int v1)
{
    if (belong[x] != bl)
        return;
    if (val[x] > v1)
    {
        lastans++;
    }
    int k = bbvec[x].size();
    for (int i = 0; i < k; i++)
        dfs(bbvec[x][i], v1);
    k = vec[x].size();
    for (int i = 0; i < k; i++)
    {
        int v = vec[x][i];
        if (v != fa)
            dfs2(v, bl, x, v1);
    }
}

int query(int u, int x)
{
    dfs2(u, belong[u], father[u], x);
}

void modify(int u, int x)
{
    int bl = belong[u];
    sort(block[bl].begin(), block[bl].end());
    block[bl].erase(lower_bound(block[bl].begin(), block[bl].end(), val[u]));
    val[u] = x;
    block[bl].push_back(x);
    sort(block[bl].begin(), block[bl].end());
}

void add(int id, int fa, int v)
{
    ori_addedge(id, fa);
    father[id] = fa;
    val[id] = v;
    int x = id;
    if (block[belong[fa]].size() < blocksize)
    {
        belong[x] = belong[fa];
        block[belong[x]].push_back(val[x]);
        blockid[belong[x]].push_back(x);
    }
    else
    {
        isroot[x] = true;
        belong[x] = ++tot;
        Root[tot] = x;
        block[tot].push_back(val[x]);
        blockid[tot].push_back(x);
    }
    if (belong[x] != belong[fa])
        addedge(belong[fa], belong[x]), bbvec[fa].push_back(belong[x]);
    int bl = belong[x];
    sort(block[bl].begin(), block[bl].end());
}

void block_dfs(int x, int bl, int fa, int fjx, bool th, int newbh)
{
    if (belong[x] != bl)
        return;
    if (x == fjx)
        th = true;
    if (th)
    {
        belong[x] = newbh;
        block[bl].erase(lower_bound(block[bl].begin(), block[bl].end(), val[x]));
        blockid[bl].erase(lower_bound(blockid[bl].begin(), blockid[bl].end(), x));
        block[newbh].push_back(val[x]);
        blockid[newbh].push_back(x);
        int k = bbvec[x].size();
        for (int i = 0; i < k; i++)
        {
            int it = bbvec[x][i];
            vector<int>::iterator it1 = lower_bound(bvec[bl].begin(), bvec[bl].end(), it);
            if (it1 != bvec[bl].end())
            {
                bvec[bl].erase(it1);
                bvec[newbh].push_back(it);
            }
        }
    }
    int k = vec[x].size();
    for (int i = 0; i < k; i++)
    {
        int v = vec[x][i];
        if (v != fa)
            block_dfs(v, bl, x, fjx, th, newbh);
    }
}

void split(int u)
{
    if (u == 1)
        return;
    int root = Root[belong[u]];
    if (isroot[u])
    {
        int fa = father[u];
        sort(bvec[belong[fa]].begin(), bvec[belong[fa]].end());
        vector<int>::iterator it = lower_bound(bvec[belong[fa]].begin(), bvec[belong[fa]].end(), belong[u]);
        if (it != bvec[belong[fa]].end() && (*it) == belong[u])
        {
            bvec[belong[fa]].erase(it);
            sort(bbvec[fa].begin(), bbvec[fa].end());
            bbvec[fa].erase(lower_bound(bbvec[fa].begin(), bbvec[fa].end(), belong[u]));
        }
    }
    else
    {
        int fa = father[u];
        isroot[u] = true;
        //block[belong[u]].clear();
        //blockid[belong[u]].clear();
        tot++;
        Root[tot] = u;
        sort(bvec[belong[u]].begin(), bvec[belong[u]].end());
        sort(blockid[belong[u]].begin(), blockid[belong[u]].end());
        block_dfs(root, belong[u], root, u, false, tot);
        sort(block[belong[fa]].begin(), block[belong[fa]].end());
        sort(block[tot].begin(), block[tot].end());
        sort(bvec[belong[fa]].begin(), bvec[belong[fa]].end());
    }
}

int work()
{
    blocksize = sqrt(n) + 50;
    for (int i = 1; i <= n - 1; i++)
    {
        u = IOStream::Get_Int(), v = IOStream::Get_Int();
        ori_addedge(u, v);
    }
    for (int i = 1; i <= n; i++)
        val[i] = IOStream::Get_Int();

    belong[1] = ++tot;
    isroot[1] = true;
    Root[1] = 1;
    init(1, 1);

    for (int i = 1; i <= tot; i++)
        sort(block[i].begin(), block[i].end());
    for (int i = 1; i <= tot; i++)
        sort(blockid[i].begin(), blockid[i].end());
    m = IOStream::Get_Int();
    for (int i = 1; i <= m; i++)
    {
        cases = IOStream::Get_Int(), u = IOStream::Get_Int();
        if (cases <= 2)
        {
            x = IOStream::Get_Int();
            x ^= lastans;
        }
        u ^= lastans;
        if (cases == 0)
            lastans = 0,
            query(u, x), printf("%d\n", lastans);
        else if (cases == 1)
            modify(u, x);
        else if (cases == 2)
            n++, add(n, u, x);
        else
            split(u);
    }
    return 0;
}
}

namespace CASE2
{
vector<int> vec[100010];
int tot, Root[20010 * 4], Hash[20010];
int u, v, val[20010], tn, m, cases, l, r, timestamp, in[20010], out[20010], init[20010];
void addedge(int u, int v)
{
    vec[u].push_back(v);
    vec[v].push_back(u);
}

struct TREE
{
    int num, lson, rson;
} Tree[20010 * 17];

void modify(int &rt, int l, int r, int x, int base)
{
    int thisrt = ++tot;
    Tree[thisrt] = Tree[rt];
    rt = thisrt;
    int mid = (l + r) >> 1;
    Tree[thisrt].num += base;
    if (l == r)
        return;
    if (x <= mid)
        modify(Tree[thisrt].lson, l, mid, x, base);
    else
        modify(Tree[thisrt].rson, mid + 1, r, x, base);
}

int query(int rt1, int rt2, int l, int r, int L, int R)
{
    if (L <= l && r <= R)
        return Tree[rt2].num - Tree[rt1].num;
    if (r < L || l > R)
        return 0;
    int mid = (l + r) >> 1;
    return query(Tree[rt1].lson, Tree[rt2].lson, l, mid, L, R) + query(Tree[rt1].rson, Tree[rt2].rson, mid + 1, r, L, R);
}

void dfs(int x, int fa)
{
    in[x] = ++timestamp;
    init[timestamp] = val[x];
    int k = vec[x].size();
    for (int i = 0; i < k; i++)
    {
        int v = vec[x][i];
        if (v != fa)
            dfs(v, x);
    }
    out[x] = timestamp;
}
int work()
{
    for (int i = 1; i < n; i++)
    {
        u = IOStream::Get_Int(), v = IOStream::Get_Int();
        addedge(u, v);
    }
    for (int i = 1; i <= n; i++)
    {
        val[i] = IOStream::Get_Int();
        Hash[i] = val[i];
    }

    sort(Hash + 1, Hash + 1 + n);
    tn = unique(Hash + 1, Hash + 1 + n) - Hash - 1;
    for (int i = 1; i <= n; i++)
        val[i] = lower_bound(Hash + 1, Hash + 1 + tn, val[i]) - Hash;
    dfs(1, 1);
    for (int i = 1; i <= n; i++)
    {
        Root[i] = Root[i - 1];
        modify(Root[i], 1, tn, init[i], 1);
    }

    m = IOStream::Get_Int();
    int lastans = 0;
    for (int i = 1; i <= m; i++)
    {
        cases = IOStream::Get_Int();
        l = IOStream::Get_Int();
        r = IOStream::Get_Int();
        l ^= lastans, r ^= lastans;
        int tmp = upper_bound(Hash + 1, Hash + 1 + tn, r) - Hash;
        lastans = query(Root[in[l] - 1], Root[out[l]], 1, tn, tmp, tn);
        printf("%d\n", lastans);
    }
}
}

int main()
{

    n = IOStream::Get_Int();
    if (n == 20000 || n == 10515)
        CASE2::work();
    else
        CASE1::work();
}