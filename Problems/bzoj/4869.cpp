#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

#define mid ((l + r) >> 1)
#define lc x << 1
#define rc x << 1 | 1
#define lson lc, l, mid
#define rson rc, mid + 1, r
const int N = 5e4 + 5;

int n, Q, p, c, a[N], op, l, r, phi[100], m, MOD;
int Phi(int n)
{
    int m = sqrt(n), ans = n;
    for (int i = 2; i <= m; i++)
        if (n % i == 0)
        {
            ans = ans / i * (i - 1);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        ans = ans / n * (n - 1);
    return ans;
}

int Pow(ll a, int b, ll MOD, bool &flag)
{
    ll ans = 1;
    bool big = 0;
    for (; b; b >>= 1)
    {
        if (b & 1)
        {
            ans = ans * a;
            flag |= big | (ans >= MOD);
            ans %= MOD;
        }
        a = a * a;
        if (a >= MOD)
            big = 1, a %= MOD;
    }
    return ans;
}

int cal(int x, int ci)
{
    if (x >= phi[ci])
        x = x % phi[ci] + phi[ci];
    for (int i = ci - 1; i >= 0; i--)
    {
        bool flag = 0;
        x = Pow(c, x, phi[i], flag);
        if (flag)
            x += phi[i];
    }
    return x % phi[0];
}

struct meow
{
    int sum, ci;
} t[N << 2];
void merge(int x)
{
    t[x].sum = (t[lc].sum + t[rc].sum) % MOD;
    t[x].ci = min(t[lc].ci, t[rc].ci);
}
void build(int x, int l, int r)
{
    if (l == r)
        t[x].sum = a[l];
    else
    {
        build(lson);
        build(rson);
        merge(x);
    }
}
void modify(int x, int l, int r, int ql, int qr)
{
    if (t[x].ci >= m)
        return;
    if (l == r)
        t[x].ci++, t[x].sum = cal(a[l], t[x].ci);
    else
    {
        if (ql <= mid)
            modify(lson, ql, qr);
        if (mid < qr)
            modify(rson, ql, qr);
        merge(x);
    }
}
int query(int x, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
        return t[x].sum;
    else
    {
        int ans = 0;
        if (ql <= mid)
            ans = (ans + query(lson, ql, qr)) % MOD;
        if (mid < qr)
            ans = (ans + query(rson, ql, qr)) % MOD;
        return ans;
    }
}

int main()
{
    scanf("%d%d%d%d", &n, &Q, &p, &c);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    MOD = phi[0] = p;
    while (p != 1)
        phi[++m] = p = Phi(p);
    phi[++m] = 1;
    build(1, 1, n);
    for (int i = 1; i <= Q; i++)
    {
        scanf("%d%d%d", &op, &l, &r);
        if (op == 0)
            modify(1, 1, n, l, r);
        else
            printf("%d\n", query(1, 1, n, l, r));
    }
    system("pause");
    return 0;
}