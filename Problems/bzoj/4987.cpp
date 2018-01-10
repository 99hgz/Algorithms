#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

int n, k, u, v, w;
struct PATH
{
    int v, w;
};
vector<PATH> vec[10010];
int size[10010], f[10010], root, ans;
vector<int> alldis;
bool vis[10010];

void addedge(int u, int v, int w)
{
    vec[u].push_back((PATH){v, w});
}

void getroot(int treesize, int x, int fa)
{
    size[x] = 1, f[x] = 0;
    for (auto P : vec[x])
        if ((P.v != fa) && (!vis[P.v]))
        {
            getroot(treesize, P.v, x);
            size[x] += size[P.v];
            f[x] = max(f[x], size[P.v]);
        }
    f[x] = max(f[x], treesize - size[x]);
    if (f[x] < f[root])
        root = x;
}

int getsize(int x, int fa)
{
    int res = 1;
    for (auto P : vec[x])
        if ((P.v != fa) && (!vis[P.v]))
            res += getsize(P.v, x);
    return res;
}

void solve(int x)
{

    for (auto P : vec[x])
    {
        if (!vis[P.v])
        {
            work(P.v, x);
            for (int i = 1; i <= n; i++)
                }
    }

    vis[x] = true;
    for (auto P : vec[x])
        if (!vis[P.v])
        {
            ans -= calc(P.v, P.w);
            root = 0;
            getroot(getsize(P.v, x), P.v, 0);
            solve(root);
        }
}

int main()
{
    while (1)
    {
        scanf("%d%d", &n, &k);
        if (n == 0)
            break;
        for (int i = 1; i <= n; i++)
            vec[i].clear();
        memset(size, 0, sizeof size);
        memset(f, 0, sizeof f);
        memset(vis, 0, sizeof vis);
        ans = 0;
        alldis.clear();

        for (int i = 1; i <= n - 1; i++)
        {
            scanf("%d%d%d", &u, &v, &w);
            addedge(u, v, w);
            addedge(v, u, w);
        }
        root = 0;
        f[0] = 0x3f3f3f3f;
        getroot(n, 1, 0);
        solve(root);
        printf("%d\n", ans);
    }
    system("pause");
    return 0;
}