#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

char st[10010];
ll n,base[1010];
ll f[710][710][10];
ll MOD=1000000007,ans;

ll solve(ll x,ll j,ll v,bool tight){
    if(j<0) return 0;
    if(x>n) return (j==0);
    if(f[x][j][tight]!=-1)
        return f[x][j][tight];
    ll res=0;
    if(!tight)
        res=(ll)solve(x+1,j,v,0)*v+(ll)solve(x+1,j-1,v,0)*(10-v);
    else if(v>(st[x]-'0'))
        res=(ll)solve(x+1,j,v,0)*(st[x]-'0')+solve(x+1,j,v,1);
    else
        res=(ll)solve(x+1,j,v,0)*v+solve(x+1,j-1,v,0)*(st[x]-'0'-v)+solve(x+1,j-1,v,1);
    res%=MOD;
    return f[x][j][tight]=res;
}

int main() {
    scanf("%s", st+1);
    n=strlen(st+1);
    base[1]=1;
    for(ll i=2;i<=1000;i++)
        base[i]=((ll)base[i-1]*10%MOD+1)%MOD;
    for(ll i=1;i<=9;i++){
        memset(f,-1,sizeof f);
        for(ll j=1;j<=n;j++)
            ans=(ans+(ll)solve(1,j,i,1)*base[j]%MOD)%MOD;
    }
    printf("%lld\n", ans);
   //system("pause");
    return 0;
}