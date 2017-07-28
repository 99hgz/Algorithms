#define MAXN 6
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>
#include <queue>
using namespace std;
typedef long long ll;
int low[2010], dfn[2010], bh[2010], in[2010], size[2010];
int n, m, a, b, root, time1, scc, ans;
bool instack[2010];
vector<int> vec[2010];
vector<int> newvec[2010];
vector<int> ansset;
vector<int> lt[2010][2010];
int maxans;
struct EDGE
{
    int l, r;
};
vector<EDGE> edges;

stack<int> pointstack;

void addedge(int a, int b) { vec[a].push_back(b); }

void tarjan(int u, int fa)
{
    low[u] = dfn[u] = ++time1;
    pointstack.push(u);
    instack[u] = true;
    for (int i = 0; i < vec[u].size(); i++)
    {
        int v = vec[u][i];
        if (!dfn[v])
        {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
        }
        else if (instack[v])
        {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u])
    {
        scc++;
        int tmp;
        while (!pointstack.empty())
        {
            size[scc]++;
            tmp = pointstack.top();
            instack[tmp] = false;
            pointstack.pop();
            bh[tmp] = scc;
            if (tmp == u)
            {
                break;
            }
        }
        if (size[scc] > 1)
            ans += size[scc];
    }
}

void dfs(int start, int x, int size1, int nowsize)
{
    //printf("%d %d %d %d\n", start, x, size1, nowsize);
    if (lt[x][start].size())
    {
        if (size1 + nowsize > maxans)
        {
            maxans = size1 + nowsize;
            ansset.clear();
            for (int i = 0; i < lt[x][start].size(); i++)
            {
                ansset.push_back(lt[x][start][i]);
            }
        }
        else
        {
            if (size1 + nowsize == maxans)
                for (int i = 0; i < lt[x][start].size(); i++)
                {
                    ansset.push_back(lt[x][start][i]);
                }
        }
    }
    int tmp = size[x];
    if (size[x] == 1)
        tmp = 0;
    for (int i = 0; i < newvec[x].size(); i++)
    {
        dfs(start, newvec[x][i], size1 - tmp, nowsize + size[x]);
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    if (n > 1500)
    {
        printf("ERROR\n");
        return 0;
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &a, &b);
        addedge(a, b);
        edges.push_back((EDGE){a, b});
    }
    memset(low, 0, sizeof(low));
    memset(instack, false, sizeof(instack));
    scc = 0;
    time1 = 0;
    while (!pointstack.empty())
        pointstack.pop();

    for (int i = 1; i <= n; i++)
    {
        if (dfn[i] == 0)
        {
            tarjan(i, i);
        }
    }

    int u, v;
    maxans = ans;
    for (int i = 0; i < edges.size(); i++)
    {
        u = edges[i].l;
        v = edges[i].r;
        if (bh[u] != bh[v])
        {
            newvec[bh[u]].push_back(bh[v]);
            lt[bh[v]][bh[u]].push_back(i + 1);
            in[bh[v]]++;
        }
        else
        {
            ansset.push_back(i + 1);
        }
    }

    //printf("%d\n", scc);

    for (int i = 1; i <= scc; i++)
    {
        dfs(i, i, ans, 0);
    }
    printf("%d\n", maxans);
    printf("%d\n", ansset.size());
    sort(ansset.begin(), ansset.end());
    for (int i = 0; i < ansset.size() - 1; i++)
    {
        printf("%d ", ansset[i]);
    }
    if ((ansset.size() - 1) >= 0)
        printf("%d\n", ansset[ansset.size() - 1]);

    system("pause");
    return 0;
}