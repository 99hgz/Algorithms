#include <cstdio>
#include <cstdlib>
#define MAXN 10000 + 10
using namespace std;

int par[MAXN], Rank[MAXN];
typedef struct
{
    int a, b, price;
} Node;
Node a[MAXN];

int cmp(const void *a, const void *b)
{
    return ((Node *)a)->price - ((Node *)b)->price;
}
void Init(int n)
{
    for (int i = 0; i < n; i++)
    {
        Rank[i] = 0;
        par[i] = i;
    }
}

int find(int x)
{
    int root = x;
    while (root != par[root])
        root = par[root];
    while (x != root)
    {
        int t = par[x];
        par[x] = root;
        x = t;
    }
    return root;
}

void unite(int x, int y)
{
    x = find(x);
    y = find(y);
    if (Rank[x] < Rank[y])
    {
        par[x] = y;
    }
    else
    {
        par[y] = x;
        if (Rank[x] == Rank[y])
            Rank[x]++;
    }
}
//n为边的数量，m为村庄的数量
int Kruskal(int n, int m)
{
    int nEdge = 0, res = 0;
    qsort(a, n, sizeof(a[0]), cmp);
    for (int i = 0; i < n && nEdge != m - 1; i++)
    {
        if (find(a[i].a) != find(a[i].b))
        {
            unite(a[i].a, a[i].b);
            res += a[i].price;
            nEdge++;
        }
    }
    if (nEdge < m - 1)
        res = -1;
    return res;
}
int main()
{
    int n, m, ans, k;
    scanf("%d %d %d", &m, &n, &k);
    Init(m + 1);
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d%d", &a[i].a, &a[i].b, &a[i].price);
    }
    ans = Kruskal(n, m - k + 1);
    if (ans == -1)
        printf("No Answer\n");
    else
        printf("%d\n", ans);
    //system("pause");
    return 0;
}
