#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int nowans, l, r, a[50010];
struct Node
{
    int l, r, block, id;
} qry[200010];
int range, sl[1000010], n, m, ANS[200010];

bool cmp(Node a, Node b)
{
    if (a.block == b.block)
        return a.r < b.r;
    else
        return a.l < b.l;
}

void change(int x, int cz)
{
    //printf("c:%d %d\n", x, cz);
    if (sl[a[x]] == 0)
        nowans++;
    sl[a[x]] += cz;
    if (sl[a[x]] == 0)
        nowans--;
}
inline int read()
{
    int s = 0, w = 1;
    char ch = getchar();
    while (ch <= '0' || ch > '9')
    {
        if (ch == '-')
            w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        s = s * 10 + ch - '0', ch = getchar();
    return s * w;
}

int main()
{
    //scanf("%d", &n);
    n = read();
    int range = sqrt(n);
    for (int i = 1; i <= n; i++)
    {
        //scanf("%d", &a[i]);
        a[i] = read();
    }
    // scanf("%d", &m);
    m = read();
    for (int i = 1; i <= m; i++)
    {
        // scanf("%d%d", &qry[i].l, &qry[i].r);
        qry[i].l = read();
        qry[i].r = read();
        qry[i].block = qry[i].l / range;
        qry[i].id = i;
    }
    sort(qry + 1, qry + 1 + m, cmp);
    l = 1, r = 0;
    for (int i = 1; i <= m; i++)
    {
        while (r < qry[i].r)
            r++, change(r, 1);
        while (r > qry[i].r)
            change(r, -1), r--;
        while (l < qry[i].l)
            change(l, -1), l++;
        while (l > qry[i].l)
            l--, change(l, 1);
        //printf("%d %d \n", l, r);
        ANS[qry[i].id] = nowans;
    }
    for (int i = 1; i <= m; i++)
    {
        printf("%d\n", ANS[i]);
    }
    system("pause");
    return 0;
}