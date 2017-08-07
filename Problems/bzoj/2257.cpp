#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, m, a[1010], ans;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    map<int, int> mp;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= floor(sqrt(a[i])); j++)
        {
            if (a[i] % j == 0)
            {
                mp[j]++;
                mp[a[i] / j]++;
            }
        }
    }
    map<int, int>::iterator it;
    it = mp.begin();
    while (it != mp.end())
    {
        if (it->second >= m)
        {
            ans = max(ans, it->first);
        }
        it++;
    }
    printf("%d\n", ans);
    system("pause");
    return 0;
}