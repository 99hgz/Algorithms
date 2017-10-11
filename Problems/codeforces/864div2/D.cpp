#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, a[300100], b[300100], times[300100], changes[300100];
int ans, now;
bool getnextzero()
{
    while (times[now] != 0)
    {
        now++;
        if (now > n)
            return true;
    }
    return false;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        b[i] = a[i];
        times[a[i]]++;
    }
    now = 1;
    for (int i = 1; i <= n; i++)
    {
        if (getnextzero())
        {
            break;
        }
        int v = a[i];
        if (times[v] == 1)
            continue;
        if (!changes[v] && now >= v)
        {
            changes[v] = true;
            continue;
        }
        if (changes[v])
        {
            b[i] = now;
            times[now]++;
            now++;
        }
        else if (now < v)
        {
            times[v]--, times[now]++;
            b[i] = now;
        }
        ans++;
    }
    printf("%d\n", ans);
    for (int i = 1; i <= n - 1; i++)
    {
        printf("%d ", b[i]);
    }
    printf("%d\n", b[n]);
    //system("pause");
    return 0;
}