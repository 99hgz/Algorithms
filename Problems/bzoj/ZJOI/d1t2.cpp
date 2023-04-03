#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int a[60], n;

void add(int x)
{
    while (x)
    {
        a[x] = (a[x] + 1) % 2;
        x = x - (x & (-x));
    }
}

int find(int x)
{
    if (x == 0)
        return 0;
    int ans = 0;
    while (x <= n)
    {
        ans = (ans + a[x]) % 2;
        x = x + (x & (-x));
    }
    return ans;
}

int main()
{
    n = 5;
    add(3);
    for (int i = 1; i <= n; i++)
        printf("i=%d :pre=%d a=%d\n", i, find(i), a[i]);
    system("pause");
    return 0;
}