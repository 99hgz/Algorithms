#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
typedef long long ll;

vector<int> vec[60010], bvec[60010], block[60010], blockid[60010], bbvec[60010];
int father[60010], belong[60010], blocksize, tot, lastans, val[60010], n, u, v, m, cases, x;
bool isroot[60010];
void ori_addedge(int u, int v)
{
    vec[u].push_back(v);
    vec[v].push_back(u);
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

void dfs(int x, int val)
{
    lastans += block[x].end() - upper_bound(block[x].begin(), block[x].end(), val);
    for (int i = 0; i < bvec[x].size(); i++)
        dfs(bvec[x][i], val);
}

void dfs2(int x, int bl, int fa, int v1)
{
    if (belong[x] != bl)
        return;
    if (val[x] > v1)
        lastans++;
    for (int i = 0; i < bbvec[x].size(); i++)
        dfs(bbvec[x][i], v1);
    for (int i = 0; i < vec[x].size(); i++)
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
        block[tot].push_back(val[x]);
        blockid[tot].push_back(x);
    }
    if (belong[x] != belong[fa])
        addedge(belong[fa], belong[x]), bbvec[fa].push_back(belong[x]);
    int bl = belong[x];
    sort(block[bl].begin(), block[bl].end());
}

void split(int k)
{
}

int main()
{
    scanf("%d", &n);
    blocksize = sqrt(n);
    for (int i = 1; i <= n - 1; i++)
    {
        scanf("%d%d", &u, &v);
        ori_addedge(u, v);
    }
    for (int i = 1; i <= n; i++)
        scanf("%d", &val[i]);

    belong[1] = ++tot;
    isroot[1] = true;
    init(1, 1);

    for (int i = 1; i <= tot; i++)
        sort(block[i].begin(), block[i].end());

    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &cases, &u);
        if (cases <= 2)
        {
            scanf("%d", &x);
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
    //system("pause");
    return 0;
}