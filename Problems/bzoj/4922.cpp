#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <stack>
using namespace std;
typedef long long ll;
char A[1000];
int n, P[1000], D[1000], sum, f[1000], dnum, pnum;

struct Node
{
    int a, d, len, plus;
} emy[1000];

bool cmp(int a, int b)
{
    if (emy[a].d == emy[b].d)
        return emy[a].a > emy[b].a;
    else
        return emy[a].d < emy[b].d;
}

bool cmp1(int a, int b)
{
    if (emy[a].a == emy[b].a)
        return emy[a].d < emy[b].d;
    else
        return emy[a].a > emy[b].a;
}

int main()
{
    scanf("%d", &n);
    int len;
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", A);
        len = strlen(A);
        int lk = 0, rk = 0;
        for (int j = 0; j < len; j++)
        {
            if (A[j] == ')')
                lk ? lk-- : rk++;
            else
                lk++;
        }
        emy[i].d = rk;
        emy[i].a = lk;
        emy[i].plus = lk - rk;
        emy[i].len = len;
        if (emy[i].plus > 0)
            P[++pnum] = i;
        else
            D[++dnum] = i;
        sum += lk;
    }
    sort(P + 1, P + 1 + pnum, cmp);
    sort(D + 1, D + 1 + dnum, cmp1);
    for (int i = 1; i <= sum; i++)
    {
        f[i] = -1000000;
    }
    for (int i = 1; i <= pnum; i++)
    {
        for (int j = sum; j >= emy[P[i]].d; j--)
            f[j + emy[P[i]].plus] = max(f[j + emy[P[i]].plus], f[j] + emy[P[i]].len);
    }
    for (int i = 1; i <= dnum; i++)
    {
        for (int j = emy[D[i]].d; j <= sum; j++)
            f[j + emy[D[i]].plus] = max(f[j + emy[D[i]].plus], f[j] + emy[D[i]].len);
    }
    printf("%d\n", f[0]);
    system("pause");
    return 0;
}