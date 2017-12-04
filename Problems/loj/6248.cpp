#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b)
{
    return a == 0 ? b : gcd(b % a, a);
}
ll a, b, c;
int main()
{
    scanf("%lld%lld%lld", &a, &b, &c);
    ll tmp1 = a * b / gcd(a, b);
    //printf("%lld\n", tmp1);
    printf("%lld\n", tmp1 * c / gcd(tmp1, c));
    system("pause");
    return 0;
}