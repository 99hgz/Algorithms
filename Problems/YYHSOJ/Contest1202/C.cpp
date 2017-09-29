/*
 * @key word:线段树
 * @已测试:HDU - 1754
 * @Author: hgz 
 * @Date: 2017-04-24 19:09:25 
 * @Last Modified by:   hgz 
 * @Last Modified time: 2017-04-24 19:09:25 
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>
using namespace std;
typedef long long ll;

const int MAXN = 500009;

struct line
{
    int l;
    int r;
    int cmin, cmax, cans;
} Tree[MAXN * 4];

struct ANS
{
    int cmax, cmin, cans;
};

void pushUp(int t)
{
    int x = t << 1;
    Tree[t].cmin = min(Tree[x + 1].cmin, Tree[x + 2].cmin);
    Tree[t].cmax = max(Tree[x + 1].cmax, Tree[x + 2].cmax);
    Tree[t].cans = max(max(Tree[x + 1].cans, -Tree[x + 1].cmin + Tree[x + 2].cmax), Tree[x + 2].cans);
}

void buildTree(int l, int r, int t)
{
    Tree[t].l = l;
    Tree[t].r = r;
    Tree[t].cmin = INT_MAX;
    if (l == r)
    {
        scanf("%d", &Tree[t].cmin);
        Tree[t].cmax = Tree[t].cmin;
        Tree[t].cans = 0;
        return;
    }
    int x = (l + r) >> 1;
    buildTree(l, x, t << 1 | 1);
    buildTree(x + 1, r, (t << 1) + 2);
    pushUp(t);
}

ANS queryTree(int l, int r, int t)
{
    ANS thisans;
    if (Tree[t].l == l && Tree[t].r == r)
    {
        thisans.cmin = Tree[t].cmin;
        thisans.cmax = Tree[t].cmax;
        thisans.cans = Tree[t].cans;
        return thisans;
    }
    int m = (Tree[t].l + Tree[t].r) >> 1;
    if (l > m)
    {
        return queryTree(l, r, (t << 1) + 2);
    }
    else if (r <= m)
    {
        return queryTree(l, r, t << 1 | 1);
    }
    else
    {
        ANS ret1 = queryTree(l, m, t << 1 | 1);
        ANS ret2 = queryTree(m + 1, r, (t << 1) + 2);
        thisans.cmin = min(ret1.cmin, ret2.cmin);
        thisans.cmax = max(ret1.cmax, ret2.cmax);
        thisans.cans = max(ret1.cans, max(ret2.cans, ret2.cmax - ret1.cmin));
        return thisans;
    }
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);

    buildTree(1, n, 0);
    while (m--)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        ANS global_ans = queryTree(a, b, 0);
        printf("%d\n", global_ans.cans);
    }
    system("pause");
    return 0;
}