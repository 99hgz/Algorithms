#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
int n, a[200100], p[200100];
bool flag[200100];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        p[a[i]]++;
    }
    for (int i = 1; i <= n; i++)
        flag[i] = false;
    int now = 1, ans = 0;
    for (int i = 1; i <= n; i++)
    {
        while (p[now] != 0)
        {
            now++;
            if (now > n)
                break;
        }
        if (now > n)
            break;
        if (p[a[i]] == 1)
            continue;
        if (flag[a[i]])
        {
            ans++, a[i] = now, p[now]++, now++;
            continue;
        }
        if (now < a[i])
        {
            p[a[i]]--, a[i] = now, p[now]++, ans++;
            continue;
        }
        flag[a[i]] = true;
    }
    printf("%d\n", ans);
    for (int i = 1; i <= n; i++)
        printf("%d%c", a[i], " \n"[i == n]);
    return 0;
}
