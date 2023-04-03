#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
vector<int> ans;

int n;
char st1[2010], st2[2010];

void work(int x)
{
    ans.push_back(x);
    reverse(st1 + 1, st1 + 1 + n);
    reverse(st1 + x + 1, st1 + n + 1);
}

int main()
{
    scanf("%d", &n);
    scanf("%s", st1 + 1);
    scanf("%s", st2 + 1);
    for (int i = 1; i <= n; i++)
    {
        int k = 0;
        for (int j = 1; j <= n - i + 1; j++)
            if (st1[j] == st2[i])
            {
                k = j;
                break;
            }
        if (!k)
        {
            printf("-1\n");
            return 0;
        }
        work(n - k);
        work(1);
        work(n);
    }
    printf("%d\n", ans.size());
    for (int v : ans)
        printf("%d ", v);
    //system("pause");
    return 0;
}