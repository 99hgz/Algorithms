/*
 * @keyword：2SAT
 * @已测试：http://acm.hit.edu.cn/hoj/problem/view?id=1917
 * @Author: hgz 
 * @Date: 2017-08-29 18:26:55 
 * @Last Modified by: hgz
 * @Last Modified time: 2017-08-29 18:31:47
 * 参考输入将至，我将开始控制，至死方休。我将不断电，不下线，不停算。我将不发论文，不报项目。我将尽忠职守，维持稳定。我是运动力学中的李雅普诺夫，信号中的卡尔曼，抵御强烈的扰动，跟随时域的曲线，唤醒执行器的运动，守护系统的性能。我将生命与荣耀献给控制系统，本拍如此，拍拍皆然 
 构图
　　更具体的后面再说
 缩点
　　Tarjan算法缩点，将所有的边反过来（ 为什么？后面有嗯 ）
 判可行
　　枚举集合的两个元素，看其是否处于不同的块内，若否的话则给出不可行信息
 记录矛盾
　　这里所说的矛盾不是题中给出的两个人之间有仇恨，那样的边是实际存在，我们这里说的矛盾是指若两个块分别含有两个对立节点，也就是说一个集合的两个元素分布在了两个不同的块中，那么这两个块就是矛盾的，即不可能同时被选择，这样一种矛盾关系是不存在于边中的，是不依赖于输入的数据的，我们要找到与一个块对立的块，并把它们保存下来。
 拓扑排序
 　将缩点后的图进行拓扑排序（排的是块而不是节点）
 构造方案
　　按照拓扑序列的顺序，依次访问所有块，若一个块未被标记，将其标记为“选择”，不传递“选择”标记，将被选块的对立块标记为“不选择”，将其“不选择”标记沿着边正向传递。（ 不是逆着边么？哼，图已经被反过来了，你到底有没有认真看呐！囧 ）

*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
typedef long long ll;
stack<int> pointstack;
vector<int> DAG[20010];
vector<int> vec[20010];
int indu[20010], color[20010], u, v, n, m, dfn[20010], low[20010], scc[20010], f[20010], time1, sccnum;
bool instack[20010];
void tarjan(int u, int fa)
{
    low[u] = dfn[u] = ++time1;
    pointstack.push(u);
    instack[u] = true;
    for (int i = 0; i < vec[u].size(); i++)
    {
        int v = vec[u][i];
        if (dfn[v] == -1)
        {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
        }
        else if (instack[v])
        {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u])
    {
        sccnum++;
        int tmp;
        while (!pointstack.empty())
        {
            tmp = pointstack.top();
            instack[tmp] = false;
            pointstack.pop();
            scc[tmp] = sccnum;
            if (tmp == u)
            {
                break;
            }
        }
    }
}

void addedge2DAG(int u, int v)
{
    DAG[v].push_back(u);
    indu[u]++;
}

void addedge(int u, int v)
{
    vec[u].push_back(v);
}

void TopologicalSorting()
{
    queue<int> q;
    for (int i = 1; i <= sccnum; i++)
    {
        if (indu[i] == 0)
        {
            q.push(i);
        }
    }
    while (!q.empty())
    {
        int tmp = q.front();
        q.pop();
        if (!color[tmp])
            color[tmp] = 1, color[f[tmp]] = 2;
        for (int i = 0; i < DAG[tmp].size(); i++)
        {
            indu[DAG[tmp][i]]--;
            if (indu[DAG[tmp][i]] == 0)
                q.push(DAG[tmp][i]);
        }
    }
}

int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        memset(dfn, -1, sizeof(dfn));
        memset(color, 0, sizeof(color));
        memset(indu, 0, sizeof(indu));
        memset(f, 0, sizeof(f));
        memset(scc, 0, sizeof(scc));
        memset(instack, 0, sizeof(instack));
        memset(low, 0, sizeof(low));
        sccnum = 0;
        while (!pointstack.empty())
            pointstack.pop();
        time1 = 0;
        for (int i = 0; i <= 2 * n; i++)
        {
            DAG[i].clear();
            vec[i].clear();
        }
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d", &u, &v);
            u--, v--;
            addedge(u, v ^ 1);
            addedge(v, u ^ 1);
        }
        //缩点
        bool flag = false;
        for (int i = 0; i < 2 * n; i++)
        {
            if (dfn[i] == -1)
                tarjan(i, i);
        }
        //判断有解
        for (int i = 0; i < 2 * n; i += 2)
        {
            if (scc[i] == scc[i + 1])
            {
                printf("NIE\n");

                flag = true;
                break;
            }
            else
            {
                f[scc[i]] = scc[i + 1];
                f[scc[i + 1]] = scc[i];
            }
        }
        if (flag)
            continue;
        //缩点连边
        for (int i = 0; i < 2 * n; i++)
        {
            for (int j = 0; j < vec[i].size(); j++)
            {
                if (scc[i] != scc[vec[i][j]])
                {
                    addedge2DAG(scc[i], scc[vec[i][j]]);
                }
            }
        }
        //拓扑排序
        TopologicalSorting();

        for (int i = 0; i < 2 * n; i += 2)
        {
            if (color[scc[i]] == 1)
            {
                printf("%d\n", i + 1);
            }
            else
            {
                printf("%d\n", i + 2);
            }
        }
    }
    system("pause");
    return 0;
}