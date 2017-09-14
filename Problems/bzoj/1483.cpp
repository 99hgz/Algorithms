#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
#define maxn 1000005
int pos[maxn], tot, Next[maxn], Head[maxn], size[maxn], a[maxn], n, x, y, cases, m, ans, cg[maxn];
int f[maxn];
void insert(int x, int p)
{
    tot++;
    size[x]++;
    pos[tot] = p;
    Next[tot] = Head[x];
    Head[x] = tot;
}

void insertnode(int x, int node)
{
    size[x]++;
    Next[node] = Head[x];
    Head[x] = node;
}

void merge(int x, int y, int changetime)
{
    if (x == y)
        return;
    bool swaphead = false;
    if (size[f[x]] > size[f[y]])
    {
        swap(f[x], f[y]);
        swaphead = true;
    }
    x = f[x];
    y = f[y];
    //printf("change%d to %d\n", x, y);
    int thisNext;
    for (int i = Head[x]; i; i = thisNext)
    {
        if (y == a[pos[i] - 1] && cg[pos[i] - 1] < changetime)
            ans--;
        if (y == a[pos[i] + 1] && cg[pos[i] + 1] < changetime)
            ans--;
        thisNext = Next[i];
        a[pos[i]] = y;
        cg[pos[i]] = changetime;
        insertnode(y, i);
    }
    /*if (swaphead)
    {
        Head[x] = Head[y];
        size[x] = size[y];
        size[y] = 0;
        Head[y] = 0;
    }
    else
    {
        size[x] = 0;
        Head[x] = 0;
    }*/
    size[x] = 0;
    Head[x] = 0;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        insert(a[i], i);
        f[a[i]] = a[i];
        if (a[i] != a[i - 1])
            ans++;
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &cases);
        if (cases == 2)
        {
            printf("%d\n", ans);
        }
        else
        {
            scanf("%d%d", &x, &y);
            merge(x, y, i);
        }
        /*for (int j = 1; j <= n; j++)
        {
            printf("%d ", a[j]);
        }
        printf("\n");*/
    }
    system("pause");
    return 0;
}