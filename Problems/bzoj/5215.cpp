#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n,m,k,w[310],f[1000010];
ll MOD=1000000007;
int ans;
ll fac[10100000];

int pow1(ll a,int b){
    ll res=1;
    while(b){
        if(b&1)
            res=res*a%MOD;
    a=a*a%MOD;
        b>>=1;
    }
    return res;
}

void init(){
    fac[0]=1;
    for(int i=1;i<=n+k;i++)
        fac[i]=fac[i-1]*i%MOD;
}

ll C(int n,int m){
    return fac[m]*pow1(fac[n],MOD-2)%MOD*pow1(fac[m-n],MOD-2)%MOD;
}

int main() {
    scanf("%d%d%d", &n,&m,&k);
    for(int i=1;i<=m;i++){
        scanf("%d", &w[i]);
        w[i]++;
    }
    f[0]=1;
    init();
    for(int i=1;i<=m;i++)
        for(int k=300*m;k>=w[i];k--)
            if(f[k-w[i]])
                f[k]=(f[k]-f[k-w[i]]+MOD)%MOD;
    for(int i=0;i<=300*m;i++){
        if(i>k) break;
        ans=(ans+(ll)C(n-1,k-1+n-i)*f[i]%MOD)%MOD;
    }
    printf("%d\n", ans);
    system("pause");
    return 0;
}