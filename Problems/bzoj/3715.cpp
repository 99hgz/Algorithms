#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, w1, w2, h1, h2, minw, maxw, minh, maxh;
bool flag = false;
struct Node
{
    int w1, w2, h1, h2;
} a[100010];
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        minh = minw = 0x7f7f7f7f;
        maxh = maxw = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d%d%d", &w1, &w2, &h1, &h2);
            minw = min(minw, w1);
            maxw = max(maxw, w2);
            minh = min(minh, h1);
            maxh = max(maxh, h2);
            a[i] = (Node){w1, w2, h1, h2};
        }
        //printf("%d %d %d %d\n", minw, maxw, minh, maxh);
        flag = false;
        for (int i = 1; i <= n; i++)
        {
            if (a[i].w1 == minw && maxw == a[i].w2 && minh == a[i].h1 && maxh == a[i].h2)
            {
                flag = true;
                printf("TAK\n");
                break;
            }
        }
        if (!flag)
            printf("NIE\n");
    }
    system("pause");
    return 0;
}