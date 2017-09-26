#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <stack>
using namespace std;
typedef long long ll;
int n, newstrlen;
char A[1000], nS[1000];

int main()
{
    scanf("%d", &n);
    int len;
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", A);
        len = strlen(A);
        stack<char> S;
        for (int j = 0; j < len; j++)
        {
            if (A[j] == ')')
            {
                if (!S.empty())
                {
                    if (S.top() == '(')
                        S.pop();
                    else
                        S.push(')');
                }
                else
                    S.push(')');
            }
            else
            {
                S.push('(');
            }
        }
        int _newstrlen;
        _newstrlen = newstrlen = S.size();
        printf("%d\n", newstrlen);
        int l1 = 0, r1 = 0, lsl[i] = 0, rsl[i] = 0;
        while (!S.empty())
        {
            char ch = S.top();
            if (ch == '(')
                l1 = _newstrlen, lsl[i]++;
            if (ch == ')')
                r1 = _newstrlen, rsl[i]++;
            S.pop();
            _newstrlen--;
        }
    }
    f[0] = 0;

    system("pause");
    return 0;
}