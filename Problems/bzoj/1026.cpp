#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

ll f[15][10][3];
ll ditnum,dit[15];
ll l,r;

ll work(ll pos,ll pre,bool lim){
    //printf("%d %d %d\n", pos,pre,lim);
    if (pos==0) return (pre!=-1);
    if (pre!=-1&&f[pos][pre][lim])
        return f[pos][pre][lim];
    ll cnt=0;
    ll sx=lim?dit[pos]:9;
    for(ll i=0;i<=sx;i++){
        if (pre!=-1&&abs(pre-i)<2)continue;
        cnt+=work(pos-1,(pre==-1&&i==0)?-1:i,lim&&(i==sx));
    }
    if (pre!=-1)f[pos][pre][lim]=cnt;
    return cnt;
}

ll calc(ll x){
    memset(f,0,sizeof f);
    ditnum=0;
    while(x){
        dit[++ditnum]=x%10;
        x/=10;
    }
    return work(ditnum,-1,true);
}

int main() {
    scanf("%lld%lld", &l,&r);
    printf("%lld\n", calc(r)-calc(l-1));
    system("pause");
    return 0;
}