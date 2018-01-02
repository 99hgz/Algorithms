#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;

int n, k, u, v;
double w;
int tot, Head[100010], To[200010], Next[200010];
double Wt[200010], Nwt[200010];
int size[100010], f[100010], root;
bool vis[100010];
struct QUEUE
{
    int pos;
    double v;
} q[100010];
double maxval[100010], maxvalnow[100010], ans;
int U, L;
void addedge(int u, int v, double w)
{
    tot++;
    Next[tot] = Head[u];
    Head[u] = tot;
    To[tot] = v;
    Wt[tot] = w;
}

void getroot(int treesize, int x, int fa)
{
    size[x] = 1, f[x] = 0;
    for (int it = Head[x]; it; it = Next[it])
        if ((To[it] != fa) && (!vis[To[it]]))
        {
            getroot(treesize, To[it], x);
            size[x] += size[To[it]];
            f[x] = max(f[x], size[To[it]]);
        }
    f[x] = max(f[x], treesize - size[x]);
    if (f[x] < f[root])
        root = x;
}

int getsize(int x, int fa)
{
    int res = 1;
    for (int it = Head[x]; it; it = Next[it])
        if ((To[it] != fa) && (!vis[To[it]]))
            res += getsize(To[it], x);
    return res;
}

int getdep(int x, int fa)
{
    int res = 0;
    for (int it = Head[x]; it; it = Next[it])
        if (!vis[To[it]] && To[it] != fa)
            res = max(res, getdep(To[it], x));
    return res + 1;
}

void work(int ms)
{
    int head = 1, tail = 1, now = 1;
    for (int i = ms; i >= 1; i--)
    {
        while (now <= ms && now + i <= U)
        {
            while (head < tail && q[tail - 1].v <= maxval[now])
            {
                //printf("pop:%.8lf\n", q[tail - 1].v);
                tail--;
            }
            while (head < tail && q[head].pos + now < L)
            {
                //printf("pop:%.8lf\n", q[head].pos);
                head++;
            }

            q[tail++] = (QUEUE){now, maxval[now]};
            //printf("insert queue %.8lf\n", maxval[now]);
            now++;
        }
        if (head < tail)
            ans = max(ans, q[head].v + maxvalnow[i]);
    }
}

void calc(int rt, int fa, int edgenum, double wsum)
{
    maxvalnow[edgenum] = max(maxvalnow[edgenum], wsum);
    for (int it = Head[rt]; it; it = Next[it])
    {
        int v = To[it];
        if (v != fa && !vis[v])
            calc(v, rt, edgenum + 1, wsum + Nwt[it]);
    }
}

struct Node
{
    int val, v;
    double w;
} dep[100010];

bool cmp(Node a, Node b)
{
    return a.val < b.val;
}

void solve(int x)
{
    int son = 0;
    for (int it = Head[x]; it; it = Next[it])
    {
        int v = To[it];
        if (!vis[v])
            dep[++son] = (Node){getdep(v, v), v, Nwt[it]};
    }

    sort(dep + 1, dep + 1 + son, cmp);

    for (int it = 1; it <= son; it++)
    {
        //printf("calcing: Root=%d v=%d w=%.8lf\n", x, dep[it].v, dep[it].w);
        calc(dep[it].v, x, 1, dep[it].w);
        work(dep[it].val);
        /*for (int i = 1; i <= dep[it].val; i++)
            printf("maxval[%d]:%.8lf maxvalnow[%d]:%.8lf\n", i, maxval[i], i, maxvalnow[i]);*/

        for (int i = 1; i <= dep[it].val; i++)
            maxval[i] = max(maxval[i], maxvalnow[i]), maxvalnow[i] = -1e20;
    }
    for (int i = 1; i <= dep[son].val; i++)
        maxval[i] = -1e20;

    vis[x] = true;
    for (int it = Head[x]; it; it = Next[it])
        if (!vis[To[it]])
            solve(To[it]);
}

int main()
{
    scanf("%d", &n);
    scanf("%d%d", &L, &U);
    for (int i = 1; i <= n - 1; i++)
    {
        scanf("%d%d%lf", &u, &v, &w);
        addedge(u, v, w);
        addedge(v, u, w);
    }

    double l = 0, r = 5, fans = 0;
    while (abs(r - l) > 1e-6)
    {
        memset(vis, 0, sizeof vis);
        double mid = (l + r) / 2.0;
        for (int i = 1; i <= n; i++)
            maxval[i] = maxvalnow[i] = -1e20;
        for (int it = 1; it <= tot; it++)
            Nwt[it] = Wt[it] - mid;
        ans = -1e20;
        root = 0;
        f[0] = 0x3f3f3f3f;
        getroot(n, 1, 0);
        solve(root);
        if (ans >= 0)
            l = mid, fans = mid;
        else
            r = mid;
    }
    printf("%.3lf\n", fans);
    system("pause");
    return 0;
}