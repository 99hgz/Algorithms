#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <climits>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;

#define N 300 + 10
#define M 90000 + 10

using namespace std;
int n, m;
struct node
{
    int v, w;
    bool operator<(const node &dd) const
    {
        return w > dd.w;
    }
};
vector<node> q[N];
bool vis[N];
LL ans;
int well;

void queue_prim()
{
    priority_queue<node> que;
    while (!que.empty())
        que.pop();
    ans = 0;
    memset(vis, false, sizeof(vis));
    for (int i = 0; i < q[1].size(); i++)
    {
        que.push(q[1][i]);
    }
    vis[1] = true;
    int edge = n - 1;
    node cur;
    while (edge--)
    {
        cur = que.top();
        que.pop();
        if (vis[cur.v] == true)
        {
            while (vis[cur.v])
            {
                cur = que.top();
                que.pop();
            }
        }
        ans = max(ans, (LL)cur.w);
        vis[cur.v] = true;
        //printf("%d\n", cur.v);
        for (int i = 0; i < q[cur.v].size(); i++)
        {
            if (vis[q[cur.v][i].v] == false)
                que.push(q[cur.v][i]);
        }
    }
}

int main()
{
    scanf("%d %d", &n, &m);
    int i, j;
    int tmp[N];
    int u, v, w;
    int wellmin = INT_MAX;
    node cur;
    for (i = 0; i <= n; i++)
        q[i].clear();
    for (i = 1; i <= m; i++)
    {
        scanf("%d %d %d", &u, &v, &w);
        cur.v = v;
        cur.w = w;
        q[u].push_back(cur);
        cur.v = u;
        q[v].push_back(cur);
    }
    queue_prim();
    printf("%d %lld\n", n - 1, ans);
    system("pause");
    return 0;
}