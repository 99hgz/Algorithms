#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

struct quenode
{
    int u, v;
    float w;
    bool operator<(const quenode &dd) const { return w > dd.w; }
};
vector<quenode> q[1010];
vector<quenode> vec[1010];
float dist[1010][1010], fmax1[1010][1010];
float ans, global_ans;
bool vis[1010];
int n, X, Y, P;
struct POINT
{
    int x, y, p;
} point[1010];

float get_dis(int a, int b)
{
    return sqrt((point[a].x - point[b].x) * (point[a].x - point[b].x) + (point[a].y - point[b].y) * (point[a].y - point[b].y));
}

void addedge(int u, int v, float w)
{
    q[u].push_back((quenode){u, v, w});
    q[v].push_back((quenode){v, u, w});
}

void addedgetotree(int u, int v, float w)
{
    vec[u].push_back((quenode){u, v, w});
    vec[v].push_back((quenode){v, u, w});
}

void queue_prim()
{
    priority_queue<quenode> que;
    que.push((quenode){-1, 1, 0});
    ans = 0;
    memset(vis, false, sizeof(vis));
    quenode cur;
    while (!que.empty())
    {
        cur = que.top();
        que.pop();

        if (vis[cur.v])
            continue;
        ans = ans + cur.w;
        if (cur.u != -1)
        {
            dist[cur.u][cur.v] = cur.w;
            dist[cur.v][cur.u] = cur.w;
            addedgetotree(cur.u, cur.v, cur.w);
        }
        vis[cur.v] = true;
        for (int i = 0; i < q[cur.v].size(); i++)
        {
            if (vis[q[cur.v][i].v] == false)
            {
                que.push(q[cur.v][i]);
            }
        }
    }
}

void dfs(int x, int fa, int rt, float maxedge)
{
    fmax1[rt][x] = maxedge;
    for (int i = 0; i < vec[x].size(); i++)
    {
        if (fa != vec[x][i].v)
            dfs(vec[x][i].v, x, rt, max(maxedge, vec[x][i].w));
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        memset(dist, 0, sizeof dist);
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
        {
            vec[i].clear();
            q[i].clear();
            scanf("%d%d%d", &X, &Y, &P);
            point[i].x = X;
            point[i].y = Y;
            point[i].p = P;
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = i + 1; j <= n; j++)
            {
                addedge(i, j, get_dis(i, j));
            }
        }
        queue_prim();
        //printf("%.2f\n",ans);
        for (int i = 1; i <= n; i++)
        {
            dfs(i, -1, i, 0);
        }
        global_ans = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = i + 1; j <= n; j++)
            {
                if (dist[i][j] != 0)
                {
                    global_ans = max(global_ans, (float)(point[i].p + point[j].p) / (ans - dist[i][j]));
                }
                else
                {
                    global_ans = max(global_ans, (float)(point[i].p + point[j].p) / (ans - fmax1[i][j]));
                }
            }
        }
        printf("%.2lf\n", global_ans);
    }
    system("pause");
    return 0;
}