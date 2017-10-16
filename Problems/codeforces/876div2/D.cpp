#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, t[300010], k, l, ANS[300010];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &t[i]);
    }
    l = 0;
    for (int i = n; i >= 1; i--)
    {
        ANS[i] = i - (n - l) + 1;
        l = max(l, t[i]);
    }
    printf("%d ", 1);
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", ANS[i]);
    }

    //system("pause");
    return 0;
}