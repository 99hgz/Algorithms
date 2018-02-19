#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int last, root, cnt, len[3100000], a[3100000][2], fa[3100000], ans[3100000], f[3100000], n, m, stlen;
char st[3100000];
struct Node
{
    int pos, val;
} Q[3100000];

void init()
{
    last = root = ++cnt;
}

void extend(int ch)
{
    int p = last, np = last = ++cnt;
    len[np] = len[p] + 1;
    while (p && !a[p][ch])
        a[p][ch] = np, p = fa[p];
    if (!p)
        fa[np] = root;
    else
    {
        int q = a[p][ch];
        if (len[q] == len[p] + 1)
            fa[np] = q;
        else
        {
            int nq = ++cnt;
            len[nq] = len[p] + 1;
            memcpy(a[nq], a[q], sizeof a[q]);
            fa[nq] = fa[q];
            fa[q] = fa[np] = nq;
            while (p && a[p][ch] == q)
                a[p][ch] = nq, p = fa[p];
        }
    }
}

void calc()
{
    int tmp = 0, cur = root;
    for (int j = 1; j <= stlen; j++)
    {
        int ch = st[j] - '0';
        if (a[cur][ch])
            tmp++, cur = a[cur][ch];
        else
        {
            while (cur && !a[cur][ch])
                cur = fa[cur];
            if (!cur)
                tmp = 0, cur = root;
            else
                tmp = len[cur] + 1, cur = a[cur][ch];
        }
        ans[j] = tmp;
    }
}

bool check(int L)
{
    int head = 1, tail = 0;
    for (int i = 1; i <= stlen; i++)
    {
        f[i] = f[i - 1];
        if (i - L < 0)
            continue;
        while (head <= tail && Q[head].val < f[i - L] - i + L)
            tail--;
        Q[++tail] = (Node){i - L, f[i - L] - i + L};
        while (head <= tail && Q[head].pos < i - ans[i])
            head++;
        if (head <= tail)
            f[i] = max(f[i], Q[head].val + i);
    }
    return f[stlen] * 10 >= 9 * stlen;
}

int main()
{
    scanf("%d%d", &n, &m);
    init();
    for (int i = 1; i <= m; i++)
    {
        scanf("%s", st + 1);
        stlen = strlen(st + 1);
        last = root;
        for (int j = 1; j <= stlen; j++)
            extend(st[j] - '0');
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", st + 1);
        stlen = strlen(st + 1);
        calc();
        int l = 0, r = stlen, ans = 0;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (check(mid))
                ans = mid, l = mid + 1;
            else
                r = mid - 1;
        }
        printf("%d\n", ans);
    }
    system("pause");
    return 0;
}