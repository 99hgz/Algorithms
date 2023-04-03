#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <map>
using namespace std;
typedef long long ll;

int n, lim = 8000000, inv6 = 166666668, MOD = 1e9 + 7;
map<int, int> M;
int phi[8000010], prime[8000010], primetot, sum[8000010];
bool mark[8000010];

void pre(int n)
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
    sum[1] = phi[1];
    for (int i = 2; i <= n; i++)
        (sum[i] = sum[i - 1] + (ll)i * phi[i] % MOD) %= MOD;
}

int work(int n)
{
    if (n <= lim)
        return sum[n];
    if (M[n])
        return M[n];
    ll res = (ll)n * (n + 1) % MOD * (2 * n + 1) % MOD * inv6 % MOD;
    int nxt;
    for (int i = 2; i <= n; i = nxt + 1)
    {
        nxt = n / (n / i);
        res = res - (ll)(i + nxt) * (nxt - i + 1) / 2 % MOD * work(n / i) % MOD;
        (res += MOD) %= MOD;
    }
    M[n] = res;
    return res;
}

int main()
{
    scanf("%d", &n);
    lim = min(lim, n);
    pre(lim);
    printf("1\n%d\n", work(n));
    system("pause");
    return 0;
}