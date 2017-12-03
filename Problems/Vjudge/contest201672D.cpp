#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

int tot, Head[5010], Next[100010], From[100010], To[100010], Val[100010];
int FLOW, Q[50100], pre[5010], n, m, S, T;
bool inq[5010];
double Cost[100010], dis[100010];
double sqr(double x)
{
    return x * x;
}

void _addedge(int u, int v, int w, double c)
{
    tot++;
    Next[tot] = Head[u];
    Head[u] = tot;
    From[tot] = u;
    To[tot] = v;
    Cost[tot] = c;
    Val[tot] = w;
}

void addedge(int u, int v, int w, double c)
{
    //printf("%d->%d %d %.8lf\n", u, v, w, c);
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
        //res += flow * Cost[pre[it]];
    }
    return res;
}

bool spfa()
{
    int h = 0, t = 1;
    Q[1] = S;
    memset(pre, 0, sizeof pre);
    memset(inq, 0, sizeof inq);
    for (int i = 1; i <= T; i++)
    {
        dis[i] = 10000000;
    }
    //memset(dis, 0x3f3f3f3f, sizeof dis);
    inq[S] = true;
    dis[S] = 0;
    while (t != h)
    {
        h++;
        if (h == 5 * n)
            h = 1;
        int u = Q[h];
        inq[u] = false;
        for (int it = Head[u]; it; it = Next[it])
        {
            int v = To[it];
            if (Val[it] > 0 && (dis[v] - (dis[u] + Cost[it]) > 1e-6))
            {
                dis[v] = Cost[it] + dis[u];
                pre[v] = it;
                if (!inq[v])
                {
                    inq[v] = true;
                    t++;
                    if (t == 5 * n)
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

double x[110], y[110];
int id[210];
int main()
{
    tot = 1;
    scanf("%d", &n);
    S = 2 * n + 1;
    T = 2 * n + 2;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lf%lf", &x[i], &y[i]);
        addedge(S, i, 1, 1);
    }
    for (int i = 1; i <= n; i++)
    {
        double xx, yy;
        scanf("%lf%lf", &xx, &yy);
        for (int j = 1; j <= n; j++)
            addedge(j, i + n, 1, sqrt(sqr(xx - x[j]) + sqr(yy - y[j])));
        addedge(i + n, T, 1, 1);
    }
    mcf();
    for (int i = 1; i <= n; i++)
    {
        for (int it = Head[i]; it; it = Next[it])
        {
            if ((it & 1) == 0 && Val[it] == 0)
                id[i] = To[it] - n;
        }
        printf("%d\n", id[i]);
    }

    system("pause");
    return 0;
}