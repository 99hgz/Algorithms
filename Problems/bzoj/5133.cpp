#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int ed[210][210], n, m, id[210][210], cnt;
char st[210], mp[210][210];
ll mod = 1000000007;
bool err;
int vis[210][210];
ll a[310][310];
int cx[5] = {0, 1, 0, 0, -1};
int cy[5] = {0, 0, 1, -1, 0};

int calc(int x, int y)
{
    if (x < 1 || y < 1 || x > n || y > m)
        return 1;
    if (id[x][y] == 0)
        id[x][y] = ++cnt;
    return id[x][y];
}

int dfs(int x, int y, int ts)
{
    if (x < 1 || y < 1 || x > n || y > m)
        return 1;
    if (mp[x][y] == '.')
        return ed[x][y] = calc(x, y);
    if (ed[x][y] != -1)
        return ed[x][y];
    if (vis[x][y] == ts)
    {
        err = true;
        return 1;
    }
    vis[x][y] = ts;
    int res = 0;
    if (mp[x][y] == 'L')
        res = dfs(x, y - 1, ts);
    else if (mp[x][y] == 'R')
        res = dfs(x, y + 1, ts);
    else if (mp[x][y] == 'U')
        res = dfs(x - 1, y, ts);
    else
        res = dfs(x + 1, y, ts);
    return ed[x][y] = res;
}

inline ll pow(ll x, int y)
{
    ll ans = 1;
    while (y)
    {
        if (y & 1)
            ans = ans * x % mod;
        x = x * x % mod, y >>= 1;
    }
    return ans;
}

void mat()
{
    int p = cnt, d = 0;
    ll ans = 1, t = 0;
    for (int i = 2; i <= p; i++)
        for (int j = 2; j <= p; j++)
            a[i][j] = (a[i][j] + mod) % mod;
    for (int i = 2; i <= p; i++)
    {
        int j;
        for (j = i; j <= p; j++)
            if (a[i][j])
                break;
        if (j > p)
            continue;
        if (j != i)
        {
            d ^= 1;
            for (int k = i; k <= p; k++)
                swap(a[i][k], a[j][k]);
        }
        ans = ans * a[i][i] % mod;
        t = pow(a[i][i], mod - 2);
        for (int j = i; j <= p; j++)
            a[i][j] = a[i][j] * t % mod;
        for (int j = i + 1; j <= p; j++)
            for (int t = a[j][i], k = i; k <= p; k++)
                a[j][k] = (a[j][k] - a[i][k] * t % mod + mod) % mod;
    }
    for (int i = 2; i <= p; i++)
        ans = ans * a[i][i] % mod;
    if (d)
        ans = (mod - ans) % mod;
    printf("%lld\n", ans);
}

void work()
{
    cnt = 1;
    memset(ed, 0, sizeof ed);
    memset(id, 0, sizeof id);
    memset(vis, 0, sizeof vis);
    memset(a, 0, sizeof a);
    err = false;

    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", st + 1);
        for (int j = 1; j <= m; j++)
            mp[i][j] = st[j];
    }
    memset(ed, -1, sizeof ed);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (1)
            {
                dfs(i, j, i * m + j);
                if (err)
                {
                    printf("0\n");
                    //system("pause");
                    return;
                }
            }
    /*for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            printf("%d ", ed[i][j]);
        printf("%d\n");
    }*/
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (mp[i][j] == '.')
                for (int fx = 1; fx <= 4; fx++)
                {
                    int tx = i + cx[fx], ty = j + cy[fx];
                    a[ed[i][j]][ed[i][j]]++;
                    a[ed[i][j]][ed[tx][ty]]--;
                }
    /*for (int i = 1; i <= cnt; i++)
    {
        for (int j = 1; j <= cnt; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }*/
    mat();
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
        work();
    system("pause");
    return 0;
}