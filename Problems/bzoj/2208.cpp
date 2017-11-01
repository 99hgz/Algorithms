#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <bitset>
using namespace std;
bitset<2005> f[2005];
int n, res;
void floyd()
{
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            if (f[i].test(k))
                f[i] |= f[k];
    for (int i = 0; i < n; i++)
        res += f[i].count();
}
char A[2005];
int main()
{
    int p = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%s", A);
        for (int j = 0; j < n; j++)
        {
            f[i][j] = (A[j] == '1' || i == j) ? 1 : 0;
        }
    }
    floyd();
    printf("%d\n", res);
    //system("pause");
}