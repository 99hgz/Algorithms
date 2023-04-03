#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

struct G
{
    int Head[20], Next[1010], To[1010], cnt;
    void addedge(int u, int v)
    {
        cnt++;
        Next[cnt] = Head[u];
        Head[u] = cnt;
        To[cnt] = v;
    }
} now, origin;
ll f[20][20];
ll ans;
int used[20], n, m, u, v;

void dfs2(int u, int fa)
{
    for (int i = 1; i <= n; i++)
        f[u][i] = used[i];
    for (int it = now.Head[u]; it; it = now.Next[it])
    {
        int v = now.To[it];
        if (v == fa)
            continue;
        dfs2(v, u);
        for (int j = 1; j <= n; j++)
        {
            ll res = 0;
            for (int it2 = origin.Head[j]; it2; it2 = origin.Next[it2])
                res += f[v][origin.To[it2]];
            f[u][j] *= res;
        }
    }
}

ll calc()
{
    memset(f, 0, sizeof f);
    dfs2(1, 1);
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        ans += f[1][i];
    //printf("%lld \n", ans);
    return ans;
}

void dfs(int x, int dep)
{
    if (x == n + 1)
    {
        ans += (((n & 1) == (dep & 1)) ? 1 : -1) * calc();
        return;
    }
    dfs(x + 1, dep);
    used[x] = 1;
    dfs(x + 1, dep + 1);
    used[x] = 0;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        origin.addedge(u, v);
        origin.addedge(v, u);
    }
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &u, &v);
        now.addedge(u, v);
        now.addedge(v, u);
    }
    dfs(1, 0);
    printf("%lld\n", ans);
    system("pause");
    return 0;
}