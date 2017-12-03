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
        if (h == 7 * n)
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
                    if (t == 7 * n)
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

int q, MIN[100], MAX[100];

int main()
{
    tot = 1;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
    {
        MIN[i] = 1;
        MAX[i] = n;
    }
    S = n * 3 + 1;
    T = n * 3 + 2;
    for (int i = 1; i <= q; i++)
    {
        int t, l, r, v;
        scanf("%d%d%d%d", &t, &l, &r, &v);
        if (t == 1)
            for (int j = l; j <= r; j++)
                MIN[j] = max(MIN[j], v);
        else
            for (int j = l; j <= r; j++)
                MAX[j] = min(MAX[j], v);
    }

    for (int i = 1; i <= n; i++)
        addedge(S, i, 1, 0);

    for (int i = 1; i <= n; i++)
    {
        for (int j = MIN[i]; j <= MAX[i]; j++)
            addedge(i, n + j, 1, 0);
        if (MIN[i] > MAX[i])
        {
            printf("-1\n");
            return 0;
        }
        //printf("%d=%d~%d\n", i, MIN[i], MAX[i]);
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            addedge(n + i, 2 * n + j, 1, 0);

    for (int i = 1; i <= n; i++)
        addedge(2 * n + i, T, 0x3f3f3f3f, i * i - (i - 1) * (i - 1));

    printf("%d\n", mcf());
    system("pause");
    return 0;
}