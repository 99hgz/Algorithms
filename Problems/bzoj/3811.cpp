#include <cstdio>
#include <cstdlib>
using namespace std;
typedef unsigned long long ull;

ull a[100010];
int n, k;

namespace ke1
{
ull res;
void work()
{
    bool xs = false;
    for (int j = 0; j < 64; j++)
    {
        bool flag = false;
        for (int i = 1; i <= n; i++)
            if (a[i] >> j & 1)
            {
                flag = true;
                break;
            }
        if (!flag)
            continue;
        if (j == 0)
            xs = true;
        else
            res = res + (1ULL << (j - 1));
    }
    printf("%llu", res);
    printf("%s", xs ? ".5" : "");
}
}

namespace ke2
{
void work()
{
    ull half = 0, res = 0;
    ull s = 0;
    for (int i = 1; i <= n; i++)
        s |= a[i];

    for (int i = 0; i < 32; i++)
        for (int j = 0; j < 32; j++)
        {
            if ((!((s >> i) & 1)) || (!((s >> j) & 1)))
                continue;
            bool flag1 = false, flag2 = false;
            for (int id = 1; id <= n; id++)
            {
                if ((a[id] >> i & 1) != (a[id] >> j & 1)) //(0,1)||(1,0)
                    flag1 = true;
                if ((a[id] >> i & 1) && (a[id] >> j & 1)) //(1,1)
                    flag2 = true;
            }
            if (i + j - 1 - flag1 < 0)
                half++;
            else
                res += 1ULL << (i + j - 1 - flag1);
        }
    res += half >> 1;
    printf("%llu%s", res, half ? ".5" : "");
}
}
struct LB
{
    ull base[30], cnt;
    void insert(ull x)
    {
        for (int i = 22; i >= 0; i--)
            if ((x >> i) & 1)
                if (base[i])
                    x ^= base[i];
                else
                {
                    base[i] = x;
                    cnt++;
                    break;
                }
    }
} B;
namespace ke3
{

void work()
{
    ull ans = 0, res = 0;
    for (int i = 1; i <= n; i++)
        B.insert(a[i]);
    int cnt = 0;
    for (int i = 0; i <= 22; i++)
        if (B.base[i])
            B.base[cnt++] = B.base[i];
    int M = 1 << cnt;
    for (int i = 1; i < M; i++)
    {
        ull v = 0;
        for (int j = 0; j < cnt; j++)
            if (i >> j & 1)
                v = v ^ B.base[j];
        ull x = 0, y = 1;
        for (int j = 0; j < k; j++)
        {
            x *= v, y *= v;
            x += y >> cnt, y &= (M - 1);
        }
        ans += x, res += y;
        ans += res >> cnt, res &= (M - 1);
    }
    printf("%llu%s\n", ans, res ? ".5" : "");
}
}

int main()
{
    freopen("x:/malygos17.in", "r", stdin);
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%llu", &a[i]);
    if (k == 1)
        ke1::work();
    else if (k == 2)
        ke2::work();
    else
        ke3::work();
    system("pause");
}