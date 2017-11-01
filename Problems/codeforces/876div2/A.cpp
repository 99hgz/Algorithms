#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, a, b, c, tmp, ans;
int main()
{
    scanf("%d%d%d%d", &n, &a, &b, &c);
    if (n == 1)
    {
        printf("0\n");
        return 0;
    }
    if (a > b)
        swap(a, b);
    ans = a + (n - 2) * min(a, min(b, c));
    printf("%d\n", ans);
    system("pause");
    return 0;
}