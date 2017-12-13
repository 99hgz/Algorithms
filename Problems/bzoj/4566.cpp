#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <algorithm>
using namespace std;
typedef long long ll;

const ll T = 1000000 + 5;

ll n, m, len;
char S1[200010], S2[200010], s[400010];
ll t1[T], t2[T], cc[T], x[T], sa[T], Rank[T], height[T];

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
map<int, int> mp;
ll ANS;
ll global_ans;
int len2;
void insert(int k)
{
    //printf("inserT:%d\n", k);
    mp[k]++;
    global_ans += k;
}
void modify(int k)
{
    map<int, int>::iterator it = mp.lower_bound(k);
    int delta = 0;
    while (it != mp.end())
    {
        global_ans -= (it->first) * (it->second);
        delta += (it->second);
        //delete it->second;
        it->second = NULL;
        mp.erase(it++);
    }
    //printf("modify:%d\n", k);
    mp[k] += delta;
    global_ans += k * delta;
}
int query()
{
    return global_ans;
}
void clear()
{
    global_ans = 0;
    mp.clear();
    //printf("CLEAR\n");
}

int main()
{
    freopen("F:/oj-data/find_2016/data1.in", "r", stdin);
    freopen("Z:/data1.out", "w", stdout);

    scanf("%s", S1 + 1);
    scanf("%s", S2 + 1);
    int len1 = strlen(S1 + 1);
    len2 = strlen(S2 + 1);
    len = strlen(S1 + 1) + strlen(S2 + 1) + 1;
    int pos = 0;
    for (int i = 1; i <= len1; i++)
        s[pos++] = S1[i];
    s[pos++] = '{';
    for (int i = 1; i <= len2; i++)
        s[pos++] = S2[i];
    make_sa();
    make_height();
    /*for (int i = 0; i <= len; i++)
        printf("%lld\n", sa[i]);*/
    int head = 0;
    for (int i = 0; i <= len - 1; i++)
        if (sa[i] < len1)
        {
            //printf("work:%d\n", i);
            ll rmq = 0x3f3f3f3f;
            for (int h = i; h >= head + 1; h--)
                rmq = min(rmq, height[h]);
            modify(rmq);
            rmq = 0x3f3f3f3f;
            for (int h = i; h >= head + 1; h--)
            {
                rmq = min(rmq, height[h]);
                if (sa[h - 1] >= len1)
                    insert(rmq);
            }
            head = i;
            ANS += query();
        }
    clear();

    head = len - 1;
    for (int i = len - 1; i >= 0; i--)
        if (sa[i] < len1)
        {
            //printf("work:%d\n", i);
            ll rmq = 0x3f3f3f3f;
            for (int h = head; h >= i + 1; h--)
                rmq = min(rmq, height[h]);
            modify(rmq);
            rmq = 0x3f3f3f3f;
            for (int h = i + 1; h <= head; h++)
            {
                rmq = min(rmq, height[h]);
                if (sa[h] >= len1)
                    insert(rmq);
            }
            head = i;
            ANS += query();
        }

    printf("%lld\n", ANS);

    system("pause");
    return 0;
}