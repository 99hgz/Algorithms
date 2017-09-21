#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxl = 200000 + 5;
int n, m, len, cut = 10000;
char S[maxl];
int a[maxl], b[maxl], c[maxl], sa[maxl], rk[maxl], ht[maxl], t1[maxl], t2[maxl];
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
    scanf("%s", S);
    int len = strlen(S);
    for (int i = 0; i < len; i++)
    {
        a[i] = a[i + len] = S[i];
    }
    SA(len * 2, maxl);
    for (int i = 0; i < len * 2; i++)
    {
        if (sa[i] < len)
            printf("%c", S[(sa[i] + len - 1) % len]);
    }
    system("pause");
    return 0;
}