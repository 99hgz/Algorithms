#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

ll n, m, t[100010], ans;
char op[100010][5];

ll calc(ll pos, ll x)
{
    for (ll i = 1; i <= n; i++)
    {
        if (op[i][0] == 'A')
            x = x & ((t[i] >> (pos - 1)) & 1);
        else if (op[i][0] == 'O')
            x = x | ((t[i] >> (pos - 1)) & 1);
        else if (op[i][0] == 'X')
            x = x ^ ((t[i] >> (pos - 1)) & 1);
    }
    return x;
}

int main()
{
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%s%lld", op[i], &t[i]);
    }
    for (ll i = 1; i <= 32; i++)
    {
        if ((ll)1 << (i - 1) <= m)
        {
            if (calc(i, 1) || calc(i, 0))
                ans |= ((ll)1 << (i - 1));
        }
        else if (calc(i, 0))
            ans |= ((ll)1 << (i - 1));
    }
    printf("%d\n", ans);
    system("pause");
    return 0;
}