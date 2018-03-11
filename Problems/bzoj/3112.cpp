#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
#define eps 1e-8
int n, m, op, tot, q[10010],l,r,k;
double a[10010][1010];

void Pivot(int x, int y)
{
    double tmp = a[x][y];
    a[x][y] = 1 / a[x][y];
    for (int i = 0; i <= n; i++)
        if (y != i)
            a[x][i] /= tmp;
    tot = 0;
    for (int i = 0; i <= n; i++)
        if (i != y && (a[x][i] > eps || a[x][i] < -eps))
            q[++tot] = i;

    for (int i = 0; i <= m; i++)
    {
        if ((x == i) || (a[i][y] < eps && a[i][y] > -eps))
            continue;
        for (int j = 1; j <= tot; j++)
            a[i][q[j]] -= a[x][q[j]] * a[i][y];
        a[i][y] = -a[i][y] / tmp;
    }
}

void simplex(){
    while (1)
    {
        int x = 0, y = 0;
        double mn = 1e15;
        for (int i = 1; i <= n; i++)
            if (a[0][i] > eps){y = i;break;}
        if (!y)
            break;
        for (int i = 1; i <= m; i++)
            if (a[i][y] > eps && a[i][0] / a[i][y] < mn)
                mn = a[i][0] / a[i][y], x = i;
        if (!x)
            return ;
        Pivot(x, y);
    }
}

int main()
{
    int _x,_y,_z;
    scanf("%d%d%d", &_x, &_y,&k);
    int rg=_y;
    n=_x;
    m=n-rg+1;
    for (int i = 1; i <= n; i++){
        scanf("%d", &r);
        a[0][i]=r;
    }
    for (int i = 1; i <= m; i++)
    {
        l++;
        for (int j = l; j <= l+rg-1; j++)
            a[i][j]=1;
        a[i][0]=k;
    }
    for (int i = m+1; i <= m+n; i++){
        a[i][i-m]=1;
        a[i][0]=1;
    }
    m+=n;
    simplex();
    printf("%d\n", int(-a[0][0]+0.5));
    system("pause");
    return 0;
}