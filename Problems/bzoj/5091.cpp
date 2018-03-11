#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n,m,k,a[100010],u,v,d[100010];
ll ans,MOD=1000000007;
ll pow(ll a,int b){
    ll res=1;
    while(b){
        if (b&1)
            res=res*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return res;
}

int main() {
    scanf("%d%d%d", &n,&m,&k);
    for (int i = 1; i <= n; i++)
        scanf("%d",&a[i]);
    for (int i = 1; i <= m; i++){
        scanf("%d%d", &u,&v);
        d[u]++,d[v]++;
    }
    for (int i = 1; i <= n; i++)
        ans=(ans+(ll)a[i]*d[i]*k)%MOD;
    ans=(ans*pow(2*m,MOD-2))%MOD;
    printf("%lld\n", ans);
    system("pause");
    return 0;
}