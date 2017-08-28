#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, tmp, a[100010], tree[100010], pos[100010], len, list[20];

int lowbit(int x) { return x & -x; }

void setnum(int x, int a)
{
    for (; x <= n; x += lowbit(x))
    {
        tree[x] = max(tree[x], a);
    }
}

int getmax(int x)
{
    int res = 0;
    for (; x; x -= lowbit(x))
    {
        res = max(res, tree[x]);
    }
    return res;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &tmp);
        pos[tmp] = i;
    }
    for (int i = 1; i <= n; i++)
    {
        int len = 0;
        for (int j = a[i] - 4; j <= a[i] + 4; j++)
        {
            if (j > 0 && j <= n)
                list[++len] = pos[j];
        }
        sort(list + 1, list + 1 + len);
        for (int j = len; j >= 1; j--)
        {
            setnum(list[j], getmax(list[j] - 1) + 1);
        }
    }
    printf("%d\n", getmax(n));
    system("pause");
    return 0;
}