/*
 * @key word:线性基
 * @已测试:http://www.lydsy.com/JudgeOnline/problem.php?id=2460
 * @Author: hgz 
 * @Date: 2017-04-27 12:51:06 
 * @Last Modified by: hgz
 * @Last Modified time: 2017-04-27 13:41:41
 * 参考输入将至，我将开始控制，至死方休。我将不断电，不下线，不停算。我将不发论文，不报项目。我将尽忠职守，维持稳定。我是运动力学中的李雅普诺夫，信号中的卡尔曼，抵御强烈的扰动，跟随时域的曲线，唤醒执行器的运动，守护系统的性能。我将生命与荣耀献给控制系统，本拍如此，拍拍皆然 
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
typedef long long ll;
using namespace std;
struct LB
{
    ll f[70];
    LB()
    {
        memset(f, 0, sizeof(f));
    }
    bool insert(ll val)
    {
        for (int i = 65; i >= 0; i--)
        {
            if ((val & (1LL << i)))
            {
                if ((!f[i]))
                {
                    f[i] = val;
                    break;
                }
                val ^= (f[i]);
            }
        }
        return val > 0;
    }
    ll max()
    {
        ll res = 0;
        for (int i = 65; i >= 0; i--)
        {
            if ((res ^ f[i]) > res)
            {
                res = (res ^ f[i]);
            }
        }
        return res;
    }
};
struct Node
{
    ll a;
    int b;
    bool operator<(const Node &d) const { return b == d.b ? a > d.a : b > d.b; }
} point[1010];

int main()
{
    LB list;
    ll ans = 0;
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld%d", &point[i].a, &point[i].b);
    sort(point + 1, point + n + 1);
    for (int i = 1; i <= n; i++)
    {
        if (list.insert(point[i].a))
        {
            ans += point[i].b;
        }
    }
    printf("%lld", ans);
    //system("pause");
}