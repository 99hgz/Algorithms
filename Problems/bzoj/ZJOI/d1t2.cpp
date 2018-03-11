#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
ll MOD=998244353;
ll C[3010][3010],pre[3010],n,m,op,l,r,len,tot[3010];
ll pow(ll a,ll b){
    ll ans=1;
    while(b){
        if (b&1)
            ans=ans*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ans;
}

void init(){
    C[0][1]=C[1][1]=1;
    for (ll i = 2; i <= 3000; i++){
        C[0][i]=1;
        for (ll j = 1; j <= i; j++)
            C[j][i]=(C[j-1][i-1]+C[j][i-1])%MOD;
    }
    for (ll i = 0; i <= 3000; i++){
        for(ll j=0;j<=i;j+=2)
            pre[i]=(pre[i]+C[j][i])%MOD;
    }
}
struct L{
    ll l,r;
}line[3010];
ll f[3010][2],cnt;
ll calc(ll x){
    memset(f,0,sizeof f);
    f[0][0]=1;
    for (ll i = 1; i <= cnt; i++)
        for (ll j = 0; j <= 1; j++){
            ll lenth=line[i].r-line[i].l+1;
            if (x>=line[i].l&&line[i].r>=x)
                f[i][j^1]=(f[i][j^1]+f[i-1][j])%MOD,lenth--;
            
            if (r>=line[i].l&&line[i].r>=r)
                f[i][j^1]=(f[i][j^1]+f[i-1][j])%MOD,lenth--;
            f[i][j]=(f[i][j]+f[i-1][j]*lenth)%MOD;
        }

    return f[cnt][0];
}

ll calc2(ll x){
    memset(f,0,sizeof f);
    f[0][0]=1;
    for(ll i=1;i<=cnt;i++){
        for(ll j=0;j<=1;j++){
            ll lenth=line[i].r-line[i].l+1;
            ll cg=(x>=line[i].l&&line[i].r>=x);
            if (cg) f[i][j]=(f[i][j]+f[i-1][j])%MOD;
            f[i][j^1]=(f[i][j^1]+f[i-1][j]*(lenth-cg))%MOD;
        }
    }
    return f[cnt][0];
}

int main() {
    //freopen("Z:\\problem_291\\ex_bit2.in", "r", stdin);
    //freopen("Z:\\problem_291\\ex_bit2.ans", "w", stdout);
    
    len=1;
    scanf("%lld%lld", &n,&m);
    //init();
    if (n>50) return 0;
    for (ll i = 1; i <= m; i++){
        scanf("%lld%lld%lld", &op,&l,&r);
        if (op==1){
            len=len*(r-l+1)%MOD;
            for (ll i = l; i <= r; i++)
                tot[i]++;
            line[++cnt]=(L){l,r};
        }else{
            //if (l==1)l=2;
            //printf("len=%lld\n", len);
            if (l==1){
                //printf("calc2=%lld\n", calc2(r));
                printf("%lld\n", calc2(r)*pow(len,MOD-2)%MOD);
                continue;
            }
            //printf("%lld\n", calc(l-1));
            printf("%lld\n", ((calc(l-1)*pow(len,MOD-2)%MOD))%MOD);
            //printf("%lld %lld\n",pre[tot[l-1]],len);
        }
    }
    system("pause");
    return 0;
}