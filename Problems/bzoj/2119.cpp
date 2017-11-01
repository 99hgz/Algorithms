#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <stack>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxl = 100000 + 5;
const int T = 100000 + 5;

int len;

int origin[T], s[T], s1[T];
int v[maxl], sa1[maxl], rk1[maxl], sa2[maxl], rk2[maxl], ht[maxl], Rk[maxl];
int *sa, *rk, *SA, *RK;
void make_sa()
{
    rk = rk1;
    RK = rk2;
    sa = sa1;
    SA = sa2;
    int i, k, j;
    for (i = 1; i <= len; i++)
        v[s[i]]++;
    for (i = 1; i <= 50010; i++)
        v[i] += v[i - 1];
    for (i = len; i; i--)
        sa[v[s[i]]--] = i;
    for (i = 1; i <= len; i++)
        rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
    for (k = 1; k <= len; k <<= 1)
    {
        for (i = 1; i <= len; i++)
            v[rk[sa[i]]] = i;
        for (i = len; i; i--)
            if (sa[i] > k)
                SA[v[rk[sa[i] - k]]--] = sa[i] - k;
        for (i = len - k + 1; i <= len; i++)
            SA[v[rk[i]]--] = i;
        for (i = 1; i <= len; i++)
            RK[SA[i]] = RK[SA[i - 1]] + (rk[SA[i]] != rk[SA[i - 1]] || rk[SA[i] + k] != rk[SA[i - 1] + k]);
        swap(sa, SA);
        swap(rk, RK);
    }
    k = 0;
    for (i = 1; i < len; i++)
    {
        j = rk[i] - 1;
        while (s[sa[rk[i]] + k] == s[sa[j] + k])
            k++;
        ht[rk[i]] = k;
        if (k)
            k--;
    }
}

int DP[2][maxl][20];
class RMQ
{
  public:
    void rmq(int bh)
    {
        int temp = (int)(log((double)len) / log(2.0));
        for (int i = 0; i <= len; i++)
            DP[bh][i][0] = ht[i];
        for (int j = 1; j <= temp; j++)
            for (int i = 0; i <= len; i++)
                if (i + (1 << j) - 1 <= len)
                    DP[bh][i][j] =
                        min(DP[bh][i][j - 1], DP[bh][i + (1 << (j - 1))][j - 1]);
    }
    int Minimum(int bh, int L, int H)
    {
        if (L > H)
            swap(L, H);
        L++;
        int k = (int)(log((double)H - L + 1) / log(2.0));
        return min(DP[bh][L][k], DP[bh][H - (1 << k) + 1][k]);
    }
};
int Hash[T];
int main()
{
    int L;
    ll ANS = 0;
    scanf("%d%d", &len, &L);
    for (int i = 1; i <= len; i++)
    {
        scanf("%d", &origin[i]);
        if (i != 1)
            Hash[i - 1] = s[i - 1] = origin[i] - origin[i - 1];
    }
    len--;
    sort(Hash + 1, Hash + len + 1);
    int tn = unique(Hash + 1, Hash + 1 + len) - Hash - 1;
    for (int i = 1; i <= len; i++)
    {
        s[i] = lower_bound(Hash + 1, Hash + 1 + tn, s[i]) - Hash;
        //printf("%d\n", s[i]);
    }
    for (int i = 1; i <= len; i++)
        s1[i] = s[i];
    make_sa();
    for (int i = 1; i <= len; i++)
        Rk[i] = rk[i];
    RMQ R;
    R.rmq(0);
    memset(v, 0, sizeof v);
    memset(sa1, 0, sizeof sa1);
    memset(rk1, 0, sizeof rk1);
    memset(sa2, 0, sizeof sa2);
    memset(rk2, 0, sizeof rk2);
    memset(ht, 0, sizeof ht);
    for (int i = 1; i <= len; i++)
    {
        s[i] = s1[len - i + 1];
        //printf("%c", s[i]);
    }
    make_sa();
    R.rmq(1);

    for (int i = 1; i + i + L <= len; i++)
    {
        for (int j = 1; j <= len; j += i)
        {
            int r = j + i + L;
            int t = min(i, R.Minimum(0, Rk[j], Rk[r]));
            int t1 = min(i, R.Minimum(1, (len - j + 1 <= 0) ? 0 : rk[len - j + 1], (len - r + 1 <= 0) ? 0 : rk[len - r + 1]));
            //printf("%d %d %d %d\n", i, j, t, t1);
            int ans = t + t1;
            if (t && t1)
                ans--;
            if (ans >= i)
                ANS += (ll)(ans - i + 1);
        }
    }

    printf("%lld\n", ANS);
    system("pause");
    return 0;
}