#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
using namespace std;

int ANS[10000];
struct Node
{
    int v, id;
};
int vec[60][60], indu[60];
bool vis[10000], hasson[60];
int n, anstot, tot;
char A[10];

int calc(char ch)
{
    return (ch >= 'A' && ch <= 'Z') ? ch - 'A' + 1 : ch - 'a' + 27;
}

char re(int x)
{
    return (x >= 1 && x <= 26) ? 'A' + x - 1 : 'a' + x - 27;
}

bool dfs(int x, int deep)
{
    ANS[deep] = x;
    //printf("anstot[%d]=%c\n", deep, re(x));
    bool son = false;
    for (int i = 1; i <= 52; i++)
    {
        if (vec[x][i] && !vis[vec[x][i]])
        {
            son = true;
            vis[vec[x][i]] = true;
            vis[vec[x][i] ^ 1] = true;
            if (dfs(i, deep + 1))
                return true;
            vis[vec[x][i]] = false;
            vis[vec[x][i] ^ 1] = false;
        }
    }
    if (!son)
    {
        if (deep == n + 1)
            return true;
        else
            return false;
    }
    return false;
}

int main()
{
    //printf("%d\n", calc('i'));
    scanf("%d", &n);
    tot = 2;
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", A);
        vec[calc(A[0])][calc(A[1])] = tot++;
        vec[calc(A[1])][calc(A[0])] = tot++;
        indu[calc(A[0])]++;
        indu[calc(A[1])]++;
        hasson[calc(A[0])] = true;
        hasson[calc(A[1])] = true;
    }
    //int start = 35;
    /*for (int i = 1; i <= 52; i++)
    {
        if (vec[i].size())
        {
            start = i;
            break;
        }
    }*/

    int cnt = 0;
    for (int i = 1; i <= 52; i++)
    {
        if (indu[i] % 2 == 1)
            cnt++;
    }
    if (cnt == 1 || cnt > 2)
    {
        printf("No Solution");
    }
    else
    {
        int start = 0;
        for (int i = 1; i <= 52; i++)
        {
            if (vis[i])
            {
                start = i;
                break;
            }
        }
        for (int i = 1; i <= 52; i++)
        {
            if (indu[i] % 2 == 1)
            {
                start = i;
                break;
            }
        }
        dfs(start, 1);
        for (int i = 1; i <= n + 1; i++)
        {
            printf("%c", re(ANS[i]));
        }
    }
    system("pause");
}