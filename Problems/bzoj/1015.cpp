#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
#define maxn 400100
int n, m, u, v, fa[maxn], k, blocks, ans[maxn], c[maxn];
vector<int> vec[maxn];
bool attacked[maxn];
int get_father(int x)
{
    return fa[x] == -1 ? x : fa[x] = get_father(fa[x]);
}

int uni(int u, int v)
{
    int fax = get_father(u);
    int fay = get_father(v);
    if (fax == fay)
        return 0;
    fa[fax] = fay;
    return 1;
}

void addedge(int u, int v)
{
    vec[u].push_back(v);
}

int main()
{
    memset(fa, -1, sizeof fa);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d %d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }
    scanf("%d", &k);
    for (int i = 1; i <= k; i++)
    {
        scanf("%d", &c[i]);
        attacked[c[i]] = true;
    }
    blocks = n;
    for (int i = 0; i < n; i++)
    {
        if (!attacked[i])
        {
            for (int j = 0; j < vec[i].size(); j++)
            {
                if (!attacked[vec[i][j]])
                    if (uni(i, vec[i][j]))
                    {
                        blocks--;
                    }
            }
        }
    }
    ans[k + 1] = blocks - k;
    for (int i = k; i >= 1; i--)
    {
        int u = c[i];
        for (int j = 0; j < vec[u].size(); j++)
        {

            if (!attacked[vec[u][j]])
                if (uni(u, vec[u][j]))
                {
                    blocks--;
                }
        }
        attacked[u] = false;
        ans[i] = blocks - (i - 1);
    }
    for (int i = 1; i <= k + 1; i++)
    {
        printf("%d\n", ans[i]);
    }
    system("pause");
    return 0;
}