#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <queue>

using namespace std;
typedef long long ll;

struct queNode
{
    int n, d;
} quenode;
struct vecNode
{
    int v, w;
} vecnode;
struct cmp
{
    bool operator()(queNode a, queNode b) { return a.d > b.d; }
};

int n, m, s, e, a, b, c, x, S, T, w, y;
bool visited[2000000];
int d[2000000];
vector<vecNode> vec[2000000];
priority_queue<queNode, vector<queNode>, cmp> q;

void addedge(int u, int v, int w)
{
    //printf("%d %d\n", u, v);
    vecnode.v = v;
    vecnode.w = w;
    vec[u].push_back(vecnode);
    vecnode.v = u;
    vecnode.w = w;
    vec[v].push_back(vecnode);
}

int dijkstra(int s)
{
    for (int i = 1; i <= n; i++)
    {
        d[i] = 2147483647;
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

int main()
{
    scanf("%d%d", &n, &m);
    if (n == 1 || m == 1)
    {
        int ans = 2100000000;
        for (int i = 1; i < max(m, n); i++)
        {
            scanf("%d", &w);
            ans = min(ans, w);
        }
        printf("%d\n", ans);
        return 0;
    }
    S = 1;
    T = (n - 1) * (m - 1) * 2 + 2;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j < m; j++)
        {
            scanf("%d", &w);
            if (i == 1)
            {
                u = 1;
                v = j * 2 + 1;
                addedge(u, v, w);
            }
            else if (i == n)
            {
                u = (n - 1) * (m - 1) * 2 + 2;
                v = ((i - 2) * (m - 1) + j) * 2;
                addedge(u, v, w);
            }
            else
            {
                u = ((i - 2) * (m - 1) + j) * 2;
                v = ((i - 1) * (m - 1) + j) * 2 + 1;
                addedge(u, v, w);
            }
        }
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &w);
            if (j == 1)
            {
                u = (n - 1) * (m - 1) * 2 + 2;
                v = ((i - 1) * (m - 1) + j) * 2;
                addedge(u, v, w);
            }
            else if (j == m)
            {
                u = 1;
                v = ((i - 1) * (m - 1) + j - 1) * 2 + 1;
                addedge(u, v, w);
            }
            else
            {
                u = ((i - 1) * (m - 1) + j - 1) * 2 + 1;
                v = ((i - 1) * (m - 1) + j) * 2;
                addedge(u, v, w);
            }
        }
    for (int i = 1; i < n; i++)
        for (int j = 1; j < m; j++)
        {
            scanf("%d", &w);
            u = ((i - 1) * (m - 1) + j) * 2;
            v = ((i - 1) * (m - 1) + j) * 2 + 1;
            addedge(u, v, w);
        }
    n = T;
    dijkstra(S);
    printf("%d\n", d[T]);
    system("pause");
    return 0;
}