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
    int n;
    ll d;
} quenode;
struct vecNode
{
    int v;
    ll w;
};
struct cmp
{
    bool operator()(queNode a, queNode b) { return a.d > b.d; }
};

int n, m, S, T, u, v, w;
bool visited[100100];
ll d[100100];
vector<vecNode> vec[100100];
priority_queue<queNode, vector<queNode>, cmp> q;

void addedge(int u, int v, ll w)
{
    vec[u].push_back((vecNode){v, w});
}

int dijkstra(int s)
{
    memset(d, 0x3f3f3f3f3f3f3f3f, sizeof d);
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
        for (int i = 0; i < vec[tmp.n].size(); i++)
        {
            int u = tmp.n, v = vec[tmp.n][i].v;
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
int len;
struct PATH
{
    int now, d;
};
void bfs(int S)
{
    queue<PATH> Q;
    Q.push((PATH){S, 1});
    while (!Q.empty())
    {
        int u = Q.front().now;
        int cd = Q.front().d;
        if (u == T)
        {
            len = Q.front().d;
            return;
        }
        Q.pop();
        for (int i = 0; i < vec[u].size(); i++)
        {
            vecNode P = vec[u][i];
            if (d[P.v] == d[u] + P.w)
                Q.push((PATH){P.v, cd + 1});
        }
    }
}

int main()
{
    freopen("z:/1.in", "r", stdin);
    freopen("z:/1.out", "w", stdout);

    scanf("%d%d%d%d", &n, &m, &S, &T);
    for (int i = 1; i <= m; i++)
    {
        ll w;
        scanf("%d%d%lld", &u, &v, &w);
        addedge(u, v, w);
        addedge(v, u, w);
    }
    dijkstra(S);
    if (d[T] == 0x3f3f3f3f3f3f3f3f)
    {
        printf("%lld\n", (ll)n * (n - 1) / (ll)2);
    }
    else
    {
        bfs(S);
        printf("%lld\n", (ll)len * (n - len));
    }

    return 0;
}