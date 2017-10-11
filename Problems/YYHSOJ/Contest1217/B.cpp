#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

ll n, SB[100005];
ll a[100005], count1, L, vec[100005], num;
int main()
{
    scanf("%lld", &n);
    if (n > 10000)
    {
        cout << "Fuck the data" << endl;
        return 0;
    }
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    SB[1] = a[1], count1 = 1;
    for (ll i = 2; i <= n; i++)
    {
        if (a[i] >= SB[count1])
            SB[++count1] = a[i];
        else
        {
            ll pos = lower_bound(SB + 1, SB + count1, a[i]) - SB;
            SB[pos] = a[i];
        }
    }
    cout << count1 << endl;
    L = count1;
    memset(SB, 0, sizeof(SB));
    SB[1] = a[2], count1 = 1;
    for (ll i = 3; i <= n; i++)
    {
        if (a[i] >= SB[count1])
            SB[++count1] = a[i];
        else
        {
            ll pos = lower_bound(SB + 1, SB + count1, a[i]) - SB;
            SB[pos] = a[i];
        }
    }
    if (count1 < L)
        vec[++num] = 1;
    for (ll pp = 2; pp <= n; pp++)
    {
        memset(SB, 0, sizeof(SB));
        SB[1] = a[1], count1 = 1;
        for (ll i = 2; i <= n; i++)
        {
            if (i == pp)
                continue;
            if (a[i] >= SB[count1])
                SB[++count1] = a[i];
            else
            {
                ll pos = lower_bound(SB + 1, SB + count1, a[i]) - SB;
                SB[pos] = a[i];
            }
        }
        if (count1 < L)
            vec[++num] = pp;
    }
    //system("pause");
    for (ll i = 1; i < num; i++)
        cout << vec[i] << ' ';
    cout << vec[num] << ' ';
    return 0;
}