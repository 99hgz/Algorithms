#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
typedef long long ll;

struct Node
{
    int v, w;
};
vector<Node> vec[200010];

int mpit[200010];
map<ll, int> mp[200010];
int u, v, w, n, k, ans;

void addedge(int u, int v, int w) { vec[u].push_back((Node){v, w}); }

void dfs(int u, int fa, int dep, ll tot)
{
    // printf("%d %d %d %d\n", u, fa, dep, tot);
    mpit[u] = u;
    for (auto P : vec[u])
    {
        int v = P.v;
        if (v != fa)
        {
            dfs(v, u, dep + 1, tot + P.w);
            int mpmax = mpit[u];
            int mpmin = mpit[v];
            if (mp[mpmin].size() > mp[mpmax].size())
                swap(mpmax, mpmin);
            map<ll, int>::iterator it = mp[mpmin].begin();
            while (it != mp[mpmin].end())
            {
                if ((it->second) == 0)
                {
                    it++;
                    continue;
                }
                ll rtot = it->first;
                ll ltot = k + 2 * tot - rtot;
                // printf("lca=%d ltot=%d\n", u, ltot);
                if (mp[mpmax][ltot] != 0)
                {
                    ans = min(ans, mp[mpmax][ltot] + (it->second) - 2 * dep);
                    //printf("update:%d %d %d\n", mp[mpmax][ltot], (it->second), dep);
                }
                it++;
            }
            it = mp[mpmin].begin();
            while (it != mp[mpmin].end())
            {
                if (mp[mpmax][it->first] == 0)
                    mp[mpmax][it->first] = (it->second);
                else
                    mp[mpmax][it->first] = min(mp[mpmax][it->first], (it->second));
                it++;
            }
            mpit[u] = mpmax;
            mp[mpmin].clear();
        }
    }
    if (mp[mpit[u]][tot + k] != 0)
    {
        //printf("update:%d %d\n", mp[mpit[u]][tot + k], dep);
        ans = min(ans, mp[mpit[u]][tot + k] - dep);
    }
    if (mp[mpit[u]][tot] == 0)
        mp[mpit[u]][tot] = dep;
    else
        mp[mpit[u]][tot] = min(mp[mpit[u]][tot], dep);
}

int main()
{
    freopen("F:/oj-data/ioi2011-race/data11.in", "r", stdin);
    //freopen("F:\oj-data\ioi2011-race\data1.out", "w", stdout);

    ans = 0x3f3f3f3f;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n - 1; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        addedge(u, v, w);
        addedge(v, u, w);
    }
    dfs(0, 0, 1, 0);
    printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
    ans = 1;
    return 0;
}