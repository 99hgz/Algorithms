#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define inf 0x7fffffff
#define T 1001
using namespace std;
int head[1005], q[1005], h[1005];
int cnt, ans, mx, mid;
int n, k, mp[1005][1005];
struct data
{
    int to, next, v;
} e[500001];
void ins(int u, int v, int w)
{
    e[++cnt].to = v;
    e[cnt].next = head[u];
    e[cnt].v = w;
    head[u] = cnt;
}
void insert(int u, int v, int w)
{
    ins(u, v, w);
    ins(v, u, 0);
}
bool bfs()
{
    int t = 0, w = 1, i, now;
    memset(h, -1, sizeof(h));
    q[0] = 0;
    h[0] = 0;
    while (t < w)
    {
        now = q[t];
        t++;
        i = head[now];
        while (i)
        {
            if (e[i].v && h[e[i].to] == -1)
            {
                h[e[i].to] = h[now] + 1;
                q[w++] = e[i].to;
            }
            i = e[i].next;
        }
    }
    return h[T] == -1 ? 0 : 1;
}
int dfs(int x, int f)
{
    if (x == T)
        return f;
    int w, used = 0, i;
    i = head[x];
    while (i)
    {
        if (e[i].v && h[e[i].to] == h[x] + 1)
        {
            w = f - used;
            w = dfs(e[i].to, min(w, e[i].v));
            e[i].v -= w;
            e[i ^ 1].v += w;
            used += w;
            if (used == f)
                return f;
        }
        i = e[i].next;
    }
    if (!used)
        h[x] = -1;
    return used;
}
void dinic()
{
    while (bfs())
        ans += dfs(0, inf);
}
void ini()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        char ch[51];
        scanf("%s", ch);
        for (int j = 1; j <= n; j++)
            if (ch[j - 1] == 'Y')
                mp[i][j] = 1;
    }
}
void build()
{
    cnt = 1;
    memset(head, 0, sizeof(head));
    for (int i = 1; i <= n; i++)
        insert(0, i, mid);
    for (int i = 1; i <= n; i++)
        insert(i, i + 500, k);
    for (int i = 1; i <= n; i++)
        insert(n + i + 500, n + i, k);
    for (int i = 1; i <= n; i++)
        insert(n + i, T, mid);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (mp[i][j])
                insert(i, n + j, 1);
            else
                insert(i + 500, n + j + 500, 1);
}
int main()
{
    ini();
    int l = 0, r = 50;
    while (l <= r)
    {
        mid = (l + r) >> 1;
        build();
        ans = 0;
        dinic();
        printf("%d\n", ans);
        if (ans >= n * mid)
        {
            mx = mid;
            l = mid + 1;
        }
        else
            r = mid - 1;
    }
    printf("%d", mx);
    system("pause");
    return 0;
}