#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;
typedef long long ll;

struct Quenode
{
    int x, y, d;
} quenode;
bool operator<(Quenode a, Quenode b)
{
    return a.d > b.d;
}
bool visited[1010][1010];
bool visited1[1010];
int d[1010][1010], dp[17][1 << 17];
int cx[5] = {0, 0, 0, 1, -1};
int cy[5] = {0, 1, -1, 0, 0};
int ans, n, m, k, sx, sy, tx, ty, a[1010][1010], x, y, num;
struct Node
{
    int x, y;
} spe[20];
int w[20][20], s[1919];
priority_queue<Quenode> q;
int sqr(int x)
{
    return x * x;
}
int dijkstra(int x, int y)
{
    memset(visited, 0, sizeof visited);
    memset(d, 0x7f7f7f7f, sizeof d);
    quenode.d = 0;
    quenode.x = x;
    quenode.y = y;
    d[x][y] = 0;
    q.push(quenode);
    Quenode tmp;
    while (!q.empty())
    {
        tmp = q.top();
        q.pop();
        if (visited[tmp.x][tmp.y])
            continue;
        visited[tmp.x][tmp.y] = true;
        for (int i = 1; i <= 4; i++)
        {
            int tx = tmp.x + cx[i], ty = tmp.y + cy[i];
            if (tx < 1 || ty < 1 || tx > n || ty > m)
                continue;
            if ((!visited[tx][ty]) && (d[tx][ty] > d[tmp.x][tmp.y] + sqr(a[tmp.x][tmp.y] - a[tx][ty])))
            {
                d[tx][ty] = d[tmp.x][tmp.y] + sqr(a[tmp.x][tmp.y] - a[tx][ty]);
                quenode.x = tx;
                quenode.y = ty;
                quenode.d = d[tx][ty];
                q.push(quenode);
            }
        }
    }
}

void relax(int &a, int b)
{
    if (a > b)
    {
        a = b;
    }
}

int main()
{
    freopen("escape.in", "r", stdin);
    freopen("escape.out", "w", stdout);

    scanf("%d%d%d%d%d%d%d", &n, &m, &k, &sx, &sy, &tx, &ty);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
    spe[num++] = (Node){sx, sy};
    s[0] = 0;
    for (int i = 1; i <= k; i++)
    {
        scanf("%d%d%d", &x, &y, &s[i]);
        spe[num++] = (Node){x, y};
    }
    spe[num++] = (Node){tx, ty};
    s[num - 1] = 0;
    for (int i = 0; i <= k + 1; i++)
    {
        dijkstra(spe[i].x, spe[i].y);
        for (int j = 0; j <= k + 1; j++)
        {
            w[i][j] = d[spe[j].x][spe[j].y];
            // printf("%d ", w[i][j]);
        }
        //printf("\n");
    }
    memset(dp, 0x7f7f7f7f, sizeof dp);
    for (int i = 1; i <= k; i++)
    {
        dp[i][1 << i - 1] = w[0][i] - s[i];
    }
    ans = w[0][k + 1];
    for (int i = 1; i < 1 << k; i++)
    {
        for (int j = 1; j <= k; j++)
        {
            if (i & (1 << j - 1))
            {
                for (int l = 1; l <= k; l++)
                {
                    if (!(i & (1 << l - 1)))
                        relax(dp[l][i | (1 << l - 1)], dp[j][i] + w[j][l] - s[l]);
                }
                ans = min(ans, dp[j][i] + w[j][k + 1]);
            }
        }
    }

    printf("%d\n", ans);
    //system("pause");
    return 0;
}