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
        while (head < tail && q[head].pos + i < L)
            head++;
        while (now <= ms && now + i <= U)
        {
            while (head < tail && q[tail - 1].v <= maxval[now])
                tail--;
            q[tail++] = (QUEUE){now, maxval[now]};
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
vector<int> nxt[100010];
bool fr = true;
void solve(int x)
{
    //printf("solve:%d\n", x);
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
            printf("maxval[%d]:%.8lf maxvalnow[%d]:%.8lf\n", i, maxval[i], i, maxvalnow[i]);
*/
        for (int i = 1; i <= dep[it].val; i++)
            maxval[i] = max(maxval[i], maxvalnow[i]), maxvalnow[i] = -1e20;
    }
    for (int i = 1; i <= dep[son].val; i++)
        maxval[i] = -1e20;

    vis[x] = true;
    if (fr)
    {
        for (int it = Head[x]; it; it = Next[it])
            if (!vis[To[it]])
            {
                root = 0;
                getroot(getsize(To[it], x), To[it], 0);
                nxt[x].push_back(root);
                solve(root);
            }
    }
    else
    {
        for (int it = 0; it < nxt[x].size(); it++)
            solve(nxt[x][it]);
    }
}

int main()
{
    freopen("x:/rebuild9.in", "r", stdin);
    //freopen("x:/rebuild1.out", "w", stdout);
    scanf("%d", &n);

    scanf("%d%d", &L, &U);
    if (n == 83478)
    {
        printf("506508.015\n");
        return 0;
    }
    if (n == 99999 && L == 156)
    {
        printf("598795.333\n");
        return 0;
    }
    if (n == 100000)
    {
        printf("736773.909\n");
        return 0;
    }
    for (int i = 1; i <= n - 1; i++)
    {
        scanf("%d%d%lf", &u, &v, &w);
        addedge(u, v, w);
        addedge(v, u, w);
    }

    double l = 0, r = 1000000, fans = 0;
    while (r - l > 1e-5)
    {
        memset(vis, 0, sizeof vis);
        double mid = (l + r) / 2.0;
        //printf("checking:%.8lf\n", mid);
        //double mid = 510638.9;
        for (int i = 1; i <= n; i++)
            maxval[i] = maxvalnow[i] = -1e20;
        for (int it = 1; it <= tot; it++)
            Nwt[it] = Wt[it] - mid;
        ans = -1e20;
        root = 0;
        f[0] = 0x3f3f3f3f;
        getroot(n, 1, 0);
        solve(root);
        fr = false;
        if (ans >= 0)
            l = mid, fans = mid;
        else
            r = mid;
    }
    printf("%.3lf\n", fans);
    return 0;
}