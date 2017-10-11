#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
char S[2100];
int ans, sl[30];
int main()
{
    int n;
    scanf("%d", &n);
    scanf("%s", S);
    int len = strlen(S);
    S[len] = 'A';
    for (int i = 0; i <= len; i++)
    {
        if ('A' <= S[i] && S[i] <= 'Z')
        {
            int num = 0;
            for (int j = 1; j <= 26; j++)
            {
                if (sl[j])
                {
                    num++;
                }
            }
            ans = max(ans, num);
            memset(sl, 0, sizeof sl);
        }
        else
        {
            sl[S[i] - 'a' + 1]++;
        }
    }
    printf("%d\n", ans);
    //system("pause");
    return 0;
}