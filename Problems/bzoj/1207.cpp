#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, m, ans, time[10010], x[10010], y[10010], f[10010];
int main()
{
    ans = 1;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &time[i], &x[i], &y[i]);
        f[i] = 1;
        for (int j = 1; j < i; j++)
        {
            if ((time[i] - time[j]) >= (abs(x[i] - x[j]) + abs(y[i] - y[j])))
                f[i] = max(f[i], f[j] + 1), ans = max(ans, f[i]);
        }
    }
    printf("%d\n", ans);
    system("pause");
    return 0;
}