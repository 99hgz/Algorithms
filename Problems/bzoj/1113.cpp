#include <cstdio>
#include <stack>
using namespace std;
stack<int> s;
int x, y, n, cnt, w, k;
int main()
{
    scanf("%d%d", &n, &w);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &x, &y);
        if (y)
            k++;
        while (!s.empty() && y <= s.top())
        {
            if (y == s.top())
                cnt++;
            s.pop();
        }
        if (y != 0)
            s.push(y);
    }
    printf("%d", k - cnt);
    while (1)
    {
    }
}