#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxn = 20000 + 5;
const int maxv = 100000 + 5;

int N, M;
int w[maxn];
pair<int, int> edge[maxv];
vector<int> graph[maxn];
vector<int> regraph[maxn];
int dfn[maxn];
int low[maxn];
stack<int> sta;
bool InStack[maxn];
int belong[maxn];
int weight[maxn];
bool vis[maxn];
int idx, sccno, ans;

void init()
{
    for (int i = 0; i < maxn; i++)
    {
        graph[i].clear();
        regraph[i].clear();
    }
    while (!sta.empty())
        sta.pop();
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(weight, 0, sizeof(weight));
    memset(belong, 0, sizeof(belong));
    memset(vis, false, sizeof(vis));
    memset(InStack, false, sizeof(InStack));
    idx = 0;
    sccno = 0;
    ans = 0;
}

void input()
{
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++)
        scanf("%d", &w[i]);
    for (int i = 0; i < M; i++)
    {
        scanf("%d%d", &edge[i].first, &edge[i].second);
        graph[edge[i].first].push_back(edge[i].second);
    }
}

void tarjan(int u)
{
    low[u] = dfn[u] = ++idx;
    InStack[u] = true;
    sta.push(u);
    for (int i = 0; i < graph[u].size(); i++)
    {
        int v = graph[u][i];
        if (!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        if (InStack[v])
        {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u])
    {
        sccno++;
        while (!sta.empty())
        {
            int j = sta.top();
            sta.pop();
            InStack[j] = false;
            belong[j] = sccno;
            weight[sccno] += w[j];
            if (j == u)
                break;
        }
    }
}

void new_graph()
{
    for (int i = 0; i < M; i++)
    {
        int u = belong[edge[i].first];
        int v = belong[edge[i].second];
        if (u == 0 || v == 0)
            continue; //点1出发不能到达的点不需进入新图
        if (u != v)
            regraph[u].push_back(v);
    }
}

void dfs(int u, int sum)
{
    ans = max(ans, sum);
    for (int i = 0; i < regraph[u].size(); i++)
    {
        int v = regraph[u][i];
        if (!vis[v])
        {
            vis[v] = true;
            dfs(v, sum + weight[v]);
            vis[v] = false;
        }
    }
}

void solve()
{
    //    for(int i=1;i<=N;i++){
    //        if(!dfn[i]) tarjan(i);
    //    }
    tarjan(1);
    new_graph();
    dfs(belong[1], weight[belong[1]]);
    printf("%d\n", ans);
}

int main()
{
    init();
    input();
    solve();
    return 0;
}
