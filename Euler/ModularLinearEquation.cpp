/*
 * @key word:求解模线性方程
 * @已测试:POJ - 1061
 * @Author: hgz 
 * @Date: 2017-04-25 09:39:32 
 * @Last Modified by: hgz
 * @Last Modified time: 2017-04-25 09:40:14
 */
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
typedef long long ll;

ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll r = exgcd(b, a % b, x, y);
    ll t = x;
    x = y;
    y = t - a / b * y;
    return r;
}

ll modular_linear_equation(ll a, ll b, ll n)
{
    ll x, y, x0, i;
    ll d = exgcd(a, n, x, y);
    if (b % d)
        return 0;
    x0 = x * (b / d) % n;
    return x0;
}

int main()
{
    ll x, y, m, n, l;
    cin >> x >> y >> m >> n >> l;
    ll tmp = modular_linear_equation(m - n, y - x, l);
    if (tmp == 0)
    {
        cout << "Impossible";
    }
    else
    {
        cout << (tmp + l) % l;
    }
}