#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
ll low[600], dfn[600];
ll n, m, a, b, root, time1;
bool visited[600], _visited[600], iscut_vertex[600];
//vector<ll> cut_vertex;
vector<ll> vec[600];
struct BRIDGE
{
    ll u, v;
};
vector<BRIDGE> bridge;

void addedge(ll a, ll b) { vec[a].push_back(b); }
bool cmp(BRIDGE a, BRIDGE b)
{
    if (a.u == b.u)
        return (a.v < b.v);
    else
        return (a.u < b.u);
}
void tarjan(ll u, ll fa)
{
    low[u] = dfn[u] = ++time1;
    visited[u] = true;
    ll son = 0;
    for (ll i = 0; i < vec[u].size(); i++)
    {
        ll v = vec[u][i];
        if (!visited[v])
        {
            son++;
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            /*if (dfn[u] < low[v])
            {
                ll tu = u, tv = v;
                if (u > v)
                    swap(tu, tv);
                bridge.push_back((BRIDGE){tu, tv});
            }*/
            if (((u == root) && (son > 1)) || ((u != root) && (dfn[u] <= low[v])))
            {
                //cut_vertex.push_back(u);
                //printf("%d\n", u);
                iscut_vertex[u] = true;
            }
        }
        else if (fa != v)
        {
            low[u] = min(low[u], dfn[v]);
        }
    }
}
ll size, cv;
void dfs(ll x)
{
    if (_visited[x])
    {
        return;
    }
    if (visited[x])
        return;
    if (iscut_vertex[x])
    {
        _visited[x] = true;
        size++;
        cv++;
        return;
    }

    size++;
    visited[x] = true;
    _visited[x] = true;
    for (ll i = 0; i < vec[x].size(); i++)
    {
        dfs(vec[x][i]);
    }
}

int main()
{
    ll T = 0;
    while ((~scanf("%lld", &n)) && (n != 0))
    {
        T++;
        for (ll i = 1; i <= 500; i++)
        {
            vec[i].clear();
        }
        memset(visited, 0, sizeof visited);
        memset(low, 0, sizeof low);
        memset(dfn, 0, sizeof dfn);
        memset(iscut_vertex, 0, sizeof iscut_vertex);
        ll thisn = 0;
        for (ll i = 1; i <= n; i++)
        {
            scanf("%lld%lld", &a, &b);
            addedge(a, b);
            addedge(b, a);
            thisn = max(thisn, max(a, b));
        }
        for (ll i = 1; i <= thisn; i++)
        {
            if (!visited[i])
            {
                root = i;
                tarjan(i, i);
            }
        }

        memset(visited, 0, sizeof visited);
        ll ans1 = 0, ans2 = 1;
        for (ll i = 1; i <= thisn; i++)
        {
            if (!visited[i] && !iscut_vertex[i])
            {
                memset(_visited, 0, sizeof _visited);
                cv = 0;
                size = 0;
                dfs(i);
                //printf("%d %d\n", cv, size);
                if (cv == 0)
                {
                    ans1 += 2;
                    ans2 *= size * (size - 1) / 2;
                }
                else if (cv == 1)
                {
                    ans1 += 1;
                    ans2 *= size - 1;
                }
            }
        }
        printf("Case %lld: %lld %lld\n", T, ans1, ans2);
    }
    system("pause");
    return 0;
}