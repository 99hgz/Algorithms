#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>

using namespace std;
typedef long long ll;

struct PATH
{
    int dis, to;
};

struct NODE
{
    int s, t;
};

vector<PATH> path[1010];

ll dis[55][20005];
int cnt, s, k, a, b, c, n, m, i, mod, t;
ll T;
void spfa()
{
    memset(dis, 0x7f7f7f7f, sizeof(dis));
    queue<NODE> Q1;
    Q1.push((NODE){s, 0});
    dis[s][0] = 0;
    while (!Q1.empty())
    {
        NODE tmp = Q1.front();
        Q1.pop();
        int u = tmp.s;
        for (int i = 0; i < path[u].size(); i++)
        {
            int goton = path[u][i].to;
            int t2 = (tmp.t + path[u][i].dis) % mod;
            if (dis[goton][t2] > dis[u][tmp.t] + path[u][i].dis)
            {
                dis[goton][t2] = dis[u][tmp.t] + path[u][i].dis;
                Q1.push((NODE){goton, t2});
            }
        }
    }
}

void addpath(int a, int b, int c)
{
    PATH tmp;
    tmp.to = b;
    tmp.dis = c;
    path[a].push_back(tmp);
    if ((a == 1) && (c < mod))
        mod = c;
}

int main()
{
    scanf("%d", &t);
    while (t--)
    {
        for (int i = 1; i <= n; i++)
        {
            path[i].clear();
        }
        mod = 0x7f7f7f7f;
        scanf("%d%d%lld", &n, &m, &T);
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d%d", &a, &b, &c);
            a++, b++;
            addpath(a, b, c);
            addpath(b, a, c);
        }
        if (mod == 0x7f7f7f7f)
            printf("Impossible\n");
        else
        {
            mod *= 2;
            s = 1;
            spfa();
            if (dis[n][T % mod] <= T)
                printf("Possible\n");
            else
                printf("Impossible\n");
        }
    }
    system("pause");
    return 0;
}