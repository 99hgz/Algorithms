#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int n;
double p, ans, l1, l2;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lf", &p);
        ans += (3 * l1 + 3 * l2 + 1) * p;
        l2 = (l2 + 2 * l1 + 1) * p;
        l1 = (l1 + 1) * p;
    }
    printf("%.1lf\n", ans);
    system("pause");
    return 0;
}