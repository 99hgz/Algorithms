#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

ll a, b, c, ta, tb, tc;
ll _a, _b, _c;
ll f[110][110][110];
ll lcaa, lcab;
struct Finda
{
    ll a, b, c;
} Find[110];
void up(ll a, ll b, ll c)
{
    if ((b - a) < (c - b))
        _a = b, _b = 2 * b - a, _c = c;
    else
        _a = a, _b = 2 * b - c, _c = b;
}
ll work(ll i, ll j, ll k, ll a, ll b, ll c)
{
    //printf("%d %d %d %d %d %d\n", i, j, k, a, b, c);
    if ((i == 0) && (j == 0) && (k == 0))
    {
        return 1;
    }
    if (k == 0)
    {
        return 0;
    }
    if ((i + j) > k)
    {
        return 0;
    }
    if (f[i][j][k] != 0)
    {
        return f[i][j][k] % 1000000007;
    }
    if ((2 * b) == (a + c))
    {
        if (i > 0)
        {
            f[i][j][k] = (work(i + 1, j, k - 1, 2 * a - b, a, c) + work(i + 1, j, k - 1, a, c, 2 * c - b)) % 1000000007;
        }
        else if ((i == 0) && (j > 0))
        {
            f[i][j][k] = (work(i + 1, j, k - 1, 2 * a - b, a, c) + work(0, j - 1, k - 1, a, c, 2 * c - b)) % 1000000007;
        }
        else if ((i == 0) && (j == 0) && (k > 0))
        {
            f[i][j][k] = (work(1, 0, k - 1, 2 * a - b, a, c) + work(1, 0, k - 1, a, c, 2 * c - b)) % 1000000007;
        }
    }
    else
    {
        if (i > 0)
        {
            up(a, b, c);
            f[i][j][k] = (work(i - 1, j, k - 1, _a, _b, _c) + work(i + 1, j, k - 1, 2 * a - b, a, c) + work(i + 1, j, k - 1, a, c, 2 * c - b)) % 1000000007;
        }
        else if ((i == 0) && (j > 0))
        {
            up(a, b, c);
            f[i][j][k] = (work(0, j + 1, k - 1, _a, _b, _c) + work(1, j, k - 1, 2 * a - b, a, c) + work(0, j - 1, k - 1, a, c, 2 * c - b)) % 1000000007;
        }
        else if ((i == 0) && (j == 0) && (k > 0))
        {
            up(a, b, c);
            f[i][j][k] = (work(0, 1, k - 1, _a, _b, _c) + work(1, 0, k - 1, 2 * a - b, a, c) + work(1, 0, k - 1, a, c, 2 * c - b)) % 1000000007;
        }
    }
    return f[i][j][k] % 1000000007;
}

void lca(ll k)
{
    memset(f, 0, sizeof(f));
    ll i = 0;
    _a = a, _b = b, _c = c;
    Find[i].a = _a, Find[i].b = _b, Find[i].c = _c;
    while ((i <= k) && ((2 * _b) != (_a + _c)))
    {
        i++;
        up(_a, _b, _c);
        Find[i].a = _a, Find[i].b = _b, Find[i].c = _c;
    }
    _a = ta, _b = tb, _c = tc;
    ll i1 = 0, i2;
    while ((i1 <= k))
    {
        // printf("%d %d %d\n", _a, _b, _c);
        for (i2 = 0; i2 <= i; i2++)
        {
            if ((_a == Find[i2].a) && (_b == Find[i2].b) && (_c == Find[i2].c))
            {
                lcaa = i2, lcab = i1;
                return;
            }
        }
        //i1++;
        if (((2 * _b) == (_a + _c)))
        {
            lcaa = -1;
            lcab = -1;
            return;
        }
        i1++;
        up(_a, _b, _c);
    }
    lcaa = -1;
    lcab = -1;
}

int main()
{
    ll k;
    int t;
    scanf("%d", &t);
    while (t--)
    {
        _a = 0, _b = 0, _c = 0, lcaa = 0, lcab = 0;
        scanf("%lld%lld%lld", &a, &b, &c);
        scanf("%lld%lld%lld", &ta, &tb, &tc);
        scanf("%lld", &k);
        lca(k);
        if ((lcaa == -1) && (lcab == -1))
        {
            printf("0\n");
        }
        else
        {
            printf("%lld\n", work(lcaa, lcab, k, a, b, c));
        }
    }
    //system("pause");
    return 0;
}