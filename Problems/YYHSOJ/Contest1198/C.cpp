/*
 * @key word:01背包
 * @已测试：http://www.yyhs.net.cn:801/JudgeOnline/problem.php?cid=1198&pid=2
 * @Author: hgz 
 * @Date: 2017-05-17 20:16:07 
 * @Last Modified by: hgz
 * @Last Modified time: 2017-05-17 20:21:14
 * 参考输入将至，我将开始控制，至死方休。我将不断电，不下线，不停算。我将不发论文，不报项目。我将尽忠职守，维持稳定。我是运动力学中的李雅普诺夫，信号中的卡尔曼，抵御强烈的扰动，跟随时域的曲线，唤醒执行器的运动，守护系统的性能。我将生命与荣耀献给控制系统，本拍如此，拍拍皆然 
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

struct Node
{
    int h;
    int v;
} node[400];
int dp[400];
int main()
{
    int t, n, m, l;

    scanf("%d%d", &m, &n);
    int i;
    for (i = 1; i <= n; i++)
        scanf("%d%d", &node[i].v, &node[i].h);
    for (i = 1; i <= n; i++)
    {
        for (l = m; l >= node[i].v; l--)
            dp[l] = max(dp[l], dp[l - node[i].v] + node[i].h);
    }
    printf("%d\n", dp[m]);
    //system("pause");
    return 0;
}
