#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int k, ANS, MOD, f[1100000], MAX;
char A[5000010];
int get(char s)
{
    if (s == 'A')
        return 0;
    if (s == 'G')
        return 1;
    if (s == 'C')
        return 2;
    if (s == 'T')
        return 3;
}

int main()
{
    scanf("%s", A + 1);
    scanf("%d", &k);
    int len = strlen(A + 1);
    ANS = 0;
    MOD = 1;
    for (int i = 1; i <= k - 1; i++)
    {
        MOD *= 4;
    }
    for (int i = 1; i <= len; i++)
    {
        if (i >= k)
        {
            ANS = ANS % MOD;
            ANS = ANS * 4 + get(A[i]);
            f[ANS]++;
            if (f[ANS] > MAX)
                MAX = f[ANS];
        }
        else
        {
            ANS = ANS * 4 + get(A[i]);
        }
    }
    printf("%d\n", MAX);
    system("pause");
    return 0;
}