#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, a[1000010], pos;
ll ans[30][2];
ll ANS;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        int x = a[i];
        for (int j = 0; j <= 25; j++)

        {
            ans[j][x % 2]++;
            //printf("%d %d\n", pos, x % 2);
            x /= 2;
        }
    }
    ll base = 1;
    for (int i = 0; i <= 25; i++)
    {
        ANS += base * (ans[i][0] * ans[i][1]);
        base *= 2;
    }
    printf("%lld\n", ANS);
    system("pause");
    return 0;
}