/*
 * @key word:树链剖分
 * @已测试:BZOJ 1036
 * @Author: hgz 
 * @Date: 2017-07-02 11:09:26 
 * @Last Modified by: hgz
 * @Last Modified time: 2017-07-02 11:10:05
 * 参考输入将至，我将开始控制，至死方休。我将不断电，不下线，不停算。我将不发论文，不报项目。我将尽忠职守，维持稳定。我是运动力学中的李雅普诺夫，信号中的卡尔曼，抵御强烈的扰动，跟随时域的曲线，唤醒执行器的运动，守护系统的性能。我将生命与荣耀献给控制系统，本拍如此，拍拍皆然 
 */
#define MAXN 30010
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef long long ll;

struct typeofmax
{
    int num, bh;
};
int hson[MAXN], hasson[MAXN], dep[MAXN], tid[MAXN], v[MAXN], top[MAXN], parent[MAXN], number[MAXN];
int sum[MAXN * 4], Max[MAXN * 4];
bool visited[MAXN];
vector<int> path[MAXN];

int n, a, b, m, global_ans_sum, global_ans_max, totaltid;

void addedge(int a, int b)
{
    path[a].push_back(b);
}

void dfs(int point, int deep, int fa)
{
    parent[point] = fa;
    dep[point] = deep;
    visited[point] = true;
    typeofmax maxson;
    maxson.num = -40000;
    maxson.bh = point;
    for (int i = 0; i < path[point].size(); i++)
    {
        int ngoto = path[point][i];
        if (!visited[ngoto])
        {
            dfs(ngoto, deep + 1, point);
            hasson[point] += hasson[ngoto] + 1;
            if ((hasson[ngoto] + 1) > maxson.num)
            {
                maxson.num = hasson[ngoto] + 1;
                maxson.bh = ngoto;
            }
        }
    }
    hson[point] = maxson.bh;
    visited[point] = false;
}

void dfs1(int point, int pointtop)
{
    if (visited[point])
        return;
    tid[point] = ++totaltid;
    number[totaltid] = point;
    top[point] = pointtop;
    visited[point] = true;
    dfs1(hson[point], pointtop);
    for (int i = 0; i < path[point].size(); i++)
    {
        int ngoto = path[point][i];
        if (!visited[ngoto])
        {
            if (hson[point] != ngoto)
            {
                dfs1(ngoto, ngoto);
            }
        }
    }
    visited[point] = false;
}

void up(int bh)
{
    Max[bh] = max(Max[bh * 2], Max[bh * 2 + 1]);
    sum[bh] = sum[bh * 2] + sum[bh * 2 + 1];
}

void build_tree(int bh, int l, int r)
{
    if (l == r)
    {
        Max[bh] = sum[bh] = v[number[l]];
        return;
    }
    build_tree(bh * 2, l, (l + r) >> 1);
    build_tree(bh * 2 + 1, ((l + r) >> 1) + 1, r);
    up(bh);
}

void change_tree(int bh, int u, int v1, int l, int r, int G)
{
    if (u == l && v1 == r)
    {
        v[number[l]] = G;
        Max[bh] = sum[bh] = G;
        return;
    }
    int mid = (u + v1) >> 1;
    if (r <= mid)
    {
        change_tree(bh * 2, u, mid, l, r, G);
    }
    else if (l > mid)
    {
        change_tree(bh * 2 + 1, mid + 1, v1, l, r, G);
    }
    else
    {
        change_tree(bh * 2, u, mid, l, mid, G);
        change_tree(bh * 2 + 1, mid + 1, v1, mid + 1, r, G);
    }
    up(bh);
}

void query_tree(int bh, int u, int v, int l, int r)
{
    if (l > r)
        swap(l, r);
    if (u == l && v == r)
    {
        global_ans_sum += sum[bh];
        global_ans_max = max(global_ans_max, Max[bh]);
        return;
    }
    int mid = (u + v) >> 1;
    if (r <= mid)
    {
        query_tree(bh * 2, u, mid, l, r);
    }
    else if (l > mid)
    {
        query_tree(bh * 2 + 1, mid + 1, v, l, r);
    }
    else
    {
        query_tree(bh * 2, u, mid, l, mid);
        query_tree(bh * 2 + 1, mid + 1, v, mid + 1, r);
    }
}

int querymax(int a, int b)
{
    int ans = -40000;
    while (top[a] != top[b])
    {
        if (dep[top[a]] > dep[top[b]])
            swap(a, b);
        if (top[b] == b)
        {
            ans = max(ans, v[b]);
            b = parent[b];
        }
        else
        {
            global_ans_sum = 0;
            global_ans_max = -40000;
            //if (tid[b]>tid[top[b]])
            query_tree(1, 1, n, tid[b], tid[top[b]]);
            ans = max(ans, global_ans_max);
            b = parent[top[b]];
        }
    }
    if (dep[top[a]] > dep[top[b]])
        swap(a, b);
    global_ans_sum = 0;
    global_ans_max = -40000;
    query_tree(1, 1, n, tid[a], tid[b]);
    ans = max(ans, global_ans_max);
    return ans;
}

int querysum(int a, int b)
{
    int ans = 0;
    //bool usedparent1 = false;
    while (top[a] != top[b])
    {
        if (dep[top[a]] > dep[top[b]])
            swap(a, b);
        if (top[b] == b)
        {
            ans += v[b];
            /*if (b == 1)
                usedparent1 = true;*/
            b = parent[b];
        }
        else
        {
            global_ans_sum = 0;
            global_ans_max = -0;
            query_tree(1, 1, n, tid[b], tid[top[b]]);
            ans += global_ans_sum;
            /*if (top[b] == 1)
                usedparent1 = true;*/
            b = parent[top[b]];
        }
    }
    if (dep[top[a]] > dep[top[b]])
        swap(a, b);
    global_ans_sum = 0;
    global_ans_max = 0;
    query_tree(1, 1, n, tid[a], tid[b]);
    ans += global_ans_sum;
    return ans;
}

int main()
{
    //freopen("bzoj_10361.in", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &a, &b);
        addedge(a, b);
        addedge(b, a);
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &v[i]);
    }
    dfs(1, 1, 0);
    dfs1(1, 1);
    build_tree(1, 1, n);
    scanf("%d", &m);
    char s[100];
    for (int j = 1; j <= m; j++)
    {
        scanf("%s%d%d", s, &a, &b);
        if (s[1] == 'M')
            printf("%d\n", querymax(a, b));
        if (s[1] == 'S')
            printf("%d\n", querysum(a, b));
        if (s[0] == 'C')
            change_tree(1, 1, n, tid[a], tid[a], b);
    }
    //system("pause");
}