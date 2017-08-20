#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
#define strlen1 300010
using namespace std;
typedef long long ll;
vector<int> isend[strlen1];
int bh, n, tn, m, l, r, G;
int ans, length, pointnum, times1;
int trietree[strlen1][26];

char A[strlen1];
int root[strlen1], point[strlen1], ltime[strlen1], rtime[strlen1];
struct NODe
{
    int lson, rson, v;
} tree[strlen1 * 20];

int build(int l, int r)
{
    bh++;
    //printf("build:%d %d %d\n", l, r, bh);
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

int update(int i, int l, int r, int old)
{

    if (l == r)
    {
        bh++;
        tree[bh].v = tree[old].v + 1;
        return bh;
    }
    int tbh;
    int mid = (l + r) >> 1;
    if (i > mid)
    {
        bh++;
        tbh = bh;
        tree[bh].v = tree[old].v + 1;
        tree[bh].lson = tree[old].lson;
        tree[tbh].rson = update(i, mid + 1, r, tree[old].rson);
    }
    else
    {
        bh++;
        tbh = bh;
        tree[bh].v = tree[old].v + 1;
        tree[bh].rson = tree[old].rson;
        tree[tbh].lson = update(i, l, mid, tree[old].lson);
    }
    //printf("%d %d %d %d", i, l, r, old);
    //printf(" change->%d\n", tbh);
    //printf("lson=%d rson=%d\n", tree[tbh].lson, tree[tbh].rson);
    return tbh;
}

int query(int G, int bh1, int bh2, int l, int r)
{
    //printf("%d %d %d %d %d\n", G, bh1, bh2, l, r);
    if (l == r)
    {
        return l;
    }
    int mid = (l + r) >> 1;
    int lsl = tree[tree[bh2].lson].v - tree[tree[bh1].lson].v;
    if (G <= lsl)
    {
        return query(G, tree[bh1].lson, tree[bh2].lson, l, mid);
    }
    else
    {
        return query(G - lsl, tree[bh1].rson, tree[bh2].rson, mid + 1, r);
    }
}

void add(int bh)
{
    int length = strlen(A);
    int cur = 0;
    for (int i = length - 1; i >= 0; i--)
    {
        if (trietree[cur][A[i] - 'a'] == 0)
        {
            trietree[cur][A[i] - 'a'] = ++pointnum;
        }
        cur = trietree[cur][A[i] - 'a'];
    }
    isend[cur].push_back(bh);

    point[bh] = cur;
    printf("bh2point %d %d\n", bh, point[bh]);
}

void dfs(int cur)
{

    ltime[cur] = times1;
    if (isend[cur].size() > 0)
    {
        ltime[cur] = ++times1;
        root[ltime[cur]] = update(isend[cur][0], 1, strlen1, root[ltime[cur] - 1]);
        for (int i = 1; i < isend[cur].size(); i++)
        {
            root[ltime[cur]] = update(isend[cur][i], 1, strlen1, root[ltime[cur]]);
        }
    }
    for (int i = 0; i <= 25; i++)
    {
        if (trietree[cur][i] != 0)
        {
            dfs(trietree[cur][i]);
        }
    }
    rtime[cur] = times1;
    printf("cur=%d l=%d r=%d\n", cur, ltime[cur], rtime[cur]);
}

int main()
{
    bh = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", A);
        add(i);
    }
    root[0] = build(1, strlen1);
    printf("----\n");
    dfs(0);
    printf("----\n");
    int k;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &k);
        printf("%d %d\n", point[i], ltime[point[i]]);
        printf("%d\n", query(k, root[ltime[point[i]]], root[rtime[point[i]]], 1, strlen1));
    }
    system("pause");
    return 0;
}
