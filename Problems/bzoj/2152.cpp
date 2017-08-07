#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

bool visited[20010];
struct Node
{
    int to, w;
};
vector<Node> vec[20010];
int f[20010][3];
int G, b, ans, fm, u, v, w, n;
void addedge(int u, int v, int w)
{
    vec[u].push_back((Node){v, w});
}
void dfs(int x)
{
    visited[x] = true;
    f[x][0] = 1;
    f[x][1] = f[x][2] = 0;
    for (int i = 0; i < vec[x].size(); i++)
    {
        int v = vec[x][i].to;
        if (!visited[v])
        {
            dfs(v);
            for (int j = 0; j < 3; j++)
                ans += f[v][j] * (f[x][(3 - (j + vec[x][i].w) % 3) % 3]);
            for (int j = 0; j < 3; j++)
                f[x][(j + vec[x][i].w) % 3] += f[v][j];
        }
    }
}

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        addedge(u, v, w);
        addedge(v, u, w);
    }
    dfs(1);
    ans = ans * 2 + n;
    fm = n * n;
    G = gcd(ans, fm);
    printf("%d/%d\n", ans / G, fm / G);
    system("pause");
    return 0;
}