#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int ans, ANS[200], n;
int check(int x)
{
    int k = 0;
    while (x)
    {
        k += x % 10;
        x /= 10;
    }
    return k;
}

int main()
{
    scanf("%d", &n);
    for (int i = max(n - 100, 1); i <= n; i++)
    {
        if (check(i) == (n - i))
            ANS[++ans] = i;
    }
    printf("%d\n", ans);
    for (int i = 1; i <= ans; i++)
    {
        printf("%d\n", ANS[i]);
    }
    //system("pause");
    return 0;
}