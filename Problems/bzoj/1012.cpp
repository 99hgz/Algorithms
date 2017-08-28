#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int m, d, n, old, top, num, stacks[200001], list[200001];
char ch[10];
int main()
{
    scanf("%d%d", &m, &d);
    for (int i = 1; i <= m; i++)
    {
        scanf("%s%d", ch, &n);
        if (ch[0] == 'A')
        {
            n = (n + old) % d;
            list[++num] = n;
            while (top && list[stacks[top]] <= list[num])
                top--;
            stacks[++top] = num;
        }
        else
        {
            int tmp = lower_bound(stacks + 1, stacks + top + 1, num - n + 1) - stacks;
            printf("%d\n", old = list[stacks[tmp]]);
        }
    }
    system("pause");
    return 0;
}