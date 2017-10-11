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
    for (int i = 1; i <= n; i++)
    {
        que.push(q[i][i - 1]);
    }
    ans = 0;
    memset(vis, false, sizeof(vis));
    for (int i = 0; i < q[well].size(); i++)
    {
        que.push(q[well][i]);
    }
    vis[well] = true;
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
        ans = ans + cur.w;
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
    scanf("%d", &n);
    int i, j;
    int tmp[N];
    int u, v, w;
    int wellmin = INT_MAX;
    node cur;
    for (i = 0; i <= n; i++)
        q[i].clear();
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &tmp[i]);
        if (tmp[i] < wellmin)
        {
            wellmin = min(wellmin, tmp[i]);
            well = i;
        }
        //q[i].push_back(cur);
    }
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            scanf("%d", &w);
            if (i != j)
            {
                cur.v = j;
                cur.w = w;
                q[i].push_back(cur);
            }
            else
            {
                cur.v = j;
                cur.w = tmp[i];
                q[i].push_back(cur);
            }
        }
    }
    queue_prim();
    printf("%lld\n", ans + wellmin);
    system("pause");
    return 0;
}