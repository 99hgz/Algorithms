#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
int used[1000010 + 10000];
int belong[1000010 + 10000];
vector<int> vec[1000010 + 10000];
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
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &a, &b);
        addedge(a, i + 10000);
        addedge(b, i + 10000);
    }
    for (i = 1; i <= 10000; i++)
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