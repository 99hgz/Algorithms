#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
ll f[100010][4];
int color[100010];
vector<int> vec[100010];
ll MOD = 1000000007;
int n, k, u, v, b, c;

void addedge(int u, int v)
{
    vec[u].push_back(v);
}

void dfs(int rt, int fa)
{
    if (color[rt] == 0)
        f[rt][1] = f[rt][2] = f[rt][3] = 1;
    else
        f[rt][color[rt]] = 1;
    for (int i = 0; i < vec[rt].size(); i++)
    {
        int v = vec[rt][i];
        if (v != fa)
        {
            dfs(v, rt);
            for (int i = 1; i <= 3; i++)
                if (color[rt] == 0 || color[rt] == i)
                {

                    ll tmp = 0;
                    for (int j = 1; j <= 3; j++)
                        if (i != j)
                            tmp = (tmp + f[v][j]) % MOD;
                    f[rt][i] = f[rt][i] * tmp % MOD;
                }
        }
    }
}

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }
    for (int i = 1; i <= k; i++)
    {
        scanf("%d%d", &b, &c);
        color[b] = c;
    }
    dfs(1, 1);
    printf("%lld\n", (f[1][1] + f[1][2] + f[1][3]) % MOD);
    while (1)
    {
    }
}
