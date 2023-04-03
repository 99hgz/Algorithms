#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

struct MT
{
    int n, m;
    ll mt[6][6];
    void print()
    {
        printf("print:%d*%d\n", n, m);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
                printf("%lld ", mt[i][j]);
            printf("\n");
        }
    }
} f[510], S, o, base[510];

int n, m;
char st[510];
int num[510];
ll p = 998244353;

MT operator*(MT a, MT b)
{
    MT c;
    c.n = c.m = m;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++)
        {
            ll res = 0;
            for (int k = 1; k <= m; k++)
                res = (res + a.mt[i][k] * b.mt[k][j]) % p;
            c.mt[i][j] = res;
        }
    return c;
}

MT operator+(MT a, MT b)
{
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++)
            a.mt[i][j] = (a.mt[i][j] + b.mt[i][j]) % p;
    return a;
}

MT power(MT a, int b)
{
    MT tmp;
    tmp.n = tmp.m = m;
    memset(tmp.mt, 0, sizeof tmp.mt);
    for (int i = 1; i <= m; i++)
        tmp.mt[i][i] = 1;
    while (b)
    {
        if (b & 1)
            tmp = tmp * a;
        a = a * a;
        b >>= 1;
    }
    return tmp;
}

void init()
{
    S.n = S.m = m;
    for (int i = 1; i <= m; i++)
        S.mt[i][1] = 1;
    for (int i = 1; i <= m - 1; i++)
        S.mt[i][i + 1] = 1;

    f[0].n = f[0].m = m;
    for (int i = 1; i <= m; i++)
        f[0].mt[i][i] = 1;

    o.n = o.m = m;
    memset(o.mt, 0, sizeof o.mt);

    base[0] = S;
    for (int i = 1; i <= 500; i++)
        base[i] = power(base[i - 1], 10);
}

void solve()
{
    for (int i = 1; i <= n; i++)
    {
        MT tmp = f[0];
        f[i] = o;
        for (int j = i - 1; j >= 0; j--)
        {
            tmp = tmp * power(base[i - j - 1], num[j + 1]);
            f[i] = f[i] + f[j] * tmp;
        }
    }
}

int main()
{
    scanf("%s", st + 1);
    scanf("%d", &m);
    n = strlen(st + 1);
    for (int i = 1; i <= n; i++)
        num[i] = st[i] - '0';
    init();
    solve();
    //f[n].print();
    printf("%lld\n", (f[n].mt[1][1] + p) % p);
    system("pause");
    return 0;
}