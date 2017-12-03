#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;
typedef long long ll;

int Q[2000], dep[2000];

int tot, Head[2000], cur[2000], Next[21000];
ll Val[21000], To[21000];
ll mp[100][100];
int n, m, S, T, u, v;

bool bfs()
{
    memset(dep, -1, sizeof dep);
    int t = 0, w = 1;
    Q[w] = S;
    dep[S] = 0;
    while (t != w)
    {
        t++;
        int u = Q[t];
        //printf("bfs:%d\n", u);
        for (int it = Head[u]; it; it = Next[it])
        {
            int v = To[it];
            if (Val[it] > 0 && dep[v] == -1)
            {
                dep[v] = dep[u] + 1;
                w++;
                Q[w] = v;
            }
        }
    }
    return dep[T] != -1;
}

ll dfs(int x, ll flow)
{
    //printf("%lld\n", flow);
    if (x == T)
        return flow;
    ll used = 0;
    for (int it = cur[x]; it; it = Next[it])
    {
        int v = To[it];
        if (dep[v] == dep[x] + 1)
        {
            ll tmp = dfs(v, min(Val[it], flow - used));
            used += tmp;
            Val[it] -= tmp;
            Val[it ^ 1] += tmp;
            cur[x] = it;
            if (used == flow)
                return flow;
        }
    }
    if (used == 0)
        dep[x] = -1;
    return used;
}

ll dinic()
{
    ll ans = 0;
    while (bfs())
    {
        for (int i = 1; i <= T; i++)
            cur[i] = Head[i];
        ans += dfs(S, 1LL << 60);
        //printf("%lld\n", ans);
    }
    return ans;
}

void addedge(int u, int v, ll flow)
{
    //printf("%d->%d\n", u, v);
    tot++;
    Next[tot] = Head[u];
    Head[u] = tot;
    Val[tot] = flow;
    To[tot] = v;
    tot++;
    Next[tot] = Head[v];
    Head[v] = tot;
    Val[tot] = 0;
    To[tot] = u;
}

int cx[9] = {0, 0, 0, 1, -1};
int cy[9] = {0, 1, -1, 0, 0};
int calc(int x, int y)
{
    return ((x - 1) * m + y);
}
ll Bsum, Bnum, Wnum, Wsum;
bool check(ll x)
{
    //return true;
    //printf("%lld\n", x);
    ll res = 0;
    memset(Head, 0, sizeof Head);
    tot = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (((i + j) & 1) == 0)
            {
                for (int fx = 1; fx <= 4; fx++)
                {
                    int tx = i + cx[fx], ty = j + cy[fx];
                    if (tx < 1 || tx > n || ty < 1 || ty > m)
                        continue;
                    addedge(calc(i, j), calc(tx, ty), 0x3f3f3f3f3f3f3f3f);
                }
                res += x - mp[i][j];
                addedge(S, calc(i, j), x - mp[i][j]);
            }
            else
            {
                addedge(calc(i, j), T, x - mp[i][j]);
            }
        }
    }
    //dinic();
    return res == dinic();
}

int main()
{
    int t;
    scanf("%d", &t);
    while (~scanf("%d%d", &n, &m))
    {
        Bnum = Bsum = Wnum = Wsum = 0;
        tot = 1;
        S = n * m + 1;
        T = n * m + 2;
        ll MIN = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
            {
                scanf("%lld", &mp[i][j]);
                MIN = max(MIN, mp[i][j]);
                if (((i + j) & 1) == 0)
                    Bnum++, Bsum += mp[i][j];
                else
                    Wnum++, Wsum += mp[i][j];
            }
        if (Bnum == Wnum)
        {
            ll l = MIN, r = 1500000000, ans = -1;
            while (l <= r)
            {
                ll mid = (l + r) >> 1;
                if (check(mid))
                {
                    r = mid - 1;
                    ans = mid;
                }
                else
                    l = mid + 1;
            }
            //printf("%lld\n", ans);
            printf("%lld\n", ans == -1 ? -1 : (ans * Wnum - Wsum));
        }
        else
        {
            ll k = (Wsum - Bsum) / (Wnum - Bnum);
            // printf("%lld\n", k);
            if (k < MIN)
                printf("-1\n");
            else
                printf("%lld\n", check(k) ? (k * Wnum - Wsum) : -1);
        }
        //printf("%lld", dinic());
    }
    system("pause");
    return 0;
}