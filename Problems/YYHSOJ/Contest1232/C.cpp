#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
ll n, m, p[100], ans;
void dfs(ll dep, ll pos, ll times, ll plus)
{
    //prllf("%d %d %d %d\n", dep, pos, times, plus);
    if (dep != 0)
        ans += plus * (m / times);
    for (ll i = pos + 1; i <= n; i++)
        dfs(dep + 1, i, times * p[i], plus * -1);
}

int main()
{
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &p[i]);
    dfs(0, 0, 1, -1);
    printf("%lld\n", ans);
    system("pause");
    return 0;
}