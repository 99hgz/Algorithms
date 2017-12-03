#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int tot, Head[5010], Next[100010], From[100010], To[100010], Cost[100010], Val[100010];
int FLOW, Q[50100], pre[5010], n, m, S, T, dis[5010];
bool inq[5010];

void _addedge(int u, int v, int w, int c)
{
    tot++;
    Next[tot] = Head[u];
    Head[u] = tot;
    From[tot] = u;
    To[tot] = v;
    Cost[tot] = c;
    Val[tot] = w;
}

void addedge(int u, int v, int w, int c)
{
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
        if (h == T)
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
                    if (t == T)
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
int MIN[10010];
int main()
{

    tot = 1;
    scanf("%d%d", &n, &m);
    S = n + 2;
    T = n + 3;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &MIN[i]);
    }
    for (int i = 1; i <= m; i++)
    {
        int s, t, c;
        scanf("%d%d%d", &s, &t, &c);
        addedge(s, t + 1, 0x3f3f3f3f, c);
    }
    for (int i = 1; i <= n + 1; i++)
    {
        int c = MIN[i] - MIN[i - 1];
        if (c > 0)
            addedge(S, i, c, 0);
        else
            addedge(i, T, -c, 0);
    }
    for (int i = 1; i <= n; i++)
    {
        addedge(i + 1, i, 0x3f3f3f3f, 0);
    }
    printf("%d\n", mcf());
    system("pause");
    return 0;
}