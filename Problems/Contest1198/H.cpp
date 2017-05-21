#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

bool isbest[50010];
int a[5010], b[5010], f[5010];
int n, i, j, k, MAX, num;
int main()
{
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    b[1] = 1;
    f[1] = 1;
    for (i = 2; i <= n + 1; i++)
    {
        MAX = 0;
        f[i] = 1;
        for (j = i - 1; j >= 1; j--)
            if (a[i] < a[j])
                if (b[j] > MAX)
                {
                    MAX = b[j];
                    memset(isbest, 1, sizeof(isbest));
                    isbest[a[j]] = 0;
                    f[i] = f[j];
                }
                else if (b[j] == MAX && isbest[a[j]])
                {
                    isbest[a[j]] = 0;
                    f[i] += f[j];
                }
        b[i] = MAX + 1;
    }
    printf("%d %d", b[n + 1] - 1, f[n + 1]);
    //system("pause");
}