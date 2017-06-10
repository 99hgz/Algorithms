#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, m, S, tot, Next[110000], head[11000], tree[110000], val[110000], dis[11000], a[11000], flag[11000], x[1100000];
bool visit[11000];
bool reg = false, regg = false;
void add(int x, int y, int z)
{
    tot++;
    Next[tot] = head[x];
    head[x] = tot;
    tree[tot] = y;
    val[tot] = z;
}
int spfa(int s)
{
    for (int i = 1; i <= n; i++)
        dis[i] = 1 << 30, visit[i] = false, flag[i] = 0;
    int t = 0, w = 1;
    x[1] = s;
    dis[s] = 0;
    visit[s] = true;
    flag[s] = 1;
    while (t < w)
    {
        t++;
        int u = x[t];
        visit[u] = false;
        if (dis[s] < 0)
        {
            reg = true;
            return 0;
        }
        for (int i = head[u]; i; i = Next[i])
        {
            int v = tree[i];
            if (dis[u] + val[i] < dis[v])
            {
                dis[v] = dis[u] + val[i];
                if (!visit[v])
                {
                    x[++w] = v, visit[v] = true;
                    flag[v]++;
                    if (flag[v] > n)
                    {
                        reg = true;
                        return 0;
                    }
                }
            }
        }
    }
}
int main()
{
    scanf("%d%d%d", &n, &m, &S);
    tot = 0;
    for (int i = 1; i <= m; i++)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z);
    }
    spfa(S);
    if (reg)
    {
        printf("-1\n");
    }
    else
    {
        memcpy(a, dis, sizeof(int) * (n + 1));
        for (int i = 1; i <= n; i++)
            if (a[i] == 1 << 30)
            {
                reg = false;
                spfa(i);
                if (reg)
                {
                    printf("-1\n");
                    regg = true;
                    break;
                }
            }
        if (!regg)
        {
            for (int i = 1; i <= n; i++)
                if (a[i] == 1 << 30)
                    printf("NoPath\n");
                else
                    printf("%d\n", a[i]);
        }
    }
    return 0;
}