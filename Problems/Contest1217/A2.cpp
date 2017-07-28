#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
typedef long long ll;
using namespace std;
char stra[300005], strb[300005];
ll lena, lenb, last;
ll next[300005][26], dictionary[26];
long long ans;
int main()
{
    scanf("%s", stra + 1);
    scanf("%s", strb + 1);
    ll lena = strlen(stra + 1);
    ll lenb = strlen(strb + 1);
    for (ll i = lena; i >= 1; i--)
    {
        memcpy(next[i], dictionary, sizeof(next[i]));
        dictionary[stra[i] - 'a'] = i;
    }
    for (ll i = 1; i <= lena; i++)
        if (stra[i] == strb[1])
        {
            ll p = i, t = 1;
            bool flag = 1;
            while (t < lenb)
            {
                p = next[p][strb[++t] - 'a'];
                if (p == 0)
                {
                    flag = 0;
                    break;
                }
            }
            if (!flag)
                continue;
            ans += (lena - p + 1) * (i - last);
            last = i;
        }
    printf("%lld\n", ans);
}