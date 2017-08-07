#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
ll n, a, b, c, ans, size[1000100];
struct Node
{
    ll to, w;
};
vector<Node> vec[1000100];

void addedge(ll a, ll b, ll c)
{
    vec[a].push_back((Node){b, c});
}

void dfs(int x, int fa)
{
    size[x] = 1;
    for (int i = 0; i < vec[x].size(); i++)
    {
        if (vec[x][i].to == fa)
            continue;
        dfs(vec[x][i].to, x);
        size[x] += size[vec[x][i].to];
        ans += (ll)(vec[x][i].w) * abs(n - 2 * size[vec[x][i].to]);
    }
}
.int main()
{
    scanf("%lld", &n);
    for (ll i = 1; i <= n - 1; i++)
    {
        scanf("%lld%lld%lld", &a, &b, &c);
        addedge(a, b, c);
        addedge(b, a, c);
    }
    dfs(1, 0);
    printf("%lld\n", ans);
    system("pause");
    return 0;
}