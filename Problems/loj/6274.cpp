#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

ll limn[10],lim[10][70],f[70][1<<17],num[10],ans,mx;

ll check(ll bt,ll sta,ll a,ll b){
    //0
    ll res=0;
    for(ll i=0;i<16;i++){
        if(!((sta>>i)&1)) continue;
        ll fx=i/4,fy=i%4;
        ll x=0,y=0;
        if(fx==0)
            x=0;
        else if(fx==1){
            if(a<lim[2][bt]) continue;
            x=(a==lim[2][bt]);
        }else if(fx==2){
            if(a>lim[3][bt]) continue;
            x=((a==lim[3][bt])?2:0);
        }else{
            if(a<lim[2][bt]) continue;
            if(a>lim[3][bt]) continue;
            if(lim[2][bt]==lim[3][bt]) x=3;
            else x=((a==lim[2][bt])?1:2);
        }

        if(fy==0)
            y=0;
        else if(fy==1){
            if(b<lim[4][bt]) continue;
            y=(b==lim[4][bt]);
        }else if(fy==2){
            if(b>lim[5][bt]) continue;
            y=((b==lim[5][bt])?2:0);
        }else{
            if(b<lim[4][bt]) continue;
            if(b>lim[5][bt]) continue;
            if(lim[4][bt]==lim[5][bt]) y=3;
            else y=((b==lim[4][bt])?1:2);
        }
        res|=(1<<(x*4+y));
    }
    return res;
}

ll dfs(ll x,ll sta,ll val){
    for(ll i=1;i<x;i++)printf(" ");
    printf("%lld %lld %lld\n",x,sta,val);
    if(sta==0) return 0;
    if(x>mx) {
        printf("get=%lld\n", val);
        return 1;
    }
    if(f[x][sta]!=-1) return f[x][sta];
    if(lim[1][x]==0){
        return f[x][sta]=dfs(x+1,check(x,sta,0,0),val<<1);
    }else{
        ll nxt=check(x,sta,0,1)|check(x,sta,1,0);
        return f[x][sta]=dfs(x+1,nxt,val<<1)+dfs(x+1,check(x,sta,1,1),val<<1|1);
    }
} 


int main() {
    memset(f,-1,sizeof f);
    for (ll i = 1; i <= 5; i++)
        scanf("%lld", &num[i]);
    for (ll i = 1; i <= 5; i++){
        while(num[i]){
            lim[i][++limn[i]]=num[i]%2;
            num[i]/=2;
        }
        //reverse(lim[i]+1,lim[i]+limn[i]+1);
        /*reverse(lim[i]+1,lim[i]+limn[1]+1);
        for(ll j=1;j<=limn[1];j++)
            printf("%lld",lim[i][j]);
        printf("\n");*/
        mx=max(mx,limn[i]);
    }
    for (ll i = 1; i <= 5; i++){
        reverse(lim[i]+1,lim[i]+mx+1);
        //for(ll j=1;j<=mx;j++)
        //    printf("%lld",lim[i][j]);
        //printf("\n");
    }
    ll ans=dfs(1,1<<(3*4+3),0);
    printf("%lld\n", ans);
    system("pause");
    return 0;
}