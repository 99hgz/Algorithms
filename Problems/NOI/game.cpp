#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
using namespace std;
int n, d;
char ch[110];
const int maxn = 16005;
const int maxm = 200005;
int head[maxn], next[maxm], to[maxm];
int dfn[maxn], low[maxn], stk[maxn], scc[maxn], ind[maxn], vis[maxn];
int color[maxn], f[maxn];
int tot, top, cnt, id;
vector<int> dag[maxn];
void addedge(int u, int v)
{
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
}

void addedgecase1(int u, int v)
{
    printf("case1:%d %d\n", u, v);
    addedge(v ^ 1, u);
    addedge(u ^ 1, v);
}

void addedgecase2(int u, int v)
{
    printf("case2:%d %d\n", u, v);
    addedge(v ^ 1, u ^ 1);
    addedge(u, v);
}
void init()
{
    memset(head, -1, sizeof(head));
    memset(vis, 0, sizeof(vis));
    memset(dfn, 0, sizeof(dfn));
    memset(ind, 0, sizeof(ind));
    memset(color, 0, sizeof(color));
    tot = top = cnt = id = 0;
}
void tarjan(int v)
{
    dfn[v] = low[v] = ++cnt;
    vis[v] = 1;
    stk[++top] = v;
    for (int i = head[v]; i != -1; i = next[i])
    {
        int u = to[i];
        if (!dfn[u])
        {
            tarjan(u);
            low[v] = min(low[v], low[u]);
        }
        else if (vis[u])
            low[v] = min(low[v], dfn[u]);
    }
    if (low[v] == dfn[v])
    {
        id++;
        while (true)
        {
            int u = stk[top--];
            vis[u] = 0;
            scc[u] = id;
            if (u == v)
                break;
        }
    }
}
void buildDag(int n)
{
    for (int u = 0; u < n; u++)
        for (int i = head[u]; i != -1; i = next[i])
        {
            int v = to[i];
            if (scc[v] != scc[u])
            {
                dag[scc[v]].push_back(scc[u]);
                ind[scc[u]]++;
            }
        }
}
void topsort()
{
    queue<int> q;
    for (int i = 1; i <= id; i++)
        if (!ind[i])
            q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (!color[u])
            color[u] = 1, color[f[u]] = 2;
        for (int i = 0; i < (int)dag[u].size(); i++)
        {
            int v = dag[u][i];
            ind[v]--;
            if (!ind[v])
                q.push(v);
        }
    }
}
void solve(int n)
{
    for (int i = 0; i < n; i++)
        if (!dfn[i])
            tarjan(i);
    for (int i = 0; i < n; i += 2)
        if (scc[i] == scc[i + 1])
        {
            printf("NIE\n");
            return;
        }
        else
            f[scc[i]] = scc[i + 1], f[scc[i + 1]] = scc[i];
    for (int i = 0; i <= id; i++)
        dag[i].clear();
    buildDag(n);
    topsort();
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", color[scc[i]]);
    }
}
/*int main()  
{  
//     freopen("in.txt","r",stdin);  
    int n,m;  
    while(~scanf("%d%d",&n,&m))  
    {  
        init();  
        for(int i=0,a,b;i<m;i++)  
        {  
            scanf("%d%d",&a,&b);  
            a--,b--;  
            addEdage(a,b^1);  
            addEdage(b,a^1);  
        }  
        solve(n);  
    }  
    return 0;  
}  */
bool use(int i, char ch)
{
    if (ch == 'x')
        return true;
    if ((ch == 'c') && (i == 3))
        return false;
    if ((ch == 'b') && (i == 2))
        return false;
    if ((ch == 'a') && (i == 1))
        return false;
    return true;
}

int main()
{
    init();
    scanf("%d%d\n", &n, &d);
    for (int i = 1; i <= n; i++)
    {
        scanf("%c", &ch[i]);
    }
    for (int i = 1; i < n; i++)
    {
        if (ch[i] == 'x')
            continue;
        for (int j = 1; j <= 3; j++)
        {
            for (int k = 1; k <= 3; k++)
            {
                if (use(j, ch[i]) && use(k, ch[i + 1]))
                {
                    addedgecase1((i - 1) * 3 + j - 1, i * 3 + k - 1);
                }
            }
        }
    }
    int m, a, b;
    char ca, cb;
    scanf("%d\n", &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d %c %d %c", &a, &ca, &b, &cb);
        //printf("%c %c\n", ca, cb);
        addedgecase2((a - 1) * 3 + (ca - 'A'), (b - 1) * 3 + (cb - 'B'));
    } 
    n = 3 * n;
    solve(n);
    system("pause");
    return 0;
}