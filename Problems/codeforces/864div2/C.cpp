#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int a, b, f, k, ans, now;
int main()
{
    scanf("%d %d %d %d", &a, &b, &f, &k);
    now = 0;
    int full = b;
    for (int i = 1; i <= k - 1; i++)
    {
        if (now == 0)
        {
            if (2 * a - f > b)
            {
                if (b < f)
                {
                    printf("-1\n");
                    return 0;
                }
                ans++;
                b = full - (a - f);
            }
            else
            {
                b -= a;
            }
            now = 1;
        }
        else
        {
            if (a + f > b)
            {
                if (b < (a - f))
                {
                    printf("-1\n");
                    return 0;
                }
                ans++;
                b = full - f;
            }
            else
            {
                b -= a;
            }
            now = 0;
        }
    }
    if (now == 0)
    {
        if (b < f)
        {
            printf("-1\n");
        }
        else
        {
            if (b < a)
            {
                ans++;
                if (full < (a - f))
                {
                    printf("-1\n");
                    return 0;
                }
            }
            printf("%d\n", ans);
        }
    }
    else
    {
        if (b < (a - f))
        {
            printf("-1\n");
        }
        else
        {
            if (b < a)
            {
                ans++;
                if (full < f)
                {
                    printf("-1\n");
                    return 0;
                }
            }
            printf("%d\n", ans);
        }
    }

    //system("pause");
    return 0;
}