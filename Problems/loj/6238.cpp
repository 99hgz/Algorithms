#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
typedef long long ll;
int du[500010], n, u, v;
vector<int> vec;
vector<int> e[500010];
int fa[500010];

void bfs()
{
    queue<int> Q;
    Q.push(2);
    fa[2] = 2;
    while (!Q.empty())
    {
        int tmp = Q.front();
        Q.pop();
        if (du[tmp] == 1)
            vec.push_back(tmp);
        for (auto i : e[tmp])
        {
            if (i != fa[tmp])
            {
                Q.push(i);
                fa[i] = tmp;
            }
        }
    }
}

void addedge(int u, int v)
{
    e[u].push_back(v);
    e[v].push_back(u);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++)
    {
        scanf("%d%d", &u, &v);
        addedge(u, v);
        du[u]++;
        du[v]++;
    }
    vec.push_back(0);
    bfs();
    int ans = vec.size() >> 1;
    printf("%d\n", ans);
    for (int i = 1; i <= ans; i++)
    {
        if (!(i == ans && (vec.size() % 2 == 0)))
            printf("%d %d\n", vec[i], vec[ans + i]);
        else
            printf("%d %d\n", vec[1], vec[ans]);
    }
    system("pause");
    return 0;
}