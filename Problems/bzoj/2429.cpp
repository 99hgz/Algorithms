#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <climits>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

#define N 1010 + 10

using namespace std;
int n, m, tot, mknum, monkey[1010];
struct node
{
    int v;
    double w;
    bool operator<(const node &dd) const { return w > dd.w; }
};
struct ZB
{
    int x, y;
} a[1010];
vector<node> q[N];
bool vis[N];
double ans;

void queue_prim()
{
    priority_queue<node> que;
    que.push((node){1, 0});
    ans = 0;
    memset(vis, false, sizeof(vis));
    int edge = n;
    node cur;
    while (!que.empty())
    {
        cur = que.top();
        que.pop();
        if (vis[cur.v])
            continue;
        ans = max(ans, cur.w);
        vis[cur.v] = true;
        for (int i = 0; i < q[cur.v].size(); i++)
        {
            if (vis[q[cur.v][i].v] == false)
                que.push(q[cur.v][i]);
        }
    }
}

double dis(int x, int y)
{
    return sqrt((a[x].x - a[y].x) * (a[x].x - a[y].x) + (a[x].y - a[y].y) * (a[x].y - a[y].y));
}

int main()
{
    scanf("%d", &mknum);
    for (int i = 1; i <= mknum; i++)
    {
        scanf("%d", &monkey[i]);
    }
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &a[i].x, &a[i].y);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
                continue;
            q[i].push_back((node){j, dis(i, j)});
            //printf("%.2lf\n", dis(i, j));
            //q[j].push_back((node){i, dis(i, j)});
        }
    }
    queue_prim();
    int tot = 0;
    //printf("%.2lf\n", ans);
    for (int i = 1; i <= mknum; i++)
    {
        if (monkey[i] >= ans)
            tot++;
    }
    printf("%d\n", tot);
    system("pause");
    return 0;
}