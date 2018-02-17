#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

ll n,m;
ll gcd(ll a,ll b){
    return a==0?b:gcd(b%a,a);
}

int main() {
    scanf("%lld%lld", &n,&m);
    ll k=(n/gcd(n,m));
    ll ans=((k*m/n)-1)*(n/k);
    printf("%lld\n", ans);
    system("pause");
    return 0;
}