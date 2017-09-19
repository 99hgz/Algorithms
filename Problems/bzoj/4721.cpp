#include <cstdio>
#include <cstring>
#include <queue>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef int ll;
typedef long long ll2;
ll n, m, p, u, v, t, q;
ll init[100010];
struct Node
{
    ll t, val;
};
//queue<Node> Q[4];

inline ll llread()
{
    char ch = getchar();
    ll x = 0, f = 1;
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while ('0' <= ch && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

struct queue
{
    ll l, r;
    Node v[8000010];
    void push(Node x)
    {
        v[++r] = x;
    }
    Node front()
    {
        return v[l];
    }
    void pop()
    {
        l++;
    }
    bool empty()
    {
        return l > r ? true : false;
    }
} Q[4];

bool cmp(ll a, ll b) { return a > b; }

ll get_max(ll t)
{
    ll d = 0;
    ll2 m = -(1LL << 50);
    for (ll i = 1; i <= 3; i++)
    {
        if (Q[i].empty())
            continue;
        Node tmp = Q[i].front();
        if ((ll2)(tmp.val + (t - tmp.t) * q) > m)
        {
            m = (ll2)(tmp.val + (t - tmp.t) * q);
            d = i;
        }
    }
    Q[d].pop();
    return (ll)m;
}

int main()
{
    n = llread();
    m = llread();
    q = llread();
    u = llread();
    v = llread();
    t = llread();
    //scanf("%lld%lld%lld%lld%lld%lld", &n, &m, &q, &u, &v, &t);
    for (ll i = 1; i <= n; i++)
    {
        init[i] = llread();
        //scanf("%lld", &init[i]);
    }
    Q[3].l = Q[1].l = Q[2].l = 1;
    sort(init + 1, init + 1 + n, cmp);
    for (ll i = 1; i <= n; i++)
    {
        Q[1].push((Node){1, init[i]});
    }
    bool isfirst = true;
    for (ll i = 1; i <= m; i++)
    {
        ll k = get_max(i);
        Q[2].push((Node){i + 1, ll((ll2)k * u / v)});
        Q[3].push((Node){i + 1, k - ll((ll2)k * u / v)});
        if (i % t == 0)
            printf(isfirst ? "%d" : " %d", k), isfirst = false;
    }
    printf("\n");
    isfirst = true;
    for (ll i = 1; i <= n + m; i++)
    {
        ll k = get_max(m + 1);
        if (i % t == 0)
            printf(isfirst ? "%d" : " %d", k), isfirst = false;
    }
    system("pause");
    return 0;
}