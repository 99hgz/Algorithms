#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, len, Next[1000010], Dep[1000010];
ll P = 1000000007;
char s[1000010];
void calc()
{
    int i = 1, j = 0;
    Next[1] = 0, Dep[1] = 0;
    while (i <= len)
        if (j == 0 || s[i] == s[j])
        {
            Next[++i] = ++j;
            Dep[i] = Dep[j] + 1;
        }
        else
            j = Next[j];
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", s + 1);
        len = strlen(s + 1);
        calc();
        ll ans = 1;
        int i1 = 1, j = 0;
        while (i1 <= len)
            if (j == 0 || s[i1] == s[j])
            {
                i1++, j++;
                while (j != 0 && ((j - 1) << 1) > (i1 - 1))
                    j = Next[j];
                if (j)
                    ans = ans * (Dep[j] + 1) % P;
            }
            else
                j = Next[j];
        printf("%lld\n", ans);
    }
    system("pause");
    return 0;
}