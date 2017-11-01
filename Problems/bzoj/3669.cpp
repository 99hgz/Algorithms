#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d%d", &edge[i].x, &edge[i].y, &edge[i].a, &edge[i].b);
    }
    sort(edge + 1, edge + 1 + m, cmp);
    memset(dis, 0x3f3f3f3f, sizeof dis);
    dis[n] = 0;
    for (int i = 1; i <= m; i++)
    {
        addedge(edge[i].x, edge[i].y, edge[i].b);
        addedge(edge[i].y, edge[i].x, edge[i].b);
        Q.push(edge[i].y);
        Q.push(edge[i].x);
        vis[edge[i].y] = true;
        vis[edge[i].x] = true;
        if (edge[i + 1].a == edge[i].a)
            continue;
        while (!Q.empty())
        {
            int u = Q.front();
            Q.pop();
            vis[u] = false;
            for (int it = Head[u]; it; it = Next[it])
            {
                int v = To[it];
                if (max(Val[it], dis[u]) < dis[v])
                {
                    if (!vis[v])
                        vis[v] = true, Q.push(v);
                    dis[v] = max(Val[it], dis[u]);
                }
            }
        }
        ans = min(ans, edge[i].a + dis[1]);
    }
    printf("%d\n", ans);
    system("pause");
    return 0;
}