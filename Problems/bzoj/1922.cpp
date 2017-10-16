#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;

struct queNode
{
    ll n, d;
};
struct vecNode
{
    ll v, w;
};
struct cmp
{
    bool operator()(queNode a, queNode b) { return a.d > b.d; }
};

ll n, m, s, e, a, b, c;
ll tmp, num[3010], u, v, w;
bool visited[3010];
ll d1[3010], d2[3010];

vector<vecNode> vec[3010];
priority_queue<queNode, vector<queNode>, cmp> q;

void addedge(ll u, ll v, ll w)
{
    vec[u].push_back((vecNode){v, w});
}

ll dijkstra(ll s)
{
    for (ll i = 1; i <= n; i++)
    {
        d1[i] = 0x3f3f3f3f;
        visited[i] = false;
    }
    d1[s] = 0;
    q.push((queNode){1, 0});
    while (!q.empty())
    {

        queNode tmp = q.top();
        ll u = tmp.n;
        q.pop();

        if (visited[u])
            continue;
        visited[u] = true;
        d2[u] = tmp.d;
        for (ll i = 0; i < vec[u].size(); i++)
        {
            ll v = vec[u][i].v, w = vec[u][i].w;
            if (w == -1)
            {
                num[v]--;
                d2[v] = max(d2[v], d2[u]);
                if (num[v] == 0)
                    q.push((queNode){v, max(d1[v], d2[v])});
            }
            else
            {
                d1[v] = min(d1[v], d2[u] + w);
                if (num[v] == 0)
                    q.push((queNode){v, max(d1[v], d2[v])});
            }
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
    }
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld", &num[i]);
        for (ll j = 1; j <= num[i]; j++)
        {
            scanf("%lld", &tmp);
            addedge(tmp, i, -1);
        }
    }
    dijkstra(1);
    /*for (int i = 1; i <= n; i++)
    {
        printf("%d %lld %lld\n", i, d1[i], d2[i]);
    }*/
    printf("%lld\n", d2[n]);
    system("pause");
    return 0;
}