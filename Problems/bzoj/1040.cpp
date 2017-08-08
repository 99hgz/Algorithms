#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

ll f[1000010][2];
ll a[1000010];
bool visited[1000010];
ll root1, root2, ans;
ll bh, rootbh;
struct Node
{
    ll to, bh;
};
vector<Node> vec[1000010];
ll n, l, k, rt;

void dp(ll x, ll fa)
{
    f[x][0] = 0;
    f[x][1] = a[x];
    for (ll i = 0; i < vec[x].size(); i++)
    {
        int v = vec[x][i].to;
        if (v == fa || ((vec[x][i].bh ^ 1) == rootbh) || (vec[x][i].bh == rootbh))
            continue;
        dp(v, x);
        f[x][1] += f[v][0];
        f[x][0] += max(f[v][0], f[v][1]);
    }
}

void dfs(ll x, ll fa)
{
    visited[x] = true;
    for (ll i = 0; i < vec[x].size(); i++)
    {
        if (vec[x][i].to == fa)
            continue;
        if (visited[vec[x][i].to])
        {
            root1 = x;
            root2 = vec[x][i].to;
            rootbh = vec[x][i].bh;
        }
        else
        {
            dfs(vec[x][i].to, x);
        }
    }
}

int main()
{
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld%lld", &a[i], &k);
        vec[i].push_back((Node){k, bh++});
        vec[k].push_back((Node){i, bh++});
    }
    for (ll i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            dfs(i, -1);
            //printf("%lld %lld\n", root1, rootbh);
            dp(root1, -1);
            ll tmp = f[root1][0];
            dp(root2, -1);
            tmp = max(tmp, f[root2][0]);
            ans += tmp;
        }
    }
    //dfs(rt);
    //printf("%d\n", max(f[rt][0], f[rt][1]));
    printf("%lld\n", ans);
    system("pause");
    return 0;
}