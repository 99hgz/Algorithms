/*
 * @keyword:左偏树
 * @已测试:https://www.luogu.org/problem/show?pid=3377
 * @Author: hgz 
 * @Date: 2017-09-01 21:17:19 
 * @Last Modified by: hgz
 * @Last Modified time: 2017-09-01 21:18:25
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
    int val, fa, left, right;
} tree[100010];
int dist[100010];
int n, m, a[100010], cases, x, y;

int merge(int A, int B)
{
    if (!A || !B)
        return A + B;
    if ((tree[A].val > tree[B].val) || (tree[A].val == tree[B].val && A > B))
        swap(A, B);
    int tmp;
    tree[A].right = tmp = merge(tree[A].right, B);
    tree[tmp].fa = A;
    if (dist[tree[A].right] > dist[tree[A].left])
        swap(tree[A].right, tree[A].left);
    dist[A] = dist[tree[A].right] + 1;
    return A;
}

int get_father(int A)
{
    return tree[A].fa ? get_father(tree[A].fa) : A;
}

int erase(int A)
{
    tree[tree[A].left].fa = 0;
    tree[tree[A].right].fa = 0;
    merge(tree[A].left, tree[A].right);
    tree[A].val = -1;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &tree[i].val);
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &cases);
        if (cases == 1)
        {
            scanf("%d%d", &x, &y);
            if (tree[x].val != -1 && tree[y].val != -1)
            {
                int fax = get_father(x);
                int fay = get_father(y);
                if (fax != fay)
                {
                    merge(fax, fay);
                }
            }
        }
        else
        {
            scanf("%d", &x);
            int fax = get_father(x);
            if (tree[fax].val == -1)
                printf("-1\n");
            else
            {
                printf("%d\n", tree[fax].val);
                erase(fax);
            }
        }
    }
    system("pause");
    return 0;
}