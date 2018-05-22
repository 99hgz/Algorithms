#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
ll MOD=1e9+7;

int n,k,det[4010],h[4010],b[4010],a[4010],f[4010],t[4010],ans[4010];


ll mt(ll k){
    //k+=MOD;
    if(k>=MOD) k-=MOD;
    return k;
    //return ((k%MOD)+MOD)%MOD;
}

void mul(int *x,int *y,int *z){
    for (int i = 0; i <= 2*k-2; i++) 
        t[i]=0;
    for(int i=0;i<k;i++)
        for(int j=0;j<k;j++)
            t[i+j]=mt(t[i+j]+(ll)x[i]*y[j]%MOD);
    for(int i=2*k-2;i>=k;i--){
        for(int j=k-1;j>=0;j--)
                t[i-k+j]=mt(t[i-k+j]+(MOD-(ll)t[i]*det[j])%MOD);
        t[i]=0;
    }
    for (int i = 0; i < k; i++) 
        z[i]=t[i];
}

int main() {
    scanf("%d%d", &n,&k);
    n++;
    for (int i = 1; i <= k; i++) {
        scanf("%d", &a[i]);
        mt(a[i]+MOD);
    }
    for (int i = 1; i <= k; i++) {
        scanf("%d", &h[i]);
        mt(h[i]+MOD);
    }
    //构造行列式
    det[k]=1;
    for (int i = 1; i <= k; i++) 
        det[k-i]=MOD-a[i];
    
    if(n<=k){
        printf("%d\n", h[n]);
        return 0;
    }

    //求m^n % f(x)的系数 卷积：快速幂/fft
    b[1]=1;
    ans[0]=1;
    int ts=n-k;
    for(;ts;mul(b,b,b),ts>>=1){
        
        if(ts&1)
            mul(ans,b,ans);
    }

    for (int i = k+1; i <= 2*k; i++) 
        for (int j = 1; j <= k; j++) 
            h[i]=mt(h[i]+(ll)a[j]*h[i-j]%MOD);
    ll res=0;
    for (int i = 0; i < k; i++) 
        res=mt(res+(ll)ans[i]*h[i+k]%MOD);
    printf("%lld\n", res);
    system("pause");
    return 0;
}