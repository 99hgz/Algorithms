#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <climits>
#include <vector>
using namespace std;
typedef long long ll;
int n, m, a, b, len;
struct Road
{
    int to, len;
} road_tmp;
int i;
int f[1010][64];
vector<Road> road[1010];
bool vis[1010];

void find(int point)
{
    int a, b, c;
    for (c = 0; c < road[point].size(); c++)
    {
        Road tmp = road[point][c];
        if (!vis[tmp.to])
        {
            vis[tmp.to] = true;
            find(tmp.to);
            for (a = 0; a < 32; a++)
            {
                if (f[point][a] == 2139062143)
                    continue;
                for (b = 0; b < 32; b++)
                {
                    if (f[tmp.to][b] == 2139062143)
                        continue;
                    f[point][a | b] = min(f[point][a | b], f[point][a] + f[tmp.to][b] + tmp.len);
                }
            }
        }
    }
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        memset(vis, 0, sizeof(vis));
        memset(f, 0x7F, sizeof(f));
        for (i = 1; i <= n; i++)
        {
            scanf("%d", &m);
            f[i][1 << (m - 1)] = 0;
            f[i][0] = 0;
            road[i].clear();
        }
        for (i = 1; i <= n - 1; i++)
        {
            scanf("%d%d%d", &a, &b, &len);
            //Road road_tmp
            road_tmp.to = b;
            road_tmp.len = len;
            road[a].push_back(road_tmp);
            road_tmp.to = a;
            road[b].push_back(road_tmp);
        }
        find(1);
        int ans = INT_MAX;
        for (i = 1; i <= n; i++)
        {
            ans = min(ans, f[i][31]);
        }
        printf("%d\n", ans);
    }
    //system("pause");
    return 0;
}