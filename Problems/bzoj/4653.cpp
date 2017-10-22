#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
typedef long long ll;

int n, m;
struct LINE
{
    int l, r, cd;
} line[500010];

bool cmp(LINE a, LINE b)
{
    return a.cd < b.cd;
};

int tot;

#define N 1000005
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
int mark[N * 4];
int visit[N * 4];
int Hash[1001010];
void pushUp(int rt)
{
    mark[rt] = max(mark[rt << 1], mark[rt << 1 | 1]);
}

void pushDown(int rt, int d)
{
    if (visit[rt] != 0)
    {
        visit[rt << 1] += visit[rt];
        visit[rt << 1 | 1] += visit[rt];
        mark[rt << 1 | 1] += visit[rt];
        mark[rt << 1] += visit[rt];
        visit[rt] = 0;
    }
}
void update(int L, int R, int c, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        visit[rt] += c;
        mark[rt] += c;
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
        return mark[rt];
    }
    pushDown(rt, r - l + 1);
    int m = (l + r) >> 1;
    int ret = 0;
    if (L <= m)
        ret = max(ret, query(L, R, lson));
    if (R > m)
        ret = max(ret, query(L, R, rson));
    return ret;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &line[i].l, &line[i].r);
        line[i].cd = line[i].r - line[i].l;
        Hash[++tot] = line[i].l;
        Hash[++tot] = line[i].r;
    }
    sort(Hash + 1, Hash + 1 + tot);
    int tn = unique(Hash + 1, Hash + 1 + tot) - Hash - 1;
    sort(line + 1, line + 1 + n, cmp);
    int head = 1, ans = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
    {
        line[i].l = lower_bound(Hash + 1, Hash + 1 + tn, line[i].l) - Hash;
        line[i].r = lower_bound(Hash + 1, Hash + 1 + tn, line[i].r) - Hash;
        update(line[i].l, line[i].r, 1, 1, tn, 1);
        int tmp = query(line[i].l, line[i].r, 1, tn, 1);
        // printf("push:%d %d\n", line[i].l, line[i].r);
        //printf("%d\n", tmp);
        if (tmp >= m)
        {
            while (head <= i)
            {
                if (query(1, tn, 1, tn, 1) < m)
                    break;
                //printf("pop:%d %d\n", line[head].l, line[head].r);
                update(line[head].l, line[head].r, -1, 1, tn, 1);
                head++;
            }
            ans = min(ans, line[i].cd - line[head - 1].cd);
        }
    }
    printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
    system("pause");
    return 0;
}