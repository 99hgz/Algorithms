#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int f[6010][2];
int a[6010], father[6010];
vector<int> vec[6010];
int n, l, k, rt;

void dfs(int x)
{
    f[x][1] = a[x];
    for (int i = 0; i < vec[x].size(); i++)
    {
        dfs(vec[x][i]);
        f[x][1] += f[vec[x][i]][0];
        f[x][0] += max(f[vec[x][i]][0], f[vec[x][i]][1]);
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n - 1; i++)
    {
        scanf("%d%d", &l, &k);
        vec[k].push_back(l);
        father[l] = k;
    }
    for (int i = 1; i <= n; i++)
    {
        if (father[i] == 0)
        {
            rt = i;
            break;
        }
    }
    dfs(rt);
    printf("%d\n", max(f[rt][0], f[rt][1]));
    system("pause");
    return 0;
}