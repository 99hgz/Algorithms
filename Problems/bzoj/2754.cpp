#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxl = 300000 + 5, maxn = 20000 + 5, maxm = 50000 + 5;
int n, m, len, cut = 10000;
int a[maxl], b[maxl], c[maxl], sa[maxl], rk[maxl], ht[maxl], vis[maxn], ANS[maxn], t1[maxl], t2[maxl];
struct Node
{
    int start, cd;
} q[maxm];
void SA(int n, int m)
{
    int i, k, p, *x = t1, *y = t2;
    for (i = 0; i < m; i++)
        c[i] = 0;
    for (i = 0; i < n; i++)
        c[x[i] = a[i]]++;
    for (i = 1; i < m; i++)
        c[i] += c[i - 1];
    for (i = 0; i < n; i++)
        sa[--c[x[i]]] = i;
    for (k = 1, p = 1; p < n; k <<= 1, m = p)
    {
        for (p = 0, i = n - k; i < n; i++)
            y[p++] = i;
        for (i = 0; i < n; i++)
            if (sa[i] >= k)
                y[p++] = sa[i] - k;
        for (i = 0; i < m; i++)
            c[i] = 0;
        for (i = 0; i < n; i++)
            c[x[i]]++;
        for (i = 1; i < m; i++)
            c[i] += c[i - 1];
        for (i = n - 1; i >= 0; i--)
            sa[--c[x[y[i]]]] = y[i];
        for (swap(x, y), p = 1, x[sa[0]] = 0, i = 1; i < n; i++)
            x[sa[i]] = y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k] ? p - 1 : p++;
    }
}
void HT(int n)
{
    int i, j, k = 0;
    for (i = 0; i < n; i++)
        rk[sa[i]] = i;
    ht[0] = 0;
    for (i = 0; i < n; ht[rk[i++]] = k)
        if (rk[i])
            for (k ? k-- : 0, j = sa[rk[i] - 1]; a[i + k] == a[j + k]; k++)
                ;
}

int main()
{
    scanf("%d%d", &n, &m);
    int mm = m;
    for (int i = 1, tmp; i <= n; i++)
    {
        scanf("%d", &tmp);
        for (int j = 1; j <= tmp; j++)
        {
            b[len] = i;
            scanf("%d", &a[len++]);
        }
        a[len++] = ++cut;
        scanf("%d", &tmp);
        for (int j = 1; j <= tmp; j++)
        {
            b[len] = i;
            scanf("%d", &a[len++]);
        }
        a[len++] = ++cut;
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &q[i].cd);
        q[i].start = len;
        for (int j = 1; j <= q[i].cd; j++)
        {
            scanf("%d", &a[len++]);
        }
        a[len++] = ++cut;
    }
    SA(len, 300005);
    HT(len);
    for (int i = 1; i <= mm; i++)
    {
        int l = rk[q[i].start], r = rk[q[i].start] + 1;
        while (ht[l] >= q[i].cd)
            l--;
        while (ht[r] >= q[i].cd)
            r++;
        r--;
        int ans = 0;
        for (int j = l; j <= r; j++)
        {
            if (b[sa[j]] && vis[b[sa[j]]] != i)
            {
                vis[b[sa[j]]] = i;
                ans++;
                ANS[b[sa[j]]]++;
            }
        }
        printf("%d\n", ans);
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%d", ANS[i]);
        if (i != n)
            printf(" ");
    }
    system("pause");
    return 0;
}