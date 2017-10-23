#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <stack>
#include <algorithm>
using namespace std;

const int maxl = 50000 + 5;
const int T = 50000 + 5;

int n, m, len;
int left[maxl], right[maxl], Stop, S1top;

struct Node
{
    int pos, val;
};
Node S[maxl], S1[maxl];

char s[T];
int t1[T], t2[T], cc[T], x[T], sa[T], rank[T], height[T];

bool cmp(int *y, int a, int b, int k)
{
    int a1 = y[a];
    int b1 = y[b];
    int a2 = a + k >= len ? -1 : y[a + k];
    int b2 = b + k >= len ? -1 : y[b + k];
    return a1 == b1 && a2 == b2;
}
int make_sa()
{
    int *x = t1, *y = t2;
    int m = 26;
    for (int i = 0; i < m; i++)
        cc[i] = 0;
    for (int i = 0; i < len; i++)
        ++cc[x[i] = s[i] - 'a'];
    for (int i = 1; i < m; i++)
        cc[i] += cc[i - 1];
    for (int i = len - 1; i >= 0; i--)
        sa[--cc[x[i]]] = i;

    for (int k = 1; k <= len; k <<= 1)
    {
        int p = 0;
        for (int i = len - k; i < len; i++)
            y[p++] = i;
        for (int i = 0; i < len; i++)
            if (sa[i] >= k)
                y[p++] = sa[i] - k;

        for (int i = 0; i < m; i++)
            cc[i] = 0;
        for (int i = 0; i < len; i++)
            ++cc[x[y[i]]];
        for (int i = 1; i < m; i++)
            cc[i] += cc[i - 1];
        for (int i = len - 1; i >= 0; i--)
            sa[--cc[x[y[i]]]] = y[i];

        swap(x, y);
        m = 1;
        x[sa[0]] = 0;
        for (int i = 1; i < len; i++)
            x[sa[i]] = cmp(y, sa[i], sa[i - 1], k) ? m - 1 : m++;

        if (m >= len)
            break;
    }
}
void make_height()
{
    for (int i = 0; i < len; i++)
        rank[sa[i]] = i;
    height[0] = 0;
    int k = 0;
    for (int i = 0; i < len; i++)
    {
        if (!rank[i])
            continue;
        int j = sa[rank[i] - 1];
        if (k)
            k--;
        while (s[i + k] == s[j + k])
            k++;
        height[rank[i]] = k;
    }
}
int DP[maxl][20];
class RMQ
{
  public:
    void rmq()
    {
        int temp = (int)(log((double)len) / log(2.0));
        for (int i = 1; i <= len; i++)
            DP[i][0] = height[i];
        for (int j = 1; j <= temp; j++)
            for (int i = 1; i <= len; i++)
                if (i + (1 << j) <= len)
                    DP[i][j] = min(DP[i][j - 1], DP[i + (1 << (j - 1))][j - 1]);
    }
    int Minimum(int L, int H)
    {
        if (L > H)
            swap(L, H);
        int k = (int)(log((double)H - L + 1) / log(2.0));
        return min(DP[L][k], DP[H - (1 << k) + 1][k]);
    }
};

int main()
{
    int L, ANS = 0;
    scanf("%d", &L);
    scanf("%s", s);
    len = strlen(s);
    make_sa();
    make_height();
    RMQ R;
    R.rmq();
    for (int i = 0; i < len; i++)
    {
        int l = 1, r = len, ans = 0;
        while (l <= r)
        {
            int mid = (l + r) / 2;
            if ((R.Minimum(rank[i] + 1, rank[i + mid + L])) >= mid)
            {
                ans = mid;
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        if (ans)
        {
            ANS += ans;
        }
    }
    printf("%d\n", ANS);
    system("pause");
    return 0;
}