#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int a[200], c[200], first[200];
int n, tmp, newnum;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &tmp);
        a[tmp]++;
        if (a[tmp] == 1)
            newnum++;
        if (newnum == 3)
        {
            printf("NO\n");
            return 0;
        }
    }
    for (int i = 1; i <= 100; i++)
    {
        if (a[i] > 0)
        {
            c[a[i]]++;
            if (c[a[i]] == 2)
            {
                printf("YES\n");
                printf("%d %d\n", first[a[i]], i);
                return 0;
            }
            first[a[i]] = i;
        }
    }
    printf("NO\n");
    //system("pause");
    return 0;
}