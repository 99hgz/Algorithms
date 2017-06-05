/*
 * @待更
 * @Author: hgz 
 * @Date: 2017-04-27 10:32:58 
 * @Last Modified by: hgz
 * @Last Modified time: 2017-04-27 18:50:29
 * 参考输入将至，我将开始控制，至死方休。我将不断电，不下线，不停算。我将不发论文，不报项目。我将尽忠职守，维持稳定。我是运动力学中的李雅普诺夫，信号中的卡尔曼，抵御强烈的扰动，跟随时域的曲线，唤醒执行器的运动，守护系统的性能。我将生命与荣耀献给控制系统，本拍如此，拍拍皆然 
 */
#define N 100;
int low[N], dfn[N];
bool instack[N];
stack<int> st;
struct LIST
{
    int v;
    LIST *next;
};
LIST *head[N] = {NULL};
void tarjan(int v)
{
    dfn[v] = low[v] = time++;
    st.push(v);
    instack[v] = true;
    for (LIST *p = head[v]; p != NULL; p = p->next)
    {
        if (!dfn[p->v])
        {
            tarjan(p->v);
            low[v] = min(low[v], low[p->v]);
        }
        else if (instack[p->v])
            low[v] = min(low[v], dfn[p->v]);
    }
    if (dfn[v] == low[v])
    {
        cout << "{ ";
        do
        {
            v = st.top();
            st.pop();
            instack[v] = false;
            cout << v << ' ';
        } while (dfn[v] != low[v]);
        cout << "}" << endl;
    }
}