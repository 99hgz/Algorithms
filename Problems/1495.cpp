#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;
priority_queue<int> Q;
int tmp, n;
char A[20];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", A);
        if (A[0] == 'A')
        {
            scanf("%d", &tmp);
            Q.push(-tmp);
        }
        else
        {
            if (Q.empty())
            {
                puts("ERROR");
                continue;
            }
            printf("%d\n", -Q.top());
            Q.pop();
        }
    }
    // system("pause");
    return 0;
}