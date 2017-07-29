#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
char A[100], B[100];
bool convert[26][26];
int m, n;
char ch1, ch2;
bool canconvert()
{
    int len1 = strlen(A);
    for (int i = 0; i < len1; i++)
    {
        if (!convert[A[i] - 'a'][B[i] - 'a'])
            return false;
    }
    return true;
}

typedef long long ll;

int main()
{
    scanf("%d%d\n", &m, &n);
    for (int i = 1; i <= m; i++)
    {
        scanf("%c %c\n", &ch1, &ch2);
        convert[ch1 - 'a'][ch2 - 'a'] = true;
    }
    for (int i = 1; i <= 26; i++)
    {
        convert[i - 1][i - 1] = true;
    }
    for (int k = 0; k < 26; k++)
    {
        for (int i = 0; i < 26; i++)
        {
            for (int j = 0; j < 26; j++)
            {
                convert[i][j] |= convert[i][k] & convert[k][j];
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        scanf("%s%s", A, B);
        int len1 = strlen(A);
        if (len1 != strlen(B))
        {
            printf("no\n");
            continue;
        }
        if (canconvert())
        {
            printf("yes\n");
        }
        else
        {
            printf("no\n");
        }
    }
    system("pause");
    return 0;
}