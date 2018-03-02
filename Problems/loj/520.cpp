#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n,a[100010];
ll ans2;
ll sqr(ll x){
    return x*x;
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    sort(a+1,a+1+n);
    //a[0]=1;
    for (int i = 3; i <= n; i+=2)
        ans2+=sqr(a[i]-a[i-2]);
    for (int i = 4; i <= n; i+=2)
        ans2+=sqr(a[i]-a[i-2]);
    ans2+=sqr(a[2]-a[1])+sqr(a[n]-a[n-1]);
    printf("%lld\n",ans2);
    system("pause");
    return 0;
}