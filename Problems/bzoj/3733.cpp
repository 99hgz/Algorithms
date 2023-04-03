#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

void dfs(int num, int last, int used, int rest)
{
    if (rest == 1)
    {
        int p = 1;
        for (int i = used + 1; i <= tot; i++)
            p *= fac[i];
        if (p != last)
        {
            printf("TAK\n");
            found = true;
        }
        return;
    }
    if (found)
        return;
    int chose = 1;
    for (int i = used + 1; i <= tot - rest + 1; i++)
    {
        chose *= fac[i];
    }
}

int main()
{
    scanf("%d%d", &n, &k);
    k--;
    for (int i = 2; i * i <= n; i++)
        while ((n % i) == 0)
        {
            fac[++tot] = i;
            n /= i;
        }
    reverse(fac + 1, fac + 1 + tot);
    dfs(0, 0, 0, k);

    system("pause");
    return 0;
}