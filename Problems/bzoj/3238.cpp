#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <stack>
#include <algorithm>
using namespace std;
typedef long long ll;

const ll maxl = 1000000 + 5;
const ll T = 1000000 + 5;

ll n, m, len;
ll left[maxl], right[maxl], Stop, S1top;

struct Node
{
    ll pos, val;
};
Node S[maxl], S1[maxl];

char s[T];
ll t1[T], t2[T], cc[T], x[T], sa[T], rank[T], height[T];

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
    ll m = 26;
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
        rank[sa[i]] = i;
    height[0] = 0;
    ll k = 0;
    for (ll i = 0; i < len; i++)
    {
        if (!rank[i])
            continue;
        ll j = sa[rank[i] - 1];
        if (k)
            k--;
        while (s[i + k] == s[j + k])
            k++;
        height[rank[i]] = k;
    }
}

int main()
{

    scanf("%s", s);
    len = strlen(s);
    make_sa();
    make_height();
    ll ans = len * (len - 1) * (len + 1) / 2;
    ll total = 0;
    for (ll i = 0; i < len; i++)
    {
        printf("%d\n", height[i]);
    }
    for (ll i = 1; i < len; i++)
    {
        while (Stop && S[Stop].val >= height[i])
        {
            Stop--;
            //S.pop();
        }
        left[i] = Stop == 0 ? 1 : S[Stop].pos + 1;
        S[++Stop] = (Node){i, height[i]};
    }
    //stack<Node> S1;
    for (ll i = len - 1; i >= 1; i--)
    {
        while (S1top && S1[S1top].val > height[i])
        {
            S1top--;
            //S1.pop();
        }
        right[i] = S1top == 0 ? len - 1 : S1[S1top].pos - 1;
        S1[++S1top] = (Node){i, height[i]};
    }
    for (ll i = 1; i < len; i++)
    {
        ans -= 2LL * ((i - left[i] + 1) * (right[i] - i + 1)) * height[i];
        //printf("%d %d\n", left[i], right[i]);
    }
    printf("%lld\n", ans);
    system("pause");
    return 0;
}