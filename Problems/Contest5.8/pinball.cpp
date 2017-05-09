#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 200009;

struct line
{
    int l;
    int r;
    int cmax;
} Tree[MAXN * 4];

void pushUp(int t)
{
    int x = t << 1;
    Tree[t].cmax = max(Tree[x + 1].cmax, Tree[x + 2].cmax);
}

void buildTree(int l, int r, int t)
{
    Tree[t].l = l;
    Tree[t].r = r;
    Tree[t].cmax = 0;
    if (l == r)
    {
        scanf("%d", &Tree[t].cmax);
        return;
    }
    int x = (l + r) >> 1;
    buildTree(l, x, t << 1 | 1);
    buildTree(x + 1, r, (t << 1) + 2);
    pushUp(t);
}

void updateTree(int v, int cn, int t)
{
    if (Tree[t].l == v && Tree[t].r == v)
    {
        Tree[t].cmax = cn;
        return;
    }
    int m = (Tree[t].l + Tree[t].r) >> 1;
    if (v <= m)
    {
        updateTree(v, cn, t << 1 | 1);
    }
    else
    {
        updateTree(v, cn, (t << 1) + 2);
    }
    pushUp(t);
}

int queryTree(int l, int r, int t)
{
    if (Tree[t].l == l && Tree[t].r == r)
    {
        return Tree[t].cmax;
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
        int ret1 = queryTree(l, m, t << 1 | 1);
        int ret2 = queryTree(m + 1, r, (t << 1) + 2);
        return max(ret1, ret2);
    }
}

int n, m;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d%d\n", &l[i],&r[i],&m[i],&cost[i]);
        points.push_back(l[i]);     
        points.push_back(r[i]);  
        //points.push_back(m[i]);       
    }
    sort(points.begin(),points.end());
    for (int i = 0; i < points.size(); i++) {
        points[i]
    }
}