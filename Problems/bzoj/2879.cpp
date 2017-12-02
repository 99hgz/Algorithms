#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int sum[200000], f[200000];
int tot, tot1, Head[200000], Next[2000000], From[2000000], To[2000000], Cost[2000000], Val[2000000];
int FLOW, Q[50100], pre[200000], n, m, S, T, dis[200000];
bool inq[200000];

int mp[70][101];
void _addedge(int u, int v, int w, int c)
{
    tot1++;
    Next[tot1] = Head[u];
    Head[u] = tot1;
    From[tot1] = u;
    To[tot1] = v;
    Cost[tot1] = c;
    Val[tot1] = w;
}

void addedge(int u, int v, int w, int c)
{
    //printf("%d %d %d %d\n", u, v, w, c);
    _addedge(u, v, w, c);
    _addedge(v, u, 0, -c);
}

int calc()
{
    //printf("calc----\n");
    int res = 0, flow = 0x3f3f3f3f;
    for (int it = T; pre[it]; it = From[pre[it]])
    {
        flow = min(flow, Val[pre[it]]);
        //printf("%d->%d\n", From[pre[it]], To[pre[it]]);
    }
    FLOW += flow;
    for (int it = T; pre[it]; it = From[pre[it]])
    {
        Val[pre[it]] -= flow;
        Val[pre[it] ^ 1] += flow;
        res += flow * Cost[pre[it]];
    }
    int x = (From[pre[T]] - 1) / tot + 1, y = (x - 1) * tot + (++sum[x]);
    addedge(y, T, 1, 0);
    for (int i = 1; i <= n; i++)
        addedge(m * tot + i, y, 1, mp[i][x] * sum[x]);
    return res;
}

bool spfa()
{
    int h = 0, t = 1;
    Q[1] = S;
    memset(pre, 0, sizeof pre);
    memset(inq, 0, sizeof inq);
    memset(dis, 0x3f3f3f3f, sizeof dis);
    inq[S] = true;
    dis[S] = 0;
    while (t != h)
    {
        h++;
        if (h == T * 2)
            h = 1;
        int u = Q[h];
        inq[u] = false;
        for (int it = Head[u]; it; it = Next[it])
        {
            int v = To[it];
            if (Val[it] > 0 && dis[v] > dis[u] + Cost[it])
            {
                dis[v] = Cost[it] + dis[u];
                pre[v] = it;
                if (!inq[v])
                {
                    inq[v] = true;
                    t++;
                    if (t == T * 2)
                        t = 1;
                    Q[t] = v;
                }
            }
        }
    }
    return pre[T] != 0;
}

int mcf()
{
    int res = 0;
    while (spfa())
        res += calc();
    return res;
}
int main()
{
    tot1 = 1;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &f[i]);
        tot += f[i];
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &mp[i][j]);
    S = tot * m + n + 1;
    T = tot * m + n + 2;
    //printf("S=%d T=%d\n", S, T);
    for (int i = 1; i <= n; i++)
        addedge(S, tot * m + i, f[i], 0);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            addedge(tot * m + i, (j - 1) * tot + 1, 1, mp[i][j]);
    for (int i = 1; i <= m; i++)
        addedge((i - 1) * tot + 1, T, 1, 0), sum[i] = 1;
    printf("%d\n", mcf());
    system("pause");
    return 0;
}