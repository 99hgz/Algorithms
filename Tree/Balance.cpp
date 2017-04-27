/*
 * @key word: 树的重心
 * @已测试:POJ - 1655
 * @Author: hgz 
 * @Date: 2017-04-27 20:57:12 
 * @Last Modified by: hgz
 * @Last Modified time: 2017-04-27 20:57:35
 * 参考输入将至，我将开始控制，至死方休。我将不断电，不下线，不停算。我将不发论文，不报项目。我将尽忠职守，维持稳定。我是运动力学中的李雅普诺夫，信号中的卡尔曼，抵御强烈的扰动，跟随时域的曲线，唤醒执行器的运动，守护系统的性能。我将生命与荣耀献给控制系统，本拍如此，拍拍皆然 
 */
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
typedef long long ll;
using namespace std;
bool visited[20010];
int son[20010];
vector<int> tg[20010];
int n, ans, ansnode;

void work(int Node)
{
    visited[Node] = true;
    int balance = 0;
    for (int i = 0; i < tg[Node].size(); i++)
    {
        int u = tg[Node][i];
        if (!visited[u])
        {
            work(u);
            son[Node] += son[u] + 1;
            balance = max(balance, son[u] + 1);
        }
    }
    balance = max(balance, n - son[Node] - 1);
    if ((balance < ans) || ((balance == ans) && (Node < ansnode)))
    {
        ans = balance;
        ansnode = Node;
    }
}

int main()
{
    int t = 1;
    //t = 1;
    scanf("%d", &t);
    while (t--)
    {
        int a, b;
        ans = 1 << 29;
        ansnode = 1 << 29;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
        {
            tg[i].clear();
        }
        for (int i = 1; i <= n - 1; i++)
        {
            scanf("%d%d", &a, &b);
            tg[a].push_back(b);
            tg[b].push_back(a);
        }
        memset(visited, 0, sizeof(visited));
        memset(son, 0, sizeof(son));
        work(1);
        printf("%d %d\n", ansnode, ans);
    }
    //system("pause");
}