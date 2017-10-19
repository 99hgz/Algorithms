#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
queue<int> Q;
double speed[1010];
bool vis[1010];
struct Node
{
    int v;
    double bl;
};
vector<Node> vec[1010];
int n, m, u, v, x, y, tot;
bool flag;
bool eq(double a, double b)
{
    return abs(a - b) <= 1e-6;
}

bool check(int x)
{
    while (!Q.empty())
    {
        Q.pop();
    }
    Q.push(x);
    speed[x] = 1;
    while (!Q.empty())
    {
        int tmp = Q.front();
        Q.pop();
        vis[tmp] = true;
        for (int i = 0; i < vec[tmp].size(); i++)
        {
            int v = vec[tmp][i].v;
            if (speed[v] == 0)
                speed[v] = speed[tmp] * vec[tmp][i].bl;
            else if (!eq(speed[tmp] * vec[tmp][i].bl, speed[v]))
                return false;
            if (!vis[v])
                Q.push(v);
        }
    }
    return true;
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        tot++;
        memset(vis, 0, sizeof vis);
        memset(speed, 0, sizeof speed);
        for (int i = 1; i <= n; i++)
        {
            vec[i].clear();
        }
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d%d%d", &u, &v, &x, &y);
            vec[u].push_back((Node){v, (double)x / (double)y});
            vec[v].push_back((Node){u, (double)y / (double)x});
        }
        flag = false;
        for (int i = 1; i <= n; i++)
        {
            if (!vis[i])
                if (!check(i))
                {
                    printf("Case #%d: No\n", tot);
                    flag = true;
                    break;
                }
        }
        if (!flag)
            printf("Case #%d: Yes\n", tot);
    }
    system("pause");
    return 0;
}