#include <cstdio>
#include <cmath>
#include <cstdlib>
using namespace std;

int n, m, a[100010], res[100010], l, r;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    int head = 1;
    a[n + 1] = -100000;
    for (int i = 2; i <= n + 1; i++)
        if (!(abs(a[i] - a[i - 1]) <= 1))
        {
            for (int j = head; j < i; j++)
                res[j] = i - 1;
            head = i;
        }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &l, &r);
        printf("%s\n", res[l] >= r ? "YES" : "NO");
    }
    system("pause");
}
