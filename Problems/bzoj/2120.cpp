#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

int n, m, len, quenum, changenum;
int c[100100], part[100100], col[100100];
ll ans, total[100100];

struct node
{
    int l, r, id, x;
    ll a;
} que[100100];
struct NODE
{
    int x, y, o;
} chg[100100];
int l = 1, r = 0, cur = 0;
bool cmp(node a, node b)
{
    return ((part[a.l] < part[b.l]) || ((part[a.l] == part[b.l]) && (a.r < b.r)) || ((part[a.l] == part[b.l]) && (a.r == b.r) && (a.x < b.x)));
}
bool cmpwithid(node a, node b)
{
    return a.id < b.id;
}
void update(int i, int add)
{
    printf("update:%d %d\n", i, add);
    int tmp = total[col[i]];
    total[col[i]] += add;
    if (tmp == 0 && total[col[i]] == 1)
        ans++;
    if (tmp == 1 && total[col[i]] == 0)
        ans--;
}

void change(int time, int color)
{
    printf("change:%d %d\n", time, color);
    if ((que[time].l >= l) && (que[time].r <= r))
    {
        total[col[chg[time].x]]--;
        if (total[col[chg[time].x]] == 0)
            ans--;
        col[chg[time].x] = color;
        total[color]++;
        if (total[color] == 1)
            ans++;
    }
    else
    {
        col[chg[time].x] = color;
    }
}

int main()
{
    int k;
    scanf("%d%d", &n, &m);
    len = floor(sqrt(n));
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &c[i]);
        col[i] = c[i];
        part[i] = (i - 1) / len + 1;
    }
    char ch;
    int tmpa, tmpb;
    for (int i = 1; i <= m; i++)
    {
        char ch = getchar();
        while (ch < 'A' || ch > 'Z')
            ch = getchar();
        scanf("%d%d", &tmpa, &tmpb);
        if (ch == 'Q')
        {
            quenum++;
            que[quenum].l = tmpa;
            que[quenum].r = tmpb;
            que[quenum].x = changenum;
            que[quenum].id = i;
        }
        else
        {
            changenum++;
            chg[changenum].x = tmpa;
            chg[changenum].y = tmpb;
            chg[changenum].o = c[chg[i].x];
            c[chg[changenum].x] = chg[i].y;
        }
    }
    sort(que + 1, que + quenum + 1, cmp);

    for (int i = 1; i <= quenum; i++)
    {
        for (; cur < que[i].x; cur++)
            change(cur + 1, chg[cur + 1].y);
        for (; cur > que[i].x; cur--)
            change(cur, chg[cur].o);
        for (; r < que[i].r; r++)
            update(r + 1, 1);
        for (; r > que[i].r; r--)
            update(r, -1);
        for (; l > que[i].l; l--)
            update(l - 1, 1);
        for (; l < que[i].l; l++)
            update(l, -1);
        que[i].a = ans;
        printf("%d %d\n", i, ans);
    }
    sort(que + 1, que + 1 + quenum, cmpwithid);
    for (int i = 1; i <= quenum; i++)
    {
        printf("%lld\n", que[i].a);
    }
    system("pause");
    return 0;
}