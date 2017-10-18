#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include <climits>
#include <queue>
#define pp pair<int, int>
using namespace std;
typedef long long ll;

int low[100010], dfn[100010], bh[100010], size[100010], ans, f[100010], in[100100];
int n, m, a, b, root, time1, scc, r, c, x[100010], y[100010], t[100010];
bool instack[100010];
vector<int> L[1000100], R[1000100];
map<pp, int> mp;
vector<int> vec[100010];
vector<int> newvec[100010];
struct EDGE
{
    int l, r;
};
int cx[9] = {0, -1, -1, -1, 0, 0, 1, 1, 1};
int cy[9] = {0, -1, 0, 1, 1, -1, -1, 0, 1};
vector<EDGE> edges;

stack<int> pointstack;

void addedge(int a, int b)
{
    //printf("addedge:%d %d\n", a, b);
    vec[a].push_back(b);
    edges.push_back((EDGE){a, b});
}

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
            tmp = pointstack.top();
            size[scc]++;
            instack[tmp] = false;
            pointstack.pop();
            bh[tmp] = scc;
            if (tmp == u)
            {
                break;
            }
        }
    }
}

int main()
{
    scanf("%d%d%d", &n, &r, &c);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d%d", &x[i], &y[i], &t[i]);
        L[x[i]].push_back(i);
        R[y[i]].push_back(i);
        mp[make_pair(x[i], y[i])] = i;
    }
    for (int i = 1; i <= n; i++)
    {
        if (t[i] == 1)
        {
            for (int j = 0; j < L[x[i]].size(); j++)
            {
                int v = L[x[i]][j];
                if (v == i)
                    continue;
                addedge(i, v);
            }
        }
        else if (t[i] == 2)
        {
            for (int j = 0; j < R[y[i]].size(); j++)
            {
                int v = R[y[i]][j];
                if (v == i)
                    continue;
                addedge(i, v);
            }
        }
        else
        {
            for (int j = 1; j <= 8; j++)
            {
                int v = mp[make_pair(x[i] + cx[j], y[i] + cy[j])];
                if (v == 0)
                    continue;
                addedge(i, v);
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (!dfn[i])
            tarjan(i, i);
    }

    int u, v;
    for (int i = 0; i < edges.size(); i++)
    {
        u = edges[i].l;
        v = edges[i].r;
        if (!bh[u] || !bh[v])
            continue;
        if (bh[u] != bh[v])
        {
            newvec[bh[u]].push_back(bh[v]);
            in[bh[v]]++;
        }
    }
    queue<int> Q2;

    //printf("%d\n", scc);
    for (int i = 1; i <= scc; i++)
    {
        if (in[i] == 0)
        {
            Q2.push(i);
            f[i] = size[i];
            ans = max(f[i], ans);
        }
    }
    while (!Q2.empty())
    {
        int u = Q2.front();
        Q2.pop();
        //printf("pop:%d\n", u);
        for (int i = 0; i < newvec[u].size(); i++)
        {
            int v = newvec[u][i];
            f[v] = max(f[u] + size[v], f[v]);
            in[v]--;
            if (in[v] == 0)
                Q2.push(v);
            ans = max(f[v], ans);
        }
    }
    printf("%d\n", ans);
    system("pause");
    return 0;
}