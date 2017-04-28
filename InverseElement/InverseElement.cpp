/*
 * @key word:逆元，扩展欧几里得
 * @已测试：HDU - 1576
 * @Author: http://blog.tk-xiong.com/archives/128 
 * @Date: 2017-04-24 21:17:36 
 * @Last Modified by: hgz
 * @Last Modified time: 2017-04-24 21:19:28
 */
#include <iostream>
using namespace std;

const int MOD = 9973;

long long extend_gcd(long long a, long long b, long long &x, long long &y)
{
    if (a == 0 && b == 0)
        return -1;
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    else
    {
        long long d = extend_gcd(b, a % b, y, x);
        y -= a / b * x;
        return d;
    }
}

long long mod_reverse(long long a, long long n)
{
    long long x, y;
    long long d = extend_gcd(a, n, x, y);
    if (d == 1)
        return (x % n + n) % n;
    else
        return -1;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n, B;
        cin >> n >> B;
        int x = mod_reverse(B, MOD);
        cout << n * x % MOD << endl;
    }
}