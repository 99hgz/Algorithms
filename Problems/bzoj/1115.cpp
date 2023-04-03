#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, sg;
int a[1010];
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        sg = 0;
        for (int i = n; i >= 1; i -= 2)
            sg ^= (a[i] - a[i - 1]);
        printf("%s\n", sg == 0 ? "NIE" : "TAK");
    }
    system("pause");
    return 0;
}