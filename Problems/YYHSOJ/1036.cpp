#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int f[110][110][27];
int main()
{
    char st[110];
    int int_st[110], len, tmplen;
    int qjmin;
    while (scanf("%s", &st) != EOF)
    {
        len = strlen(st);
        tmplen = 1;
        int_st[1] = int(st[0]) - 96;
        memset(f, 127, sizeof(f));
        for (int i = 1; i <= len - 1; i++)
        {
            if (st[i] != st[i - 1])
            {
                int_st[++tmplen] = (int)(st[i]) - 96;
            }
        }
        len = tmplen;
        for (int i = 1; i <= len; i++)
        {
            for (int c = 1; c <= 26; c++)
            {
                if (int_st[i] == c)
                    f[i][i][c] = 0;
                else
                    f[i][i][c] = 1;
            }
        }

        for (int cs = 1; cs <= (len - 1); cs++)
        {
            for (int i = 1; i <= (len - cs); i++)
            {
                for (int k = i; k <= (i + cs); k++)
                {
                    for (int c = 1; c <= 26; c++)
                    {
                        f[i][i + cs][c] = min(f[i][k][c] + f[k + 1][i + cs][c], f[i][i + cs][c]);
                    }
                }
            }
            for (int i = 1; i <= (len - cs); i++)
            {
                qjmin = INT_MAX;
                for (int c = 1; c <= 26; c++)
                {
                    qjmin = min(f[i][i + cs][c], qjmin);
                }
                for (int c = 1; c <= 26; c++)
                {
                    if (f[i][i + cs][c] > qjmin)
                        f[i][i + cs][c] = qjmin + 1;
                }
            }
        }
        qjmin = INT_MAX;
        for (int c = 1; c <= 26; c++)
        {
            qjmin = min(f[1][len][c], qjmin);
        }
        printf("%d\n", qjmin + 1);
    }
    system("pause");
    return 0;
}