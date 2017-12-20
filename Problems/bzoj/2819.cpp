#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;

vector<int> vec[500010];
int in[500010], out[500010], timestamp, BIT[1000010], a[500010], n, u, v, q;
char CASES[10];
int deep[500010], st[500010][20];

void addedge(int u, int v)
{
    vec[u].push_back(v);
}

int lowbit(int x) { return x & (-x); }

int sum(int pos)
{
    int res = 0, upos = pos;
    for (; pos; pos -= lowbit(pos))
        res ^= BIT[pos];
    return res;
}

void add(int pos, int val)
{
    for (; pos <= 2 * n; pos += lowbit(pos))
        BIT[pos] ^= val;
}

void lca_dfs(int x, int fa, int depth)
{
    in[x] = ++timestamp;
    st[x][0] = fa;
    deep[x] = depth;
    for (int i = 0; i < vec[x].size(); i++)
    {
        int P = vec[x][i];
        if (P != fa)
            lca_dfs(P, x, depth + 1);
    }
    out[x] = ++timestamp;
}

void init_st()
{

    int deep = floor(log(n) / log(2));
    for (int j = 1; j <= deep; j++)
        for (int i = 1; i <= n; i++)
            st[i][j] = st[st[i][j - 1]][j - 1];
}

int lca(int a, int b)
{
    int ua = a, ub = b;
    if (deep[a] < deep[b])
        swap(a, b);
    int depth = floor(log(deep[a] - 1) / log(2));
    for (int i = depth; i >= 0; i--)
        if (deep[a] - (1 << i) >= deep[b])
            a = st[a][i];
    if (a == b)
        return a;
    for (int i = depth; i >= 0; i--)
        if (st[a][i] != st[b][i])
        {
            a = st[a][i];
            b = st[b][i];
        }
    return st[a][0];
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n - 1; i++)
    {
        scanf("%d%d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }
    lca_dfs(1, 0, 1);
    init_st();
    for (int i = 1; i <= n; i++)
        add(in[i], a[i]),
            add(out[i], a[i]);

    scanf("%d", &q);
    for (int i = 1; i <= q; i++)
    {
        scanf("%s", CASES);
        if (CASES[0] == 'Q')
        {
            int l, r;
            scanf("%d%d", &u, &v);
            //printf("lca=%d\n", lca(u, v));
            int res = sum(in[u]) ^ sum(in[v]) ^ a[lca(u, v)];
            //printf("%d\n", res);
            if (res)
                printf("Yes\n");
            else
                printf("No\n");
        }
        else
        {
            scanf("%d%d", &u, &v);
            add(in[u], a[u] ^ v);
            add(out[u], a[u] ^ v);
            a[u] = v;
        }
    }
    system("pause");
    return 0;
}