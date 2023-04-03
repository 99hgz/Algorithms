#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int hash[100100], sg[110][110], n, x, y, flag, ans;

bool check(int x, int y)
{
    return (x == y || x == 1 || y == 1) ? 0 : 1;
}

int getsg(int x, int y)
{
    int id = (x - 1) * 100 + y;
    for (int i = 1; i <= x - 1; i++)
        if (check(x - i, y))
            hash[sg[x - i][y]] = id;
    for (int i = 1; i <= y - 1; i++)
        if (check(x, y - i))
            hash[sg[x][y - i]] = id;
    for (int i = 1; i < min(x, y); i++)
        if (check(x - i, y - i))
            hash[sg[x - i][y - i]] = id;
    for (int i = 0;; i++)
        if (hash[i] != id)
            return i;
}

int main()
{
    for (int i = 1; i <= 100; i++)
        for (int j = 1; j <= 100; j++)
            sg[i][j] = getsg(i, j);
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        ans = flag = 0;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d", &x, &y);
            x++, y++;
            if (!check(x, y))
                flag = true;
            ans ^= sg[x][y];
        }
        if (ans || flag)
            printf("^o^\n");
        else
            printf("T_T\n");
    }
    system("pause");
    return 0;
}