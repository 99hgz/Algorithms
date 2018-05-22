#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int MOD=1000000007;
int inv2=500000004;
int f[100010],n,m,primenum,prime[10000],marked[100000],l,p;
ll pow(ll a,int b){
    ll res=1;
    while(b){
        if(b&1)
            res=res*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return res;
}
void fwt(){
    for(int i=1;i<l;i<<=1)
        for(int j=0,m=i<<1;j<l;j+=m)
            for(int k=0;k<i;k++){
                int l=f[j+k],r=f[i+j+k];
                f[j+k]=(l+r)%MOD;
                f[i+j+k]=(l-r+MOD)%MOD;
            }
}

void ufwt(){
    for(int i=1;i<l;i<<=1)
        for(int j=0,m=i<<1;j<l;j+=m)
            for(int k=0;k<i;k++){
                int l=f[j+k],r=f[i+j+k];
                f[j+k]=(ll)(l+r)*inv2%MOD;
                f[i+j+k]=(ll)(((l-r)*inv2%MOD)+MOD)%MOD;
            }
}

void getprime(int k){
    for(int i=2;i<=k;i++){
            if (!marked[i])
                prime[++primenum]=i;
            for(int j=1;j<=primenum;j++){
                if(i*prime[j]>k) break;
                marked[i*prime[j]]=true;
                if(i%prime[j]==0)
                    break;
            }
   }
}
int main() {
    getprime(50000);
    while(~scanf("%d%d", &n,&m)){
        memset(f,0,sizeof f);
        for(int i=1;i<=m;i++)
            f[i]=(1-marked[i]);
        f[1]=0;
        for(l=1;l<=m;l<<=1,p++);
        fwt();
        for(int i=0;i<l;i++)
            if(f[i])f[i]=pow(f[i],n);
        ufwt();
        printf("%d\n", f[0]);
    }
    system("pause");
    return 0;
}