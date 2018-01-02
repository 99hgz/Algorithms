#include<cstdio>
#include<algorithm>
#include<cstdlib>
using namespace std;
typedef long long ll;
int n,m;
ll a[500010],mu[500010],phi[500010],ans,presum[500010],prime[500010],tot;
ll MOD=1000000007;
bool ist[500010];
ll pow(ll a, ll b) {
  ll ans = 1;
  while (b > 0) {
    if (b & 1)
      ans = (ans * a)%MOD;
    a = (a * a)%MOD;
    b >>= 1;
  }
  return ans;
}

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
}
int main(){
    scanf("%d%d",&n,&m);
    if (n>m) swap(n,m);
    for(int i=1;i<=m;i++)
        a[i]=1;
    euler(m);
    for(int d=1;d<=n;d++){
        ll tmp=pow(d,d);
        for(int j=1;j<=m/d;j++)
            a[j]=a[j]*j%MOD,presum[j]=(presum[j-1]+a[j])%MOD;
        for(int k=1;k<=n/d;k++)
            ans=(((ans+tmp*a[k]%MOD*a[k]%MOD*mu[k]%MOD*presum[n/(d*k)]%MOD*presum[m/(d*k)]%MOD)%MOD)+MOD)%MOD;
    }
    printf("%lld\n",ans);
    system("pause");
}