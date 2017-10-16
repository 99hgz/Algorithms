#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;
#define gt greater<int>
multiset<int> rg;
priority_queue<int, vector<int>, gt> Q;
multiset<int> sorted;

int totin, n, m, a[500010], pos, val;
vector<int> vec[500010];
char A[20];

void st_insert(int x)
{
    Q.push(x);
    //printf("stinsert:%d\n", x);
}

void stinsert2(int x)
{
    if (totin == 0)
    {
        sorted.insert(x);
        totin++;
        return;
    }
    if (totin == 1)
    {
        st_insert(abs(x - *sorted.begin()));
    }
    else
    {
        if (x >= (*--sorted.end()))
        {
            st_insert(abs(x - (*--sorted.end())));
        }
        else if (x <= (*sorted.begin()))
        {
            st_insert(abs(x - (*sorted.begin())));
        }
        else
        {
            multiset<int>::iterator suc, pre;
            suc = pre = sorted.lower_bound(x);
            pre--;
            //printf("lb:%d %d %d\n", x, *pre, *suc);
            //st_erase(*suc - *pre);
            st_insert(abs(x - *suc));
            st_insert(abs(*pre - x));
        }
    }
    sorted.insert(x);
    totin++;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        vec[i].push_back(a[i]);
        stinsert2(a[i]);
        if (i == 1)
            continue;
        rg.insert(abs(a[i] - a[i - 1]));
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%s", A);
        if (A[0] == 'I')
        {
            scanf("%d%d", &pos, &val);
            int cd = vec[pos].size() - 1;
            if (pos == n)
            {
                rg.insert(abs(val - vec[pos][cd]));
            }
            else
            {
                rg.erase(rg.find(abs(vec[pos + 1][0] - vec[pos][cd])));
                rg.insert(abs(val - vec[pos][cd]));
                rg.insert(abs(vec[pos + 1][0] - val));
            }
            stinsert2(val);
            vec[pos].push_back(val);
        }
        else if (A[4] == 'S')
        {
            printf("%d\n", Q.top());
        }
        else
        {
            printf("%d\n", *rg.begin());
        }
    }
    system("pause");
    return 0;
}