#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <queue>

using namespace std;
typedef long long ll;

struct queNode
{
    ll n, d;
} quenode;
struct vecNode
{
    ll v, w;
} vecnode;
struct cmp
{
    bool operator()(queNode a, queNode b) { return a.d > b.d; }
};
ll a[20];
ll n, m, s, e, b, c;
bool visited[500010];
ll d[500010];
vector<vecNode> vec[500010];
priority_queue<queNode, vector<queNode>, cmp> q;

void addedge(ll u, ll v, ll w)
{
    vecnode.v = v;
    vecnode.w = w;
    vec[u].push_back(vecnode);
}

ll dijkstra(ll s)
{
    for (ll i = 0; i < a[1]; i++)
    {
        d[i] = (ll)10000000000000;
        visited[i] = false;
    }
    quenode.d = 0;
    quenode.n = s;
    d[s] = 0;
    q.push(quenode);
    queNode tmp;
    while (!q.empty())
    {
        tmp = q.top();
        q.pop();
        if (visited[tmp.n])
            continue;
        visited[tmp.n] = true;
        for (ll i = 0; i < vec[tmp.n].size(); i++)
        {
            ll u = tmp.n, v = vec[tmp.n][i].v;
            if ((!visited[v]) && (d[v] > d[u] + vec[u][i].w))
            {
                d[v] = d[u] + vec[u][i].w;
                quenode.d = d[v];
                quenode.n = v;
                q.push(quenode);
            }
        }
    }
}

ll solve(ll x)
{
    ll res = 0;
    for (ll i = 0; i < a[1]; i++)
    {
        if (d[i] == (ll)10000000000000)
            continue;
        if (x < d[i])
            continue;
        res += ((x - d[i]) / a[1]) + 1;
    }
    return res;
}

int main()
{
    ll bmin, bmax;
    scanf("%lld%lld%lld", &n, &bmin, &bmax);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
    }
    for (ll i = 0; i < a[1]; i++)
    {
        for (ll j = 2; j <= n; j++)
        {
            addedge(i, (i + a[j]) % a[1], a[j]);
        }
    }
    dijkstra(0);
    printf("%lld", solve(bmax) - solve(bmin - 1));
    return 0;
}