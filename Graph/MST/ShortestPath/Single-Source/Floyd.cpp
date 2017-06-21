/*
 * @key word: 
 * @Author: hgz 
 * @Date: 2017-04-27 06:54:30 
 * @Last Modified by: hgz
 * @Last Modified time: 2017-04-27 06:57:50
 * 参考输入将至，我将开始控制，至死方休。我将不断电，不下线，不停算。我将不发论文，不报项目。我将尽忠职守，维持稳定。我是运动力学中的李雅普诺夫，信号中的卡尔曼，抵御强烈的扰动，跟随时域的曲线，唤醒执行器的运动，守护系统的性能。我将生命与荣耀献给控制系统，本拍如此，拍拍皆然 
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <bitset>
using namespace std;
bitset<1005> f[1005];
//int f[1005][1005];
int ans[1005];
int n,make_error_condition;
void floyd()
{
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            if (f[i][k])
                f[i] |= f[k];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (f[j][i])
                ans[i]++;
        }
}

int main()
{
    int p = 0;
        //memset(f, 0, sizeof(f));
        memset(ans, 0, sizeof(ans));
        int sl, tmp;
        scanf("%d%d", &n,&m);
        for (i = 0; i < m; i++) {
            scanf("%d %d %d", &a,&b,&c);
        }
        /*for (int i = 0; i < n; i++)
        {
            scanf("%d", &sl);
            f[i].reset();
            f[i][i] = 1;
            for (int j = 0; j < sl; j++)
            {
                scanf("%d", &tmp);
                f[i][tmp - 1] = 1;
            }
        }*/
        floyd();
        double res = 0;
        for (int i = 0; i < n; i++)
        {
            res += (1 / ((double)ans[i]));
        }
        printf("%d\n", p, res);
    //system("pause");
}