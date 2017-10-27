#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;

int n, m, dis[10010], flag[10010], Next[100100], head[10010], tot, tree[100100], val[100100];
bool visit[10010];
queue<int> Q;
int cases, u, v, w;
void addedge(int x, int y, int z)
{
    tot++;
    Next[tot] = head[x];
    head[x] = tot;
    tree[tot] = y;
    val[tot] = z;
}
int spfa(int s)
{
    for (int i = 0; i <= n; i++)
        dis[i] = 1 << 30, visit[i] = false, flag[i] = 0;
    int t = 0, w = 1;
    Q.push(s);
    dis[s] = 0;
    visit[s] = true;
    flag[s] = 1;
    while (!Q.empty())
    {

        int u = Q.front();
        Q.pop();
        visit[u] = false;
        if (dis[s] < 0)
            return 0;
        for (int i = head[u]; i; i = Next[i])
        {
            int v = tree[i];
            if (dis[u] + val[i] < dis[v])
            {
                dis[v] = dis[u] + val[i];
                if (!visit[v])
                {
                    Q.push(v);
                    visit[v] = true;
                    flag[v]++;
                    if (flag[v] > n)
                        return 0;
                }
            }
        }
    }
    return 1;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        addedge(0, i, 0);
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &cases);
        if (cases == 1)
        {
            scanf("%d%d%d", &u, &v, &w);
            addedge(v, u, -w);
        }
        else if (cases == 2)
        {
            scanf("%d%d%d", &u, &v, &w);
            addedge(u, v, w);
        }
        else if (cases == 3)
        {
            scanf("%d%d", &u, &v);
            addedge(u, v, 0);
            addedge(v, u, 0);
        }
    }
    if (!spfa(0))
    {
        printf("No\n");
    }
    else
    {
        printf("Yes\n");
    }
    system("pause");
    return 0;
}