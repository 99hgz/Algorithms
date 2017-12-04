#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
#define MAX 200008
typedef unsigned long long ULL;
ULL H[MAX], A[MAX];
int main()
{
    int i, n;
    ULL sum, S, L, h, dif, temp, max;
    ULL left, right, mid;
    scanf("%d%lld%lld", &n, &S, &L);
    for (i = 0; i < n; i++)
    {
        scanf("%lld", &H[i]);
    }
    for (i = 0; i < n; i++)
    {
        scanf("%lld", &A[i]);
    }

    if (S > L)
    {
        temp = S;
    }
    else
    {
        temp = L;
    }
    for (i = 0, max = 0; i < n; i++)
    {
        dif = (temp - H[i]) / A[i];
        if ((temp - H[i]) % A[i] != 0)
        {
            dif++;
        }
        if (dif > max)
        {
            max = dif;
        }
    }
    left = 0, right = max;
    while (left < right)
    {
        mid = left + (right - left) / 2;
        for (i = 0, sum = 0; i < n; i++)
        {
            h = H[i] + A[i] * mid;
            if (h >= L)
            {
                sum += h;
            }
        }
        if (sum < S)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }
    printf("%lld\n", right);
    return 0;
}