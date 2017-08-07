#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

struct PATH
{
    ll to, w;
};
vector<PATH> vec[2010];
ll f[2010][2010], size[2010];
ll n, k, a, b, c;

void addedge(ll u, ll v, ll w)
{
    vec[u].push_back((PATH){v, w});
}

void dfs(ll u, ll fa)
{
    f[u][0] = f[u][1] = 0;
    size[u] = 1;
    for (ll i = 0; i < vec[u].size(); i++)
    {
        ll v = vec[u][i].to;
        if (v != fa)
        {
            dfs(vec[u][i].to, u);
            size[u] += size[v];
            for (ll j = min(k, size[u]); j >= 0; j--)
            {
                for (ll l = 0; l <= min(j, size[v]); l++)
                {
                    ll blackscore = (l * (k - l)) * vec[u][i].w;
                    ll whitescore = (size[v] - l) * (n - k - size[v] + l) * vec[u][i].w;
                    f[u][j] = max(f[u][j], f[u][j - l] + f[v][l] + blackscore + whitescore);
                }
            }
        }
    }
}

int main()
{
    memset(f, 128, sizeof f);
    scanf("%lld%lld", &n, &k);
    for (ll i = 1; i <= n - 1; i++)
    {
        scanf("%lld%lld%lld", &a, &b, &c);
        addedge(a, b, c);
    }
    dfs(1, 0);
    printf("%lld\n", f[1][k]);
    system("pause");
    return 0;
}