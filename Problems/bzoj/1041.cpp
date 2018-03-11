#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
ll r, cnt;
int main()
{
    scanf("%lld", &r);
    for (ll i = 1; i * i <= r * 2LL; i++)
    {
        if (2 * r % i != 0)
            continue;
        ll d = i, t = 2 * r / i;
        for (int j = 0; j < 2; j++)
        {
            for (ll a = 1; a * a < t / 2; a++)
            {
                double _b = sqrt(t - a * a);
                ll b = (ll)_b;
                if (abs((double)b - _b) <= 1e-6 && __gcd(a, b) == 1)
                    cnt++;
            }
            if (d != t)
                swap(d, t);
            else
                break;
        }
    }
    printf("%lld\n", cnt * 4 + 4);
    system("pause");
    return 0;
}