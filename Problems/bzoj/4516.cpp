#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <set>
using namespace std;
typedef int ll;
const ll MAXN = 1000000 + 10;
const ll T = 100000 + 10;

ll n, m, len;

template <size_t size>
struct suffix_array
{
    bool type[size << 1];
    int ht[size], rk[size], sa[size], bk[size], bk1[size];

    inline bool isLMS(int i, bool *type)
    {
        return (i > 0 && type[i] && !type[i - 1]);
    }

    template <class T>
    inline void induced_sort(T s, int *sa, int len, int bs, int sigma,
                             bool *type, int *bk, int *cb, int *p)
    {
        memset(bk, 0, sizeof(int) * sigma), memset(sa, -1, sizeof(int) * len);
        for (int i = 0; i < len; ++i)
            bk[s[i]]++;
        cb[0] = bk[0];
        for (int i = 1; i < sigma; ++i)
            cb[i] = cb[i - 1] + bk[i];
        for (int i = bs - 1; i >= 0; --i)
            sa[--cb[s[p[i]]]] = p[i];
        for (int i = 1; i < sigma; ++i)
            cb[i] = cb[i - 1] + bk[i - 1];
        for (int i = 0; i < len; ++i)
            if (sa[i] > 0 && !type[sa[i] - 1])
                sa[cb[s[sa[i] - 1]]++] = sa[i] - 1;
        cb[0] = bk[0];
        for (int i = 1; i < sigma; ++i)
            cb[i] = cb[i - 1] + bk[i];
        for (int i = len - 1; i >= 0; --i)
            if (sa[i] > 0 && type[sa[i] - 1])
                sa[--cb[s[sa[i] - 1]]] = sa[i] - 1;
    }

    template <class T>
    inline void sais(T s, int *sa, int len, bool *type, int *bk,
                     int *bk1, int sigma)
    {
        int cnt = 0, p = -1, x, bs = 0, *cb = bk + sigma, j;
        type[len - 1] = true;
        for (int i = len - 2; i >= 0; --i)
            type[i] = (s[i] < s[i + 1] || (s[i] == s[i + 1] && type[i + 1]));
        for (int i = 1; i < len; ++i)
            if (type[i] && !type[i - 1])
                bk1[bs++] = i;
        induced_sort(s, sa, len, bs, sigma, type, bk, cb, bk1);
        for (int i = bs = 0; i < len; ++i)
            if (isLMS(sa[i], type))
                sa[bs++] = sa[i];
        for (int i = bs; i < len; ++i)
            sa[i] = -1;
        for (int i = 0; i < bs; ++i)
        {
            x = sa[i];
            for (int j = 0; j < len; ++j)
            {
                if (p == -1 || (s[x + j] != s[p + j]) || type[x + j] != type[p + j])
                {
                    cnt++, p = x;
                    break;
                }
                else if (j > 0 && (isLMS(x + j, type)))
                    break;
            }
            x >>= 1, sa[x + bs] = cnt - 1;
        }
        for (int i = j = len - 1; i >= bs; --i)
            if (sa[i] >= 0)
                sa[j--] = sa[i];
        int *s1 = sa + len - bs, *bk2 = bk1 + bs;
        if (cnt < bs)
            sais(s1, sa, bs, type + len, bk, bk2, cnt);
        else
            for (int i = 0; i < bs; ++i)
                sa[s1[i]] = i;
        for (int i = 0; i < bs; ++i)
            bk2[i] = bk1[sa[i]];
        induced_sort(s, sa, len, bs, sigma, type, bk, cb, bk2);
    }

    inline void get_height(int *s, int len, int *sa)
    {
        for (int i = 0, k = 0; i < len; ++i)
        {
            if (rk[i] == 0)
                k = 0;
            else
            {
                if (k > 0)
                    k--;
                int j = sa[rk[i] - 1];
                while (i + k < len && j + k < len && s[i + k] == s[j + k])
                    k++;
            }
            ht[rk[i]] = k;
        }
    }

    template <class T>
    inline void init(T s, int len, int sigma)
    {
        sais(s, sa, len, type, bk, bk1, sigma);
        for (int i = 1; i < len; ++i)
            rk[sa[i]] = i;
        get_height(s, len, sa);
    }
};
ll a[100010], Hash[100010], delta[100010], Q[100010], res[100010], s[100010];

suffix_array<MAXN> sa;
int Minimum(int L, int H)
{
    int res = 0x3f3f3f3f;
    for (int i = L; i <= H; i++)
        res = min(res, sa.ht[i]);
    return res == 0x3f3f3f3f ? 0 : res;
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
    n = read();
    for (int i = 1; i <= n; i++)
    {
        a[i] = read();
        Hash[i] = a[i];
    }
    sort(Hash + 1, Hash + 1 + n);
    int tn = unique(Hash + 1, Hash + 1 + n) - Hash - 1;
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(Hash + 1, Hash + 1 + tn, a[i]) - Hash;
    for (int i = 1; i <= n; i++)
        s[n - i] = a[i] + 2;

    len = n;
    s[len] = 1;
    sa.init(s, len + 1, 100010);
    for (int i = 1; i <= n; i++)
    {
        sa.sa[i - 1] = sa.sa[i];
        sa.ht[i - 1] = sa.ht[i];
        sa.rk[i - 1]--;
        //printf("rk=%d\n", sa.rk[i]);
    }

    int head = 1, tail = 1;
    for (int i = 0; i < n; i++)
    {
        int it = lower_bound(Q + head, Q + tail, n - 1 - sa.sa[i]) - Q;
        if (head == tail || Q[head] > (n - 1 - sa.sa[i]))
            res[i] = 0;
        else
        {
            it--;
            int tmp = sa.rk[n - 1 - Q[it]] + 1;
            res[i] = Minimum(tmp, i);
        }
        while (head < tail && Q[tail - 1] > (n - 1 - sa.sa[i]))
            tail--;
        Q[tail++] = n - 1 - sa.sa[i];
    }

    head = tail = 1;
    Q[1] = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        int it = lower_bound(Q + head, Q + tail, n - 1 - sa.sa[i]) - Q;
        if (head == tail || Q[head] > (n - 1 - sa.sa[i]))
            res[i] = max(res[i], 0);
        else
        {
            it--;
            int tmp = sa.rk[n - 1 - Q[it]];
            res[i] = max(res[i], Minimum(i + 1, tmp));
        }
        while (head < tail && Q[tail - 1] > (n - 1 - sa.sa[i]))
            tail--;
        Q[tail++] = n - 1 - sa.sa[i];
        delta[n - 1 - sa.sa[i]] = n - 1 - sa.sa[i] + 1 - res[i];
    }

    long long sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += delta[i];
        printf("%lld\n", sum);
    }
    //system("pause");
    return 0;
}