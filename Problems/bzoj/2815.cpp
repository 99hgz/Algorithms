#include <cstdio>
#include <cstring>
#include <queue>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

queue<int> Q;
int indu[70000], deep[70000], father[70000][20], size[70000], n, tmp;
vector<int> vec[70000];
vector<int> fx[70000];
vector<int> tree[70000];
void TopologicalSorting()
{
    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        if (indu[i] == 0)
        {
            q.push(i);
        }
    }
    while (!q.empty())
    {
        int tmp = q.front();
        Q.push(tmp);
        q.pop();
        for (int i = 0; i < vec[tmp].size(); i++)
        {
            indu[vec[tmp][i]]--;
            if (indu[vec[tmp][i]] == 0)
                q.push(vec[tmp][i]);
        }
    }
}

int lca(int a, int b)
{
    //printf("lca:%d %d\n", a, b);
    if (deep[a] < deep[b])
        swap(a, b);
    int st2 = floor(log(deep[a] - 1) / log(2));
    for (int i = st2; i >= 0; i--)
        if (deep[a] - (1 << i) >= deep[b])
            a = father[a][i];
    if (a == b)
        return a;
    for (int i = st2; i >= 0; i--)
        if ((father[a][i] != -1) && (father[a][i] != father[b][i]))
        {
            a = father[a][i];
            b = father[b][i];
        }
    return father[a][0];
}

void build()
{
    father[n + 1][0] = n + 1;
    deep[n + 1] = 1;
    for (int i = 1; i <= n; i++)
    {
        int tmp = Q.front();
        //printf("%d\n", tmp);
        Q.pop();
        int LCA;
        if (fx[tmp].size() == 0)
        {
            LCA = n + 1;
        }
        else
        {
            LCA = fx[tmp][0];
            for (int j = 1; j < fx[tmp].size(); j++)
                LCA = lca(LCA, fx[tmp][j]);
        }
        tree[LCA].push_back(tmp);
        //printf("%d %d\n", LCA, tmp);
        father[tmp][0] = LCA;
        for (int j = 1; j <= 15; j++)
            father[tmp][j] = father[father[tmp][j - 1]][j - 1];
        deep[tmp] = deep[LCA] + 1;
    }
}

void dfs(int x)
{
    size[x] = 1;
    for (int i = 0; i < tree[x].size(); i++)
    {
        dfs(tree[x][i]);
        size[x] += size[tree[x][i]];
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &tmp);
        while (tmp != 0)
        {
            vec[tmp].push_back(i);
            fx[i].push_back(tmp);
            indu[i]++;
            scanf("%d", &tmp);
        }
    }
    TopologicalSorting();
    build();
    dfs(n + 1);
    for (int i = 1; i <= n; i++)
    {
        printf("%d\n", size[i] - 1);
    }
    system("pause");
    return 0;
}