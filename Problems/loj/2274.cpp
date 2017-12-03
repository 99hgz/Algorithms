#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
<<<<<<< HEAD
#define N 200010
using namespace std;

int t[N], c[N], n, m, k, a, r, l, ans, pre[N];
=======
using namespace std;

#define N 200005
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ll long long
int sum[N * 4];
int visit[N * 4];
void pushUp(int rt)
{
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

void pushDown(int rt, int d)
{
    if (visit[rt] != 0)
    {
        visit[rt << 1] += visit[rt];
        visit[rt << 1 | 1] += visit[rt];
        sum[rt << 1 | 1] += (ll)(d >> 1) * visit[rt]; //注意后边乘可能超整形，强制类型转换（ll），即AC
        sum[rt << 1] += (ll)(d - (d >> 1)) * visit[rt];
        visit[rt] = 0;
    }
}
void update(int L, int R, int c, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        visit[rt] += c;
        sum[rt] += (r - l + 1) * c;
        return;
    }
    pushDown(rt, r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m)
        update(L, R, c, lson);
    if (R > m)
        update(L, R, c, rson);
    pushUp(rt);
}
int query(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        return sum[rt];
    }
    pushDown(rt, r - l + 1);
    int m = (l + r) >> 1;
    int ret = 0;
    if (L <= m)
        ret += query(L, R, lson);
    if (R > m)
        ret += query(L, R, rson);
    return ret;
}
priority_queue<int> Q;
int t[N], c[N], n, m, k, a, r, l, ans;
>>>>>>> 27a87cfa0b08413ef36f9e3d5ff66c291088b7dd
struct Node
{
    int l, r;
} range[N];
bool cmp(Node a, Node b)
{
    return a.l < b.l;
}
bool check(int x)
{
<<<<<<< HEAD
    priority_queue<int> Q;
    int it = 1;
    int used = 0;
    for (int i = 1; i <= n; i++)
        pre[i] = 0;
    int qzh = 0;
=======
    while (!Q.empty())
        Q.pop();
    for (int i = 1; i <= n; i++)
    {
        if (x <= c[i])
            t[i] = 0;
        else
            t[i] = ((x - c[i] - 1) / a) + 1;
    }
    int it = 1;
    int used = 0;
    memset(visit, 0, sizeof visit);
    memset(sum, 0, sizeof sum);
>>>>>>> 27a87cfa0b08413ef36f9e3d5ff66c291088b7dd
    for (int i = 1; i <= n; i++)
    {
        while (it <= m && range[it].l <= i)
        {
            Q.push(range[it].r);
            it++;
        }
<<<<<<< HEAD
        qzh += pre[i];
        int plused = qzh;
        int tmp = x <= c[i] ? 0 : ((x - c[i] - 1) / a) + 1;
        for (int times = 1; times <= tmp - plused; times++)
=======
        int plused = query(i, i, 1, n, 1);
        for (int times = 1; times <= t[i] - plused; times++)
>>>>>>> 27a87cfa0b08413ef36f9e3d5ff66c291088b7dd
        {
            while (!Q.empty() && Q.top() < i)
                Q.pop();
            if (Q.empty())
            {
                return false;
            }
            int nowr = Q.top();
            Q.pop();
<<<<<<< HEAD
            pre[i + 1]++;
            pre[nowr + 1]--;
            //update(i, nowr, 1, 1, n, 1);
=======
            update(i, nowr, 1, 1, n, 1);
>>>>>>> 27a87cfa0b08413ef36f9e3d5ff66c291088b7dd
            used++;
            if (used > k)
                return false;
        }
    }
    return true;
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d%d%d", &n, &m, &k, &a);
        r = 0;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &c[i]);
            r = max(r, c[i]);
        }
        for (int i = 1; i <= m; i++)
            scanf("%d%d", &range[i].l, &range[i].r);
        sort(range + 1, range + 1 + n, cmp);
<<<<<<< HEAD
        l = 1, r = 1e9, ans = 0;
        while (l <= r)
        {
            int mid = (l + r) / 2;
            //printf("%d %d mid=%d\n", l, r, mid);
=======
        l = 1, r += a * k, ans = 0;
        while (l <= r)
        {
            int mid = (l + r) / 2;
            printf("%d %d mid=%d\n", l, r, mid);
>>>>>>> 27a87cfa0b08413ef36f9e3d5ff66c291088b7dd
            if (check(mid))
            {
                ans = mid;
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        printf("%d\n", ans);
    }
    system("pause");
}