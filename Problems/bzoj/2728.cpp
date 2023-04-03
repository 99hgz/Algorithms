#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

ll jc[70],a[1010],jhnum,n,k,l,r,u[1010];

bool check(ll x,ll y){
    for(ll i=1;i<=n;i++)
        if(((a[i]>>x)^(a[i]>>y))&1)
            return false;
    return true;    
}

ll query(ll x){
    if(x>=(1LL<<k)) return 1LL<<jhnum;
    ll ans=0;
    ll jh=jhnum;
    memset(jc,-1,sizeof jc);
    for(ll i=k-1;i>=0;i--){
        ll j=u[i];
        if((x>>i)&1){
            if(jc[j]==-1)
                jc[j]=1,jh--,ans+=(1LL<<jh);
            else if(jc[j]==0){
                ans+=(1LL<<jh);
                break;
            }
        }else{
            if(jc[j]==-1)
                jc[j]=0,jh--;
            else if(jc[j]==1)
                break;
        }
    }
    return ans;
}

int main() {
    //freopen("bzoj_2728.in", "r", stdin);
    //freopen("bzoj_2728.out", "w", stdout);
    
    scanf("%lld%lld%lld%lld", &n,&k,&l,&r);
    for(ll i=1;i<=n;i++)
        scanf("%lld", &a[i]);
    for(ll i=0;i<k;i++){
        bool flag=false;
        for(ll j=0;j<i;j++)
            if(check(i,j)){
                u[i]=j,flag=true;
                break;
            }
        if(!flag)
            u[i]=i,jhnum++;
        //printf("%d %d\n", i,u[i]);
    }
    //printf("%d\n", jhnum);
    printf("%lld\n", query(r+1)-query(l));
    system("pause");
    return 0;
}