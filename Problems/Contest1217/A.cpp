#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int count2, count1, f[300100][26];
char A[300100], B[210];
int jump(int i, int x)
{
    //printf("%d %d\n", i, x);
    if (x == count1 - 1)
        return f[i][B[x] - 'a'];
    else if (f[i][B[x] - 'a'] == -1)
        return -1;
    else
        return jump(f[i][B[x] - 'a'], x + 1);
}

int main()
{
    memset(f, -1, sizeof f);

    scanf("%s", A);
    scanf("%s", B);
    count2 = strlen(A);
    count1 = strlen(B);
    for (int i = count2 - 1; i >= 0; i--)
    {
        for (int j = 25; j >= 0; j--)
        {
            if ((A[i] - 'a') == j)
            {
                f[i][j] = i;
            }
            else
            {
                f[i][j] = f[i + 1][j];
            }
            //printf("%d %d %d\n", i, j, f[i][j]);
        }
    }
    ll ans = 0;

    for (int i = 0; i < count2; i++)
    {
        int last = jump(i, 0);
        //printf("----\n");
        if (last == -1)
            break;
        //printf("%d %d\n", i, last);
        ans += count2 - last;
    }
    printf("%lld\n", ans);
    system("pause");
    return 0;
}