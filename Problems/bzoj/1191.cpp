#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
int used[20010];
int belong[20010];
vector<int> vec[20010];
int n, m, sl, b, ans, T;
bool find(int x)
{
    for (int k = 0; k < vec[x].size(); k++)
    {
        int j = vec[x][k];
        if ((used[j] != T))
        {
            used[j] = T;
            if ((belong[j] == 0) || (find(belong[j])))
            {
                belong[j] = x;
                return true;
            }
        }
    }
    return false;
}
void addedge(int u, int v)
{
    vec[u].push_back(v);
}
int main()
{
    int i = 1;
    int a, b;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &a, &b);
        addedge(i, a);
        addedge(i, b);
    }
    for (i = 1; i <= m; i++)
    {
        T++;
        //memset(used, 0, sizeof(used));
        if (find(i))
            ans++;
        else
            break;
    }
    printf("%d\n", ans);
    system("pause");
    return 0;
}