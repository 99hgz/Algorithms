#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
char S[100][100];
int n, m, used[50010], belong[50010], T, ans, id[100][100], size[50010];
vector<int> vec[50010];
int calc(int x, int y)
{
    return (((x - 1) * m + y - 1));
}

void addedge(int x, int y)
{
    //printf("%d\n", y);
    vec[x].push_back(y);
}

bool find(int x)
{
    for (int j = 0; j < vec[x].size(); j++)
    {
        int v = vec[x][j];
        if (used[v] != T)
        {
            used[v] = T;
            if ((belong[v] == 0) || (find(belong[v])))
            {
                belong[v] = x;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    scanf("%d%d", &n, &m);
    int hid = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", S[i] + 1);
        hid++;
        for (int j = 1; j <= m; j++)
        {
            if (S[i][j] == '.')
                hid++;
            else
            {
                id[i][j] = hid;
            }
            //printf("%d ", hid);
        }
        //printf("\n");
    }
    int dhid = 0;
    for (int j = 1; j <= m; j++)
    {
        dhid++;
        for (int i = 1; i <= n; i++)
            if (S[i][j] == '.')
                dhid++;
            else
            {
                size[dhid]++;
                addedge(hid + dhid, id[i][j]);
            }
    }

    ans = 0;
    for (int i = 1; i <= dhid; i++)
    {
        if (size[i] != 0)
        {
            T++;
            if (find(hid + i))
                ans++;
        }
    }
    printf("%d\n", ans);

    system("pause");
    return 0;
}