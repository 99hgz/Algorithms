#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
ll n, m, xorval[50010], u, v, w;
bool visited[50010];

struct Node
{
    ll v, w;
};
vector<Node> vec[50010];
void addedge(ll u, ll v, ll w)
{
    vec[u].push_back((Node){v, w});
}

struct LB
{
    ll f[70];
    LB()
    {
        memset(f, 0, sizeof(f));
    }
    bool insert(ll val)
    {
        for (ll i = 62; i >= 0; i--)
        {
            if ((val & (1LL << i)))
            {
                if ((!f[i]))
                {
                    f[i] = val;
                    break;
                }
                val ^= (f[i]);
            }
        }
        return val > 0;
    }
    ll max(ll intial)
    {
        ll res = intial;
        for (ll i = 62; i >= 0; i--)
        {
            if ((res ^ f[i]) > res)
            {
                res = (res ^ f[i]);
            }
        }
        return res;
    }
};
LB list;
void dfs(ll x)
{
    visited[x] = true;
    for (ll i = 0; i < vec[x].size(); i++)
    {
        ll v = vec[x][i].v;
        if (visited[v])
        {
            list.insert(xorval[v] ^ xorval[x] ^ vec[x][i].w);
        }
        else
        {
            xorval[v] = xorval[x] ^ vec[x][i].w;
            dfs(v);
        }
    }
}

int main()
{
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= m; i++)
    {
        scanf("%lld%lld%lld", &u, &v, &w);
        addedge(u, v, w);
        addedge(v, u, w);
    }
    dfs(1);
    printf("%lld\n", list.max((ll)xorval[n]));
    system("pause");
    return 0;
}