#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int n;
bool mark[100000010];
int prime[10000000], primetot, ans;

void init(int x)
{
    for (int i = 2; i <= x; i++)
    {
        if (!mark[i])
        {
            prime[++primetot] = i;
            ll q = 1;
            while (q <= x)
                q *= i;
            q /= i;
            ans = (q * (ll)ans) % (ll)100000007;
        }
        for (int j = 1; j <= primetot; j++)
        {
            if (i * prime[j] > x)
                break;
            mark[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
        }
    }
}

int main()
{
    scanf("%lld", &n);
    ans = 1;
    init(n);
    printf("%d\n", ans);
    system("pause");
    return 0;
}