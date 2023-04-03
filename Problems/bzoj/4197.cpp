#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19};
int maxp = 8;

int n, MOD;
typedef pair<int, int> pr;
pr S[510];
int f[1 << 8][1 << 8], p[2][1 << 8][1 << 8];

int main()
{
    scanf("%d%d", &n, &MOD);
    for (int i = 2; i <= n; i++)
    {
        int j = i;
        for (int k = 0; k < maxp; k++)
            if (j % primes[k] == 0)
            {
                while (j % primes[k] == 0)
                    j /= primes[k];
                S[i - 1].second |= (1 << k);
            }
        S[i - 1].first = j;
    }
    sort(S + 1, S + n);
    f[0][0] = 1;
    for (int i = 1; i < n; i++)
    {
        if (i == 2 || S[i].first == 1 || S[i].first != S[i - 1].first)
        {
            memcpy(p[0], f, sizeof f);
            memcpy(p[1], f, sizeof f);
        }
        for (int s1 = (1 << maxp) - 1; s1 >= 0; s1--)
            for (int s2 = (1 << maxp) - 1; s2 >= 0; s2--)
            {
                if ((S[i].second & s2) == 0)
                    p[0][s1 | S[i].second][s2] = (p[0][s1 | S[i].second][s2] + p[0][s1][s2]) % MOD;
                if ((S[i].second & s1) == 0)
                    p[1][s1][s2 | S[i].second] = (p[1][s1][s2 | S[i].second] + p[1][s1][s2]) % MOD;
            }
        if (i == n || S[i].first == 1 || S[i].first != S[i + 1].first)
        {
            for (int s1 = (1 << maxp) - 1; s1 >= 0; s1--)
                for (int s2 = (1 << maxp) - 1; s2 >= 0; s2--)
                    f[s1][s2] = (((p[0][s1][s2] + p[1][s1][s2] - f[s1][s2]) % MOD) + MOD) % MOD;
        }
    }
    int ans = 0;
    for (int s1 = (1 << maxp) - 1; s1 >= 0; s1--)
        for (int s2 = (1 << maxp) - 1; s2 >= 0; s2--)
            if ((s1 & s2) == 0)
                ans = (ans + f[s1][s2]) % MOD;
    printf("%d\n", ans);
    system("pause");
    return 0;
}