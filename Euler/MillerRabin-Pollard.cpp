/*
 * @key word:素数测试，质因数分解
 * @已测试:BZOJ - 4802
 * @Author: hgz 
 * @Date: 2017-04-25 09:58:26 
 * @Last Modified by: hgz
 * @Last Modified time: 2017-04-25 09:59:11
 */
#include <cmath>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

#define abs(x) ((x) < 0 ? -(x) : (x))

int cs = 50;

vector<ll> lists;

ll mod_mul(ll a, ll b, ll n)
{
    ll t;
    for (t = 0; b; a = (a << 1) % n, b >>= 1)
        if (b & 1)
            t = (t + a) % n;
    return t;
}

ll PowerMod(ll a, ll b, ll n)
{
    ll res = 1, temp = a % n;
    for (; b; b >>= 1, temp = mod_mul(temp, temp, n))
        if (b & 1)
            res = mod_mul(res, temp, n);
    return res;
}

bool ml(ll n)
{
    if (n == 2)
    {
        return true;
    }
    int t = 0;
    ll ran, pre, suc;
    ll tmp = n - 1;
    while ((tmp & 1) == 0)
    {
        t++;
        tmp >>= 1;
    }
    for (int i = 0; i < 50; i++)
    {
        ran = rand() % (n - 1) + 1;
        pre = PowerMod(ran, tmp, n);
        for (int j = 0; j < t; j++)
        {
            suc = mod_mul(pre, pre, n);
            if (suc == 1 && pre != 1 && pre != n - 1)
                return false;
            pre = suc;
        }
        if (pre != 1)
            return false;
    }
    return true;
}

ll Random(ll n)
{
    return ((double)rand() / RAND_MAX * n + 0.5);
}

ll gcd(ll a, ll b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

ll pr(ll n, ll b)
{
    ll x, y, d, i = 1, k = 2;
    x = Random(n - 1) + 1;
    y = x;
    while (1)
    {
        i++;
        x = (mod_mul(x, x, n) + b) % n;
        d = gcd(y - x, n);
        if (1 < d && d < n)
            return d;
        if (x == y)
            return n;
        if (i == k)
        {
            y = x;
            k <<= 1;
        }
    }
    return n;
}

void findFac(ll x)
{
    if (ml(x))
        return lists.push_back(x), void(0);
    ll p = x;
    while (p >= x)
    {
        p = pr(p, Random(p - 1) + 1);
    }
    findFac(p), findFac(x / p);
}

int main()
{
    srand(2252877);
    ll n;
    cin >> n;
    if (n == 1)
    {
        cout << 1;
        return 0;
    }
    if (ml(n))
    {
        cout << n - 1;
        return 0;
    }
    ll phi = n;
    findFac(n);
    sort(lists.begin(), lists.end());
    lists.erase(unique(lists.begin(), lists.end()), lists.end());
    for (vector<ll>::iterator i = lists.begin(); i != lists.end(); ++i)
    {
        phi = (phi / (*i)) * ((*i) - 1);
    }
    cout << phi;
    return 0;
}
