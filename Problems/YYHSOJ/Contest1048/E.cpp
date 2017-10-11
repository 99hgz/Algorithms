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
bool visited[100010];
int d[100010];
vector<vecNode> vec[100010];
priority_queue<queNode, vector<queNode>, cmp> q;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        vecnode.v = b;
        vecnode.w = c;
        vec[a].push_back(vecnode);
        vecnode.v = a;
        vec[b].push_back(vecnode);
    }
    s = 1;
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
    printf("%d", d[n]);
    return 0;
}