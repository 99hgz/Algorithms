#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int n;
int phi[40005], prime[40005], primetot, ans;
bool mark[40005];
void getphi(int n)
{
    phi[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (!mark[i])
        {
            prime[++primetot] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= primetot; j++)
        {
            if (i * prime[j] > n)
                break;
            mark[i * prime[j]] = true;
            if (i % prime[j] == 0)
            {
                phi[i * prime[j]] = phi[i] * (prime[j]);
                break;
            }
            else
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
}

int main()
{
    scanf("%d", &n);
    getphi(n);
    for (int i = 1; i < n; i++)
    {
        ans += phi[i];
    }
    printf("%d\n", 2 * ans + 1);
    system("pause");
    return 0;
}