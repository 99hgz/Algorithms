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

void getdeep(int x, int fa, int dep)
{
    alldis.push_back(dep);
    for (auto P : vec[x])
        if ((!vis[P.v]) && (P.v != fa))
            getdeep(P.v, x, dep + P.w);
}

int calc(int rt, int dep)
{
    alldis.clear();
    getdeep(rt, 0, dep);
    int res = 0;
    sort(alldis.begin(), alldis.end());
    /*printf("calc:%d %d\n", rt, dep);
    for (auto v : alldis)
        printf("%d ", v);
    printf("\n");*/
    for (int l = 0, r = alldis.size() - 1; l < r;)
        if (alldis[l] + alldis[r] <= k)
        {
            res += r - l;
            l++;
        }
        else
            r--;
    return res;
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
    //printf("solve:%d\n", x);
    ans += calc(x, 0);
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
    //freopen("F:/oj-data/poj1741_tree/data10.in", "r", stdin);
    //freopen("F:\oj-data\poj1741_tree\data10.out", "w", stdout);

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