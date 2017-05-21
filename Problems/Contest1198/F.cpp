/*
 * @key word：LCS,最长公共子串
 * @已测试
 * @Author: hgz 
 * @Date: 2017-05-07 15:29:36 
 * @Last Modified by: hgz
 * @Last Modified time: 2017-05-20 14:49:44
 * @参考输入将至，我将开始控制，至死方休。我将不断电，不下线，不停算。我将不发论文，不报项目。我将尽忠职守，维持稳定。我是运动力学中的李雅普诺夫，信号中的卡尔曼，抵御强烈的扰动，跟随时域的曲线，唤醒执行器的运动，守护系统的性能。我将生命与荣耀献给控制系统，本拍如此，拍拍皆然
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
#define MAX(a, b) (a > b ? a : b)
const int MAXN = 2010;
int dp[MAXN][MAXN];
char a[MAXN], b[MAXN];
int main()
{
    scanf("%s%s", a + 1, b + 1);
    int i, j;
    for (i = 1; a[i]; i++)
    {
        for (j = 1; b[j]; j++)
        {
            if (a[i] == b[j])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = MAX(dp[i][j - 1], dp[i - 1][j]);
        }
    }
    printf("%d\n", dp[i - 1][j - 1]);
    return 0;
}