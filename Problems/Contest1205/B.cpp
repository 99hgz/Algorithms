#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int size = 6;
int tree[size], cancontrol[size], sorted[size], sortedq[size], ans[size];
struct Person
{
    int rank, age;
} p[size];
struct Query
{
    int x, y, rmin;
} query[size];
int n, k, i, q;
typedef long long ll;

const int MAXN = 1010;

struct line
{
    int l;
    int r;
    int cmax;
} Tree[7];

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
        return;
    int x = (l + r) >> 1;
    buildTree(l, x, t << 1 | 1);
    buildTree(x + 1, r, (t << 1) + 2);
    pushUp(t);
}

void updateTree(int v, int cn, int t)
{
    if (Tree[t].l == v && Tree[t].r == v)
    {
        Tree[t].cmax = max(cn, Tree[t].cmax);
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
    if (l > r)
        return -1;
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

int lowbit(int x) { return x & -x; }

ll sum(int end)
{
    ll ans = 0;
    while (end > 0)
    {
        ans += tree[end];
        end -= lowbit(end);
    }
    return ans;
}
void update(int pos, int num)
{
    while (pos < size)
    {
        tree[pos] += num;
        pos += lowbit(pos);
    }
}

bool cmp(int a, int b) { return p[a].rank > p[b].rank; }
bool cmp1(int a, int b) { return p[a].rank < p[b].rank; }
bool cmpforq(int a, int b) { return query[a].rmin > query[b].rmin; }

int main()
{
    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &p[i].rank);
        sorted[i] = i;
    }
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &p[i].age);
    }
    sort(sorted + 1, sorted + n + 1, cmp1);
    int pointa = 1;
    int pointb = 0;
    while (pointb <= n)
    {
        while (p[sorted[pointa]].rank == p[sorted[pointa + 1]].rank)
        {
            pointa++;
            update(p[sorted[pointa]].age, 1);
            printf("inserted \n", );
        }
        printf("inserted total:%d\n", sum(max(5, 1)));
        for (int i = pointb + 1; i <= pointa; i++)
        {
            cancontrol[sorted[i]] = sum(p[sorted[i]].age + k) - sum(max(p[sorted[i]].age - k - 1, 1));
        }
        pointb = pointa;
        pointa++;
    }
    sort(sorted + 1, sorted + n + 1, cmp);
    scanf("%d", &q);
    for (int i = 1; i <= q; i++)
    {
        scanf("%d%d", &query[i].x, &query[i].y);
        query[i].rmin = max(p[query[i].x].rank, p[query[i].y].rank);
        sortedq[i] = i;
    }
    sort(sortedq + 1, sortedq + q + 1, cmpforq);
    buildTree(1, 4, 0);
    int tail = 1;
    for (int i = 1; i <= q; i++)
    {
        while ((query[sortedq[i]].rmin <= p[sorted[tail]].rank))
        {
            updateTree(p[sorted[tail]].age, cancontrol[sorted[tail]], 0);
            tail++;
        }
        ans[sortedq[i]] =
            queryTree(max(query[sortedq[i]].x - k, query[sortedq[i]].y - k),
                      min(query[sortedq[i]].x + k, query[sortedq[i]].y + k), 0);
    }
    for (int i = 1; i <= q; i++)
    {
        printf("%d\n", ans[i]);
    }
    system("pause");
}
