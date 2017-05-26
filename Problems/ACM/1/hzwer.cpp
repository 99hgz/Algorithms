#include <map>
#include <set>
#include <cmath>
#include <stack>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define mod 998244353
#define pi acos(-1)
#define inf 0x7fffffff
#define ll long long
using namespace std;
ll read()
{
    ll x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int n, blo;
int v[100005], bl[100005], atag[100005];
set<int> st[105];
void add(int a, int b, int c)
{
    for (int i = a; i <= min(bl[a] * blo, b); i++)
    {
        v[i] += c;
    }
    st[bl[a]].clear();
    for (int i = (bl[a] - 1) * blo + 1; i <= min(bl[a] * blo, n); i++)
        st[bl[a]].insert(v[i]);
    if (bl[a] != bl[b])
    {
        for (int i = (bl[b] - 1) * blo + 1; i <= b; i++)
        {
            v[i] += c;
        }
        st[bl[b]].clear();
        for (int i = (bl[b] - 1) * blo + 1; i <= min(bl[b] * blo, n); i++)
            st[bl[b]].insert(v[i]);
    }
    for (int i = bl[a] + 1; i <= bl[b] - 1; i++)
        atag[i] += c;
}
int query(int a, int b, int c)
{
    int ans = -1;
    for (int i = a; i <= min(bl[a] * blo, b); i++)
    {
        int val = v[i] + atag[bl[a]];
        if (val < c)
            ans = max(val, ans);
    }
    if (bl[a] != bl[b])
        for (int i = (bl[b] - 1) * blo + 1; i <= b; i++)
        {
            int val = v[i] + atag[bl[b]];
            if (val < c)
                ans = max(val, ans);
        }
    for (int i = bl[a] + 1; i <= bl[b] - 1; i++)
    {
        int x = c - atag[i];
        set<int>::iterator it = st[i].lower_bound(x);
        if (it == st[i].begin())
            continue;
        --it;
        ans = max(ans, *it + atag[i]);
    }
    return ans;
}
int main()
{
    freopen("lln.in", "r", stdin);
    freopen("lln.out", "w", stdout);
    n = read();
    blo = 1000;
    for (int i = 1; i <= n; i++)
        v[i] = read();
    for (int i = 1; i <= n; i++)
    {
        bl[i] = (i - 1) / blo + 1;
        st[bl[i]].insert(v[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        int f = read(), a = read(), b = read(), c = read();
        if (f == 0)
            add(a, b, c);
        if (f == 1)
            printf("%d\n", query(a, b, c));
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
