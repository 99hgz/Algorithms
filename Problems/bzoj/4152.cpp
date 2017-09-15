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

int n, m, s, e, a, b, c;
bool visited[200010];
int d[200010];
vector<vecNode> vec[200010];
priority_queue<queNode, vector<queNode>, cmp> q;
struct Node
{
    int id, x, y;
} points[200010];
bool cmp(Node a, Node b) { return a.x < b.x; }
bool cmp2(Node a, Node b) { return a.y < b.y; }
void addedge(int u, int v, int w)
{
    vecnode.v = v;
    vecnode.w = w;
    vec[u].push_back(vecnode);
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
int nx, nx2;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &points[i].x, &points[i].y);
        points[i].id = i;
    }
    sort(points + 1, points + 1 + n, cmp);
    for (int i = 1; i <= n; i++)
    {
        nx = points[i].id;
        if (i > 1)
        {
            nx2 = points[i - 1].id;
            addedge(nx, nx2, points[i].x - points[i - 1].x);
        }
        if (i < n)
        {
            nx2 = points[i + 1].id;
            addedge(nx, nx2, points[i + 1].x - points[i].x);
        }
    }
    sort(points + 1, points + 1 + n, cmp2);
    for (int i = 1; i <= n; i++)
    {
        nx = points[i].id;
        if (i > 1)
        {
            nx2 = points[i - 1].id;
            addedge(nx, nx2, points[i].y - points[i - 1].y);
        }
        if (i < n)
        {
            nx2 = points[i + 1].id;
            addedge(nx, nx2, points[i + 1].y - points[i].y);
        }
    }
    dijkstra(1);
    printf("%d\n", d[n]);
    return 0;
}