#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, ans;
int prime[40000], primenum;
bool ist[40010];
void init_prime()
{
    for (int i = 2; i <= n; i++)
        if (!ist[i])
        {
            prime[++primenum] = i;
            for (int j = i * 2; j <= n; j += i)
                ist[j] = true;
        }
}

void dfs(int times, int plus, int last)
{
    if (times > n)
        return;
    for (int i = last + 1; i <= primenum; i++)
    {
        ans += plus * ((n / times) * (n / times));
        dfs(times * prime[i], -plus, i);
    }
}

int main()
{
    scanf("%d", &n);
    init_prime();
    dfs(1, 1, 0);
    printf("%d\n", ans);
    system("pause");
    return 0;
}