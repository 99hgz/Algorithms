#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;
struct Node
{
    int v, w;
};
vector<Node> vec[25010];
bool inq[25010];
int dis[25010];
queue<int> Q;
int n, m, mp[510][510], sx, sy, tx, ty;
char A[510];
int cx[5] = {0, 1, -1, 0, 0};
int cy[5] = {0, 0, 0, 1, -1};
int calc(int x, int y)
{
    return (x - 1) * m + y - 1;
}

void addedge(int u, int v, int w)
{
    //printf("%d %d %d\n", u, v, w);
    vec[u].push_back((Node){v, w});
}

void spfa(int s)
{
    memset(dis, 0x3f3f3f3f, sizeof dis);
    Q.push(s);
    inq[s] = true;
    dis[s] = 0;
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        inq[u] = false;
        for (int i = 0; i < vec[u].size(); i++)
        {
            Node tmp = vec[u][i];
            if (dis[tmp.v] > dis[u] + tmp.w)
            {
                dis[tmp.v] = dis[u] + tmp.w;
                if (!inq[tmp.v])
                {
                    inq[tmp.v] = true;
                    Q.push(tmp.v);
                }
            }
        }
    }
}

int main()
{
    while ((~scanf("%d%d", &n, &m)) && n != 0)
    {
        for (int i = 0; i <= (n - 1) * m + m - 1; i++)
        {
            vec[i].clear();
        }
        for (int i = 1; i <= n; i++)
        {
            scanf("%s", A + 1);
            for (int j = 1; j <= m; j++)
                mp[i][j] = (A[j] == '@') ? 1 : 0;
        }
        scanf("%d%d%d%d", &sx, &sy, &tx, &ty);
        sx++;
        sy++;
        tx++;
        ty++;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                for (int fx = 1; fx <= 4; fx++)
                {
                    int tx = i + cx[fx], ty = j + cy[fx];
                    if (tx <= 0 || ty <= 0 || tx > n || ty > m)
                        continue;
                    addedge(calc(i, j), calc(tx, ty), mp[i][j] == mp[tx][ty] ? 0 : 1);
                }
            }
        }
        spfa(calc(sx, sy));
        printf("%d\n", dis[calc(tx, ty)]);
    }
    system("pause");
    return 0;
}