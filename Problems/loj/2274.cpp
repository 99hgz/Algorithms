#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
#define N 200010
using namespace std;

int t[N], c[N], n, m, k, a, r, l, ans, pre[N];
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
    priority_queue<int> Q;
    int it = 1;
    int used = 0;
    for (int i = 1; i <= n; i++)
        pre[i] = 0;
    int qzh = 0;
    for (int i = 1; i <= n; i++)
    {
        while (it <= m && range[it].l <= i)
        {
            Q.push(range[it].r);
            it++;
        }
        qzh += pre[i];
        int plused = qzh;
        int tmp = x <= c[i] ? 0 : ((x - c[i] - 1) / a) + 1;
        for (int times = 1; times <= tmp - plused; times++)
        {
            while (!Q.empty() && Q.top() < i)
                Q.pop();
            if (Q.empty())
            {
                return false;
            }
            int nowr = Q.top();
            Q.pop();
            pre[i + 1]++;
            pre[nowr + 1]--;
            //update(i, nowr, 1, 1, n, 1);
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
        l = 1, r = 1e9, ans = 0;
        while (l <= r)
        {
            int mid = (l + r) / 2;
            //printf("%d %d mid=%d\n", l, r, mid);
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