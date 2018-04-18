#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=500000;
int MOD=998244353;
int phi=998244353-1;
int pr=3;
int n,k,l,r[N],a[N],b[N],c[N],d[N],e[N];

int pow(int a,int b){int s=1;while(b){if(b&1)s=1ll*s*a%MOD;a=1ll*a*a%MOD;b>>=1;}return s;}
inline int mt(int a){return ((a%MOD)+MOD)%MOD;}
void ntt(int *u,int v){
    for(int i=0;i<n;i++)
        if(i<r[i])
            swap(u[i],u[r[i]]);
    for(int i=1;i<n;i<<=1){
        int wn=pow(pr,phi/(i<<1));
        for(int j=0;j<n;j+=(i<<1)){
            int w=1;
            for(int k=0;k<i;k++,w=(ll)w*wn%MOD){
                int x=u[j+k],y=(ll)w*u[i+j+k]%MOD;
                u[j+k]=(x+y)%MOD;
                u[i+j+k]=(x-y+MOD)%MOD;
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
void trans(int *a,int *b){
    for (int i = 0; i <= k; i++) 
        c[i]=(a[i]+(i?((a[i-1]+b[i-1])%MOD):0))%MOD;
    for(int i=0;i<=k;i++)
        b[i]=a[i],a[i]=c[i];
}
void dfs(int x){
    if(x==2||x==1)
        return;
    if(x==3){
        trans(a,b);
        return;
    }
    int nxt=(x-(x&1))/2;
    dfs(nxt);
    ntt(a,1),ntt(b,1);
    for(int i=0;i<n;i++){
        c[i]=(ll)a[i]*a[i]%MOD;
        d[i]=(ll)a[i]*b[i]%MOD;
        e[i]=(ll)b[i]*b[i]%MOD;
    }
    ntt(c,-1),ntt(d,-1),ntt(e,-1);
    for(int i=0;i<=k;i++){
        a[i]=(c[i]+(i?e[i-1]:0))%MOD;
        b[i]=mt(mt(2*d[i]-(i?e[i-1]:0))-e[i]);
    }
    for(int i=k+1;i<n;i++)
        a[i]=b[i]=0;
    if(x&1) trans(a,b);  
}

int main() {
    scanf("%d%d", &n,&k);
    int _n=n,m=2*k;
    for(n=1;n<=m;n<<=1)l++;
    for(int i=0;i<n;i++)
        r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
    a[0]=a[2]=1;a[1]=3;
    b[0]=b[1]=1;
    dfs(_n);
    if(_n==1){
        for (int i = 1; i <= k; i++)
            printf("%d\n", b[i]);
        return 0;
    }
    for (int i = 1; i <= k; i++)
        printf("%d\n", a[i]);
    //system("pause");
    return 0;
}