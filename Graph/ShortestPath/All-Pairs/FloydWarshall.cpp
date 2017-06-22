/*
 * @key word:Floyd,全源最短路
 * @已测试:HDU 2544
 * @Author: hgz 
 * @Date: 2017-06-22 14:51:29 
 * @Last Modified by: hgz
 * @Last Modified time: 2017-06-22 14:51:51
 * 参考输入将至，我将开始控制，至死方休。我将不断电，不下线，不停算。我将不发论文，不报项目。我将尽忠职守，维持稳定。我是运动力学中的李雅普诺夫，信号中的卡尔曼，抵御强烈的扰动，跟随时域的曲线，唤醒执行器的运动，守护系统的性能。我将生命与荣耀献给控制系统，本拍如此，拍拍皆然 
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, m, i, j, k, a, b, c;
int dist[110][110];
int main()
{
    while ((scanf("%d%d", &n, &m)) && (n != 0) && (m != 0))
    {

        memset(dist, 0x3f3f3f3f, sizeof(dist));
        for (int i = 1; i <= n; i++)
        {
            dist[i][i] = 0;
        }
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d%d", &a, &b, &c);
            dist[a][b] = c;
            dist[b][a] = c;
        }
        for (int k = 1; k <= n; k++)
        {
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    if (dist[i][j] > dist[i][k] + dist[k][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
        printf("%d\n", dist[1][n]);
    }
    system("pause");
    return 0;
}