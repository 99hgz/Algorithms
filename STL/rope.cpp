/*
 * @keyword: rope
 * @Author: hgz 
 * @Date: 2017-09-19 20:38:48 
 * @Last Modified by:   hgz 
 * @Last Modified time: 2017-09-19 20:38:48 
 * 参考输入将至，我将开始控制，至死方休。我将不断电，不下线，不停算。我将不发论文，不报项目。我将尽忠职守，维持稳定。我是运动力学中的李雅普诺夫，信号中的卡尔曼，抵御强烈的扰动，跟随时域的曲线，唤醒执行器的运动，守护系统的性能。我将生命与荣耀献给控制系统，本拍如此，拍拍皆然 
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <ext/rope>
using namespace std;
typedef long long ll;
using namespace __gnu_cxx;

crope a, b, tmp;
int n, k, now, size, len;
char str[2000000], rstr[2000000], S[2000000];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", S);
        if (S[0] == 'M')
        {
            scanf("%d", &k);
            now = k;
        }
        else if (S[0] == 'I')
        {
            scanf("%d", &k);
            int len = a.length();
            for (int i = 0; i < k; i++)
            {
                do
                {
                    str[i] = getchar();
                } while (str[i] == '\n');
                rstr[k - i - 1] = str[i];
            }
            str[k] = rstr[k] = '\0';
            a.insert(now, str);
            b.insert(len - now, rstr);
        }
        else if (S[0] == 'D')
        {
            scanf("%d", &k);
            int len = a.length();
            a.erase(now, k);
            b.erase(len - now - k, k);
        }
        else if (S[0] == 'R')
        {
            scanf("%d", &size);
            len = a.length();
            tmp = a.substr(now, size);
            a = a.substr(0, now) + b.substr(len - now - size, size) + a.substr(now + size, len - now - size);
            b = b.substr(0, len - now - size) + tmp + b.substr(len - now, now);
        }
        else if (S[0] == 'G')
        {
            putchar(a[now]);
            putchar('\n');
        }
        else if (S[0] == 'P')
        {
            now--;
        }
        else
        {
            now++;
        }
    }
    system("pause");
    return 0;
}