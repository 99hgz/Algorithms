#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <stack>
#include <algorithm>
using namespace std;
typedef int ll;

const ll maxl = 1000000 + 5;
const ll T = 1000000 + 5;

ll n, m, len, pos;
ll t1[T], t2[T], cc[T], x[T], sa[T], Rank[T], height[T];

char s1[50010], s2[50010], s3[50010], s[150010];
bool cmp(ll *y, ll a, ll b, ll k)
{
    ll a1 = y[a];
    ll b1 = y[b];
    ll a2 = a + k >= len ? -1 : y[a + k];
    ll b2 = b + k >= len ? -1 : y[b + k];
    return a1 == b1 && a2 == b2;
}
ll make_sa()
{
    ll *x = t1, *y = t2;
    ll m = 30;
    for (ll i = 0; i < m; i++)
        cc[i] = 0;
    for (ll i = 0; i < len; i++)
        ++cc[x[i] = s[i] - 'a'];
    for (ll i = 1; i < m; i++)
        cc[i] += cc[i - 1];
    for (ll i = len - 1; i >= 0; i--)
        sa[--cc[x[i]]] = i;

    for (ll k = 1; k <= len; k <<= 1)
    {
        ll p = 0;
        for (ll i = len - k; i < len; i++)
            y[p++] = i;
        for (ll i = 0; i < len; i++)
            if (sa[i] >= k)
                y[p++] = sa[i] - k;

        for (ll i = 0; i < m; i++)
            cc[i] = 0;
        for (ll i = 0; i < len; i++)
            ++cc[x[y[i]]];
        for (ll i = 1; i < m; i++)
            cc[i] += cc[i - 1];
        for (ll i = len - 1; i >= 0; i--)
            sa[--cc[x[y[i]]]] = y[i];

        swap(x, y);
        m = 1;
        x[sa[0]] = 0;
        for (ll i = 1; i < len; i++)
            x[sa[i]] = cmp(y, sa[i], sa[i - 1], k) ? m - 1 : m++;

        if (m >= len)
            break;
    }
}
void make_height()
{
    for (ll i = 0; i < len; i++)
        Rank[sa[i]] = i;
    height[0] = 0;
    ll k = 0;
    for (ll i = 0; i < len; i++)
    {
        if (!Rank[i])
            continue;
        ll j = sa[Rank[i] - 1];
        if (k)
            k--;
        while (s[i + k] == s[j + k])
            k++;
        height[Rank[i]] = k;
    }
}

int Minimum(int L, int H)
{
    if (L > H)
        swap(L, H);
    L++;
    int res = 0x3f3f3f3f;
    for (int i = L; i <= H; i++)
        res = min(res, height[i]);
    return res == 0x3f3f3f3f ? 0 : res;
}

int main()
{
    scanf("%s", s1);
    scanf("%s", s2);
    scanf("%s", s3);
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int len3 = strlen(s3);
    len = len1 + 1 + len2 + 1 + len3;
    for (int i = 0; i < len1; i++)
        s[pos++] = s1[i];
    s[pos++] = '{';
    for (int i = 0; i < len2; i++)
        s[pos++] = s2[i];
    s[pos++] = '{';
    for (int i = 0; i < len3; i++)
        s[pos++] = s3[i];
    make_sa();
    make_height();
    int poss3 = Rank[len1 + 1 + len2 + 1];
    int last = -1;
    int ans = 0;
    //printf("%d\n", len);
    for (int i = 0; i <= len - 1; i++)
    {
        printf("sa=%d\n", sa[i]);
        if (sa[i] >= len1 + 1 && sa[i] <= len1 + len2)
        {
            if (last != -1)
            {
                int lcp = Minimum(last, i);
                int lcp2 = Minimum(i, poss3);
                int tmp = min(lcp, lcp2);
                printf("%d %d %d last=%d\n", sa[i], lcp, lcp2, last);
                if (tmp == len3)
                    tmp--;
                else
                    tmp = lcp;
                ans = max(ans, tmp);
            }
        }
        else if (sa[i] <= len1 - 1)
        {
            printf("last=%d\n", i);
            last = i;
        }
    }
    last = -1;
    for (int i = len - 1; i >= 0; i--)
    {
        if (sa[i] >= len1 + 1 && sa[i] <= len1 + len2)
        {
            if (last != -1)
            {
                int lcp = Minimum(last, i);
                int lcp2 = Minimum(i, poss3);
                int tmp = min(lcp, lcp2);
                if (tmp == len3)
                    tmp--;
                else
                    tmp = lcp;
                ans = max(ans, tmp);
            }
        }
        else if (sa[i] <= len1 - 1)
            last = i;
    }
    printf("%d\n", ans);
    system("pause");
    return 0;
}