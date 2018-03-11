#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n,k,a[2010],b[2010];
ll fac[2010],ifac[2010],inv[2010],f[2010][2010],g[2010];
ll MOD=1000000009;

ll C(ll a,ll b){
    return fac[a]*ifac[b]%MOD*ifac[a-b]%MOD;
}

int main() {
    scanf("%d%d", &n,&k);
    if ((n+k)&1){
        printf("0\n");
        return 0;
    }
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &b[i]);
    sort(a+1,a+1+n),sort(b+1,b+1+n);
    k+=(n-k)/2;
    inv[1]=1,fac[0]=ifac[0]=1;
    for (int i = 1; i <= n; i++){
        if (i!=1) inv[i]=(MOD-MOD/i)*inv[MOD%i]%MOD;
        fac[i]=fac[i-1]*i%MOD;
        ifac[i]=ifac[i-1]*inv[i]%MOD;
    }
    
    int cur=0;
    for (int i = 1; i <= n; i++){
        while(cur<n&&b[cur+1]<a[i]) cur++;
        g[i]=cur;
    }
    for (int i = 0; i <= n; i++)
        f[i][0]=1;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= g[i]; j++)
            f[i][j]=(f[i-1][j]+f[i-1][j-1]*(g[i]-j+1)%MOD)%MOD;
    }
    ll ans=0;
    for (int i = k; i <= n; i++)
        ans=(ans+(((i-k)&1)?-1:1)*fac[n-i]*f[n][i]%MOD*C(i,k)%MOD)%MOD;
    printf("%lld\n", (ans+MOD)%MOD);
    system("pause");
    return 0;
}