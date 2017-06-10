#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

struct queNode
{
    int n;
    double d;
} quenode;
struct vecNode
{
    int v;
    double w;
} vecnode;
struct cmp
{
    bool operator()(queNode a, queNode b) { return a.d > b.d; }
};

int n, m, s, e, a, b, c;
bool visited[10010];
double d[10010];
vector<vecNode> vec[10010];
priority_queue<queNode, vector<queNode>, cmp> q;

void addedge(int u, int v, double w)
{
    vecnode.v = v;
    vecnode.w = w;
    vec[u].push_back(vecnode);
    vecnode.v = u;
    vecnode.w = w;
    vec[v].push_back(vecnode);
}

int dijkstra(int s, int e)
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

int dist(int x1, int y1, int x2, int y2) { return sqr(x1 - x2) + sqr(y1 - y2); }
int main()
{
    scanf("%d%d%d%d", &s, &t, &A, &B);
    for (i = 1; i <= s; i++)
    {
        scanf("%d%d%d%d%d%d%d", &x[1][i], &y[1][i], &x[2][i], &y[2][i], &x[3][i], &y[3][i], &T[i]);
        int d1 = dist(x[2][i], y[2][i], x[3][i], y[3][i]);
        int d2 = dist(x[1][i], y[1][i], x[3][i], y[3][i]);
        int d3 = dist(x[1][i], y[1][i], x[2][i], y[2][i]);
        if (d1 > d2 && d1 > d3)
        {
            x[4][i] = x[3][i] - (x[1][i] - x[2][i]);
            y[4][i] = y[3][i] - (y[1][i] - y[2][i]);
        }
        else if (d2 > d1 && d2 > d3)
        {
            x[4][i] = x[3][i] - (x[2][i] - x[1][i]);
            y[4][i] = y[3][i] - (y[2][i] - y[1][i]);
        }
        else if (d3 > d1 && d3 > d2)
        {
            x[4][i] = x[1][i] - (x[3][i] - x[2][i]);
            y[4][i] = y[1][i] - (y[3][i] - y[2][i]);
        }
        addedge(4 * i - 3, 4 * i - 2, sqrt(d3) * T[i]);
        addedge(4 * i - 3, 4 * i - 1, sqrt(d2) * T[i]);
        addedge(4 * i - 3, 4 * i, sqrt(dist(x[1][i], y[1][i], x[4][i], y[4][i])) * T[i]);
        addedge(4 * i - 2, 4 * i - 1, sqrt(d1) * T[i]);
        addedge(4 * i - 2, 4 * i, sqrt(dist(x[2][i], y[2][i], x[4][i], y[4][i])) * T[i]);
        addedge(4 * i - 1, 4 * i, sqrt(dist(x[3][i], y[3][i], x[4][i], y[4][i])) * T[i]);
    }
    for (i = 1; i <= s; i++)
    {
        for (j = i + 1; j <= s; j++)
        {
            for (pointi = -3; pointi <= 0; pointi++)
            {
                for (pointj = -3; pointj <= 0; pointj++)
                {
                    addedge(4 * i + pointi, 4 * j + pointj, sqrt(dist(x[pointi + 4][i], y[pointi + 4][i], x[pointj + 4][j], y[pointj + 4][j])) * t)
                }
            }
        }
    }
    system("pause");
    return 0;
}