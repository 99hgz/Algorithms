#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

ll a[500010],mu[500010],phi[500010],ans,presum[500010],prime[500010],tot,pre[500010],b,d,k,c,a1;
bool ist[50010];
void euler(int n){
    ist[0]=ist[1]=true;
    mu[1]=phi[1]=1;
    for(int i=2;i<=n;i++){
        if (!ist[i]){
            prime[++tot]=i;
            mu[i]=-1;
            phi[i]=i-1;
        }
        for(int j=1;j<=tot;j++){
            int t=i*prime[j];
            if (t>n) break;
            ist[t]=true;
            if (i%prime[j]==0){
                phi[t]=phi[i]*prime[j];
                mu[t]=0;
                break;
            }else{
                mu[t]=-mu[i];
                phi[t]=phi[i]*(prime[j]-1);
            }
        }
    }
    for(int i=1;i<=n;i++)
        pre[i]=pre[i-1]+mu[i];
}

ll F(int a,int b,int k){
    if (a>b) swap(a,b);
    ll res=0;
    a/=k,b/=k;
    for(ll i=1,last=1;i<=a;i=last+1){
        last=min(a/(a/i),b/(b/i));
        res+=(pre[last]-pre[i-1])*(a/i)*(b/i);
    }
    return res;
}

int main(){
    euler(50000);
    int T;
    scanf("%d",&T);
    while(T--){
    scanf("%lld%lld%lld%lld%lld",&a1,&b,&c,&d,&k);
    printf("%lld\n",F(b,d,k)-F(a1-1,d,k)-F(b,c-1,k)+F(a1-1,c-1,k));
    }
    system("pause");
}