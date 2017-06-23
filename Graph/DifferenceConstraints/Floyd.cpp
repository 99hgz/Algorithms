/*
 * @key word:差分约束
 * @Author: hgz 
 * @Date: 2017-06-23 14:31:11 
 * @Last Modified by: hgz
 * @Last Modified time: 2017-06-23 14:32:10
 * 参考输入将至，我将开始控制，至死方休。我将不断电，不下线，不停算。我将不发论文，不报项目。我将尽忠职守，维持稳定。我是运动力学中的李雅普诺夫，信号中的卡尔曼，抵御强烈的扰动，跟随时域的曲线，唤醒执行器的运动，守护系统的性能。我将生命与荣耀献给控制系统，本拍如此，拍拍皆然 
 */
#define PAIR pair<int, int>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

int dist[1100][1100], dis[1100], psum[1100];
int a, b, c, n, m;

vector<PAIR> pathq;

void relax(int a, int b)
{
    if (dis[b] > dis[a] + dist[a][b])
        dis[b] = dis[a] + dist[a][b];
}

bool DAG()
{
    for (int j = 0; j < pathq.size(); j++)
    {
        int a = pathq[j].first;
        int b = pathq[j].second;
        if (dis[b] > dis[a] + dist[a][b])
            return true;
    }
    return false;
}

int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        memset(dist, 0x3f3f3f3f, sizeof(dist));
        psum[0] = 0;
        pathq.clear();
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &c);
            dist[i][i - 1] = min(0, dist[i][i - 1]);
            dist[i - 1][i] = min(c, dist[i - 1][i]);
            dist[n + 1][i] = min(0, dist[n + 1][i]);
            psum[i] = psum[i - 1] + c;
            pathq.push_back(make_pair(i - 1, i));
            pathq.push_back(make_pair(i, i - 1));
            pathq.push_back(make_pair(n + 1, i));
        }

        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d%d", &a, &b, &c);
            a--;
            dist[b][a] = min(-c, dist[b][a]);
            pathq.push_back(make_pair(b, a));
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
        if (DAG())
        {
            printf("Bad Estimations\n");
        }
        else
        {
            printf("%d\n", dis[n] - dis[0]);
        }
    }
    return 0;
}