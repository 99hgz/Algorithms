#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
#define inf 1000000000
using namespace std;
typedef long long ll;
const int size = 300100;
ll tree[size];
int n, m, k, l, r, w, oldmid;
int list[size], ans[size], tmplist[size], belong[size];
ll need[size];
int Next[size], head[size], val[size], tot;
struct METEORS
{
    int l, r, w, id;
} meteors[size * 2];
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int lowbit(int x)
{
    return x & -x;
}
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
void add(int x, int z)
{
    tot++;
    Next[tot] = head[x];
    head[x] = tot;
    val[tot] = z;
}
void solve(int block_l, int block_r, int meteors_l, int meteors_r)
{
    /*printf("%d %d %d %d\n", block_l, block_r, meteors_l, meteors_r);
    for (int i = block_l; i <= block_r; i++)
    {
        printf("%d ", list[i]);
    }
    printf("\n");*/
    if (block_l > block_r)
    {
        return;
    }
    if (meteors_l == meteors_r)
    {
        for (int i = block_l; i <= block_r; i++)
        {
            ans[list[i]] = meteors[meteors_l].id;
        }
        return;
    }
    //memset(got, 0, sizeof got);

    int mid = (meteors_l + meteors_r) >> 1;
    for (int i = oldmid; i > mid; i--)
    {
        if (meteors[i].l > meteors[i].r)
        {
            update(meteors[i].l, -meteors[i].w);
            update(m + 1, meteors[i].w);
            update(1, -meteors[i].w);
            update(meteors[i].r + 1, meteors[i].w);
        }
        else
        {
            update(meteors[i].l, -meteors[i].w);
            update(meteors[i].r + 1, meteors[i].w);
        }
    }
    for (int i = oldmid + 1; i <= mid; i++)
    {
        if (meteors[i].l > meteors[i].r)
        {
            update(meteors[i].l, meteors[i].w);
            update(m + 1, -meteors[i].w);
            update(1, meteors[i].w);
            update(meteors[i].r + 1, -meteors[i].w);
        }
        else
        {
            update(meteors[i].l, meteors[i].w);
            update(meteors[i].r + 1, -meteors[i].w);
        }
    }
    oldmid = mid;
    /*for (int i = 1; i <= m; i++)
    {
        got[belong[i]] += sum(i);
    }*/
    int pointa = block_l;
    int pointb = block_r;
    for (int i = block_l; i <= block_r; i++)
    {
        ll got = 0;
        for (int j = head[list[i]]; j; j = Next[j])
        {
            got += sum(val[j]);
        }
        if (got < need[list[i]])
        {
            tmplist[pointb--] = list[i];
        }
        else
        {
            tmplist[pointa++] = list[i];
        }
    }
    for (int i = block_l; i <= block_r; i++)
    {
        list[i] = tmplist[i];
    }
    solve(block_l, pointa - 1, meteors_l, mid);
    solve(pointb + 1, block_r, mid + 1, meteors_r);
}

int main()
{
    n = read();
    m = read();
    //scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        belong[i] = read();
        //scanf("%d", &belong[i]);
        add(belong[i], i);
        //sons[belong[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++)
    {
        need[i] = read();
        //scanf("%lld", &need[i]);
        list[i] = i;
    }
    k = read();
    //scanf("%d", &k);
    int tmpk = 0;
    for (int i = 1; i <= k; i++)
    {
        l = read();
        r = read();
        w = read();
        //scanf("%d%d%d", &l, &r, &w);
        /*if (l > r)
        {
            tmpk++;
            meteors[tmpk].l = l;
            meteors[tmpk].r = m;
            meteors[tmpk].w = w;
            meteors[tmpk].id = i;
            tmpk++;
            meteors[tmpk].l = 1;
            meteors[tmpk].r = r;
            meteors[tmpk].w = w;
            meteors[tmpk].id = i;
        }
        else
        {
            tmpk++;
            meteors[tmpk].l = l;
            meteors[tmpk].r = r;
            meteors[tmpk].w = w;
            meteors[tmpk].id = i;
        }*/
        tmpk++;
        meteors[tmpk].l = l;
        meteors[tmpk].r = r;
        meteors[tmpk].w = w;
        meteors[tmpk].id = i;
    }
    tmpk++;
    meteors[tmpk].l = 1;
    meteors[tmpk].r = m;
    meteors[tmpk].w = inf;
    meteors[tmpk].id = tmpk;
    k = tmpk;
    solve(1, n, 1, k);
    for (int i = 1; i <= n; i++)
    {
        if (ans[i] == k)
        {
            printf("NIE\n");
        }
        else
        {
            printf("%d\n", ans[i]);
        }
    }
    system("pause");
    return 0;
}