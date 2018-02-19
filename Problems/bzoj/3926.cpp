#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

int fa[4000005], a[4000005][10], cnt, len[4000005];
vector<int> vec[100010];
int root, n, c, color[100010], du[100010], u, v;
ll ans;
int extend(int last, int ch)
{
    int p = last, np = ++cnt;
    len[np] = len[p] + 1;
    while (p && !a[p][ch])
        a[p][ch] = np, p = fa[p];
    if (!p)
        fa[np] = root;
    else
    {
        int q = a[p][ch];
        if (len[q] == len[p] + 1)
            fa[np] = q;
        else
        {
            int nq = ++cnt;
            len[nq] = len[p] + 1;
            memcpy(a[nq], a[q], sizeof a[q]);
            fa[nq] = fa[q];
            fa[q] = fa[np] = nq;
            while (p && a[p][ch] == q)
                a[p][ch] = nq, p = fa[p];
        }
    }
    return np;
}

void dfs(int x, int fa, int pre)
{
    int t = extend(pre, color[x]);
    for (int i = 0; i < vec[x].size(); i++)
    {
        int v = vec[x][i];
        if (v != fa)
            dfs(v, x, t);
    }
}

int main()
{
    root = ++cnt;
    scanf("%d%d", &n, &c);
    for (int i = 1; i <= n; i++)
        scanf("%d", &color[i]);
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
        vec[v].push_back(u);
        du[u]++, du[v]++;
    }
    for (int i = 1; i <= n; i++)
    {
        if (du[i] == 1)
            dfs(i, i, root);
    }
    for (int i = 1; i <= cnt; i++)
    {
        ans += len[i] - len[fa[i]];
    }
    printf("%lld\n", ans);
    system("pause");
    return 0;
}
