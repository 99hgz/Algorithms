#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

char st[100];
int f[210][210];

bool match(char a, char b)
{
    if (((a == '(') && (b == ')')) || ((a == '[') && (b == ']')))
        return true;
    else
        return false;
}

int main()
{
    scanf("%s", &st);
    int len = strlen(st);
    memset(f, 127, sizeof(f));
    f[0][0] = 1;
    for (int i = 1; i < len; i++)
    {
        f[i][i] = 1;
        if (match(st[i - 1], st[i]))
            f[i - 1][i] = 0;
        else
            f[i - 1][i] = 2;
    }
    bool pd;
    for (int cd = 2; cd <= len; cd++)
    {
        for (int j = 0; j <= (len - cd); j++)
        {
            pd = match(st[j], st[j + cd - 1]);
            if (pd)
                f[j][j + cd - 1] = min(f[j][j + cd - 1], f[j + 1][j + cd - 2]);
            for (int k = j; k <= (j + cd - 2); k++)
            {
                if (pd)
                    f[j][j + cd - 1] = min(f[j][k] + f[k + 1][j + cd - 1], f[j][j + cd - 1]);
                else
                    f[j][j + cd - 1] = min(f[j][k] + f[k + 1][j + cd - 1], f[j][j + cd - 1]);
            }
            //printf("%d %d %d\n", j, j + cd - 1, f[j][j + cd - 1]);
        }
    }
    printf("%d\n", f[0][len - 1] + len);
    system("pause");
    return 0;
}