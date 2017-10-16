#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <stack>
#include <algorithm>
using namespace std;
typedef long long ll;

char A[500010];
int f[500010][2];
int main()
{
    scanf("%s", A + 1);
    int len = strlen(A + 1);
    stack<int> S;
    for (int i = len; i >= 1; i--)
    {
        if (A[i] == '0')
        {
            f[i][1] = 1;
            S.push(i);
        }
        else if (A[i] == '1')
        {
            int tmp = S.top();
            S.pop();
            f[i][1] = f[tmp][0] + 1;
            f[i][0] = f[tmp][1];
            S.push(i);
        }
        else
        {
            int l = S.top();
            S.pop();
            int r = S.top();
            S.pop();
            f[i][1] = f[l][0] + f[r][0] + 1;
            f[i][0] = max(f[l][0] + f[r][1], f[l][1] + f[r][0]);
            S.push(i);
        }
    }
    printf("%d ", max(f[1][1], f[1][0]));
    memset(f, 0, sizeof f);
    S.pop();
    for (int i = len; i >= 1; i--)
    {
        if (A[i] == '0')
        {
            f[i][1] = 1;
            S.push(i);
        }
        else if (A[i] == '1')
        {
            int tmp = S.top();
            S.pop();
            f[i][1] = f[tmp][0] + 1;
            f[i][0] = f[tmp][0];
            S.push(i);
        }
        else
        {
            int l = S.top();
            S.pop();
            int r = S.top();
            S.pop();
            f[i][1] = f[l][0] + f[r][0] + 1;
            f[i][0] = min(f[l][0] + f[r][1], f[l][1] + f[r][0]);
            S.push(i);
        }
    }
    printf("%d\n", min(f[1][1], f[1][0]));
    system("pause");
    return 0;
}