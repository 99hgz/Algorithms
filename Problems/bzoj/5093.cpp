#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;


int MOD=998244353;
int phi=998244353-1;
int pr=3;
int jc[1000010],inv[1000010],a[1000010],b[1000010],r[1000010],n,k,ans;
int s[1000010];
int pow(int a,int b){int s=1;while(b){if(b&1)s=1ll*s*a%MOD;a=1ll*a*a%MOD;b>>=1;}return s;}
inline int mt(int a){return ((a%MOD)+MOD)%MOD;}
void NTT(int *u,int v){
    for(int i=0;i<n;i++)
        if(i<r[i])
            swap(u[i],u[r[i]]);
    for(int i=1;i<n;i<<=1){
        int wn=pow(pr,phi/(i<<1));
        //printf("%d\n", wn);
        for(int j=0;j<n;j+=(i<<1)){
            int w=1;
            for(int k=0;k<i;k++,w=(ll)w*wn%MOD){
                int x=u[j+k],y=(ll)w*u[i+j+k]%MOD;
                u[j+k]=(x+y)%MOD;
                u[i+j+k]=(((x-y)%MOD)+MOD)%MOD;
            }
        }
    }
    if(v==-1){
        reverse(&u[1],&u[n]);
        int inv=pow(n,MOD-2);
        for(int i=0;i<n;i++)
            u[i]=(ll)u[i]*inv%MOD;
    }
}

void init(){
    jc[0]=inv[0]=1;
    for(int i=1;i<=k;i++){
        jc[i]=(ll)jc[i-1]*i%MOD;
        inv[i]=pow(jc[i],MOD-2);
    }
    for(int i=0;i<=k;i++){
        a[i]=(i&1)?MOD-inv[i]:inv[i];
        b[i]=(ll)pow(i,k)*inv[i]%MOD;
        
    }
    int m=2*k,l=0;
    for(n=1;n<=m;n<<=1)
        l++;
    for(int i=0;i<n;i++)
        r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
    NTT(a,1),NTT(b,1);
    for(int i=0;i<n;i++){
//printf("%d %d\n", a[i],b[i]);
        a[i]=(ll)a[i]*b[i]%MOD;
}
    NTT(a,-1);
    for(int i=0;i<=k;i++){
        s[i]=a[i];
        //printf("%d\n", s[i]);
    }
}

int main() {
    scanf("%d%d", &n,&k);
    int _n=n;
    init();
    n=_n;
    int inv2=pow(2,MOD-2);
    for(int i=0,p=pow(2,n-1),pp=1;i<=min(n-1,k);i++){
        int t=(ll)s[i]*pp%MOD*p%MOD;
        p=(ll)p*inv2%MOD;
        pp=(ll)pp*(n-1-i)%MOD;
        ans=(ans+t)%MOD;
    }
    ans=(ll)ans*n%MOD*pow(2,(ll)(n-1)*(n-2)/2%phi)%MOD;
    printf("%d\n", ans);
    //system("pause");
    return 0;
}