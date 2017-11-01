#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
int n, k, m, tmp;
vector<int> mp[100010];
int main()
{
    scanf("%d%d%d", &n, &k, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &tmp);
        mp[tmp % m].push_back(tmp);
    }
    bool flag = false;
    for (int i = 0; i < m; i++)
    {
        if (mp[i].size() >= k)
        {
            flag = true;
            printf("Yes\n");
            for (int j = 0; j < k; j++)
            {
                printf("%d ", mp[i][j]);
            }
            break;
        }
    }
    if (!flag)
    {
        printf("No\n");
    }
    //system("pause");
    return 0;
}