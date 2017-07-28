#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;
vector<int> vec;
int k, n, tmp;
map<int, bool> map1;
int main()
{
    scanf("%d%d", &k, &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &tmp);
        map1[tmp] = true;
        vec.push_back(tmp);
    }
    sort(vec.begin(), vec.end());
    bool p = false;
    for (int i = 0; i < n; i++)
    {
        if (vec[i] >= (k / 2))
            break;
        if (vec[i] * 2 == k)
            break;
        if (map1[k - vec[i]])
        {
            p = true;
            printf("%d %d\n", vec[i], k - vec[i]);
        }
    }
    if (!p)
        printf("No Solution\n");
    system("pause");
    return 0;
}