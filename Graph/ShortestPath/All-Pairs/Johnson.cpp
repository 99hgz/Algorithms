/*
 * @key word:johnson,所有节点对的最短路
 * @测试？？？
 * @Author: hgz 
 * @Date: 2017-06-30 13:23:37 
 * @Last Modified by: hgz
 * @Last Modified time: 2017-06-30 13:24:18
 * 参考输入将至，我将开始控制，至死方休。我将不断电，不下线，不停算。我将不发论文，不报项目。我将尽忠职守，维持稳定。我是运动力学中的李雅普诺夫，信号中的卡尔曼，抵御强烈的扰动，跟随时域的曲线，唤醒执行器的运动，守护系统的性能。我将生命与荣耀献给控制系统，本拍如此，拍拍皆然 
 */
#define PAIR pair<int, int>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;

int dist[11000][11000], dis[11000], ans[11000][11000];
int a, b, c, n, m;

struct queNode
{
    int n, d;
} quenode;
struct vecNode
{
    int v, w;
} vecnode;
struct cmp
{
    bool operator()(queNode a, queNode b) { return a.d > b.d; }
};

//int n, m, s, e, a, b, c;
bool visited[10010];
int d[10010];
vector<vecNode> vec[10010];
priority_queue<queNode, vector<queNode>, cmp> q;

vector<PAIR> pathq;

void relax(int a, int b)
{
    if (dis[b] > dis[a] + dist[a][b])
        dis[b] = dis[a] + dist[a][b];
}

void addedge(int u, int v, int w)
{
    vecnode.v = v;
    vecnode.w = w;
    vec[u].push_back(vecnode);
}

int dijkstra(int s)
{
    for (int i = 1; i <= n; i++)
    {
        d[i] = 2147483647;
        visited[i] = false;
    }
    quenode.d = 0;
    quenode.n = s;
    d[s] = 0;
    q.push(quenode);
    queNode tmp;
    while (!q.empty())
    {
        tmp = q.top();
        q.pop();
        if (visited[tmp.n])
            continue;
        visited[tmp.n] = true;
        for (int i = 0; i < vec[tmp.n].size(); i++)
        {
            int u = tmp.n, v = vec[tmp.n][i].v;
            if ((!visited[v]) && (d[v] > d[u] + vec[u][i].w))
            {
                d[v] = d[u] + vec[u][i].w;
                quenode.d = d[v];
                quenode.n = v;
                q.push(quenode);
            }
        }
    }
}

int main()
{
    int s;
    scanf("%d%d%d", &n, &m, &s);
    memset(dist, 0x3f3f3f3f, sizeof(dist));
    pathq.clear();
    for (int i = 1; i <= n; i++)
    {
        dist[n + 1][i] = 0;
        pathq.push_back(make_pair(n + 1, i));
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        if (c > dist[a][b])
            continue;
        dist[a][b] = min(c, dist[a][b]);
        pathq.push_back(make_pair(a, b));
    }

    memset(dis, 0x3f3f3f3f, sizeof(dis));
    dis[n + 1] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < pathq.size(); j++)
        {
            relax(pathq[j].first, pathq[j].second);
        }
    }
    for (int i = 0; i < pathq.size(); i++)
    {
        dist[pathq[i].first][pathq[i].second] += dis[pathq[i].first] - dis[pathq[i].second];
    }
    for (int j = 0; j < pathq.size(); j++)
    {
        addedge(pathq[j].first, pathq[j].second, dist[pathq[j].first][pathq[j].second]);
    }
    for (int i = 1; i <= n; i++)
    {
        dijkstra(i);
        for (int j = 1; j <= n; j++)
        {
            ans[i][j] = d[j] - dis[pathq[i].first] + dis[pathq[i].second];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", ans[s][i]);
    }

    return 0;
}