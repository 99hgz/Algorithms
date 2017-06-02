#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

#define MAX 100010
#define MAXCOST 0x7fffffff

ll graph[MAX][MAX];

ll prim(ll n)
{
    ll lowcost[MAX];
    ll i, j, min, minid, sum = 0;
    for (i = 2; i <= n; i++)
    {
        lowcost[i] = graph[1][i];
    }
    for (i = 2; i <= n; i++)
    {
        min = MAXCOST;
        minid = 0;
        for (j = 2; j <= n; j++)
        {
            if (lowcost[j] < min && lowcost[j] != 0)
            {
                min = lowcost[j];
                minid = j;
            }
        }
        sum += min;
        lowcost[minid] = 0;
        for (j = 2; j <= n; j++)
        {
            if (graph[minid][j] < lowcost[j])
            {
                lowcost[j] = graph[minid][j];
            }
        }
    }
    return sum;
}

int main()
{
    ll i, j, k, m, n;
    ll x, y, cost;
    scanf("%lld %lld", &m, &n);
    for (i = 1; i <= m; i++)
    {
        for (j = 1; j <= m; j++)
        {
            graph[i][j] = MAXCOST;
        }
    }
    for (k = 1; k <= n; k++)
    {
        scanf("%lld %lld %lld", &i, &j, &cost);
        graph[i][j] = cost;
        graph[j][i] = cost;
    }
    cost = prim(m);
    printf("%lld", cost);
    //system("pause");
    return 0;
}