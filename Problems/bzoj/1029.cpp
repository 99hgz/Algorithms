#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
int needtime[150010], endtime[150010], id[150010];
bool cmp(int a, int b)
{
    return endtime[a] < endtime[b];
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &needtime[i], &endtime[i]);
        id[i] = i;
    }
    sort(id + 1, id + 1 + n, cmp);
    priority_queue<int> Q;
    int ans = 0, now = 0;
    for (int i = 1; i <= n; i++)
    {
        if (now + needtime[id[i]] <= endtime[id[i]])
            ans++, Q.push(needtime[id[i]]), now += needtime[id[i]];
        else
        {
            if (!Q.empty())
            {
                int tmp = Q.top();
                if (tmp >= needtime[id[i]] && needtime[id[i]] + now - tmp <= endtime[id[i]])
                {
                    Q.pop();
                    Q.push(needtime[id[i]]);
                    now = needtime[id[i]] + now - tmp;
                }
            }
        }
    }
    printf("%d\n", ans);
    system("pause");
    return 0;
}