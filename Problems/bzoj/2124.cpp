#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

ll MOD=998244353;
int SZ[2][10010],base[10010],n,a[10010];

void add(int id,int x,int v){
    for(;x<=n;x+=(x&-x))
        SZ[id][x]=(SZ[id][x]+v)%MOD;
}

ll q(int id,int x){
    ll res=0;
    for(;x;x-=(x&-x))
        res=(res+SZ[id][x])%MOD;
    return res;
}

ll get(int id,int l,int r){
    r=min(r,n),l=max(1,l);
    return (q(id,r)-q(id,l-1)+MOD)%MOD;
}

bool check(){
    for(int j=1;j<=n;j++){
        int i=a[j];
        int llen=i-1,rlen=n-i;
        int plen=min(llen,rlen);
        ll L=get(0,i-plen,i-1),R=get(1,i+1,i+plen);
        //printf("L=(%d,%d) %lld R=(%d,%d) %lld\n",i-plen,i-1,L,i+1,i+plen,R );
        if(i-plen>n-i-plen)
            R=R*base[2*i-n]%MOD;
        else
            L=L*base[n-2*i]%MOD;
        if(L!=R) {
            //printf("%d\n", j);
            return true;
        }
        add(0,i,base[i]);
        add(1,i,base[n-i]);
    }
    return false;
}

int main() {
    int T;
    scanf("%d", &T);
    base[0]=1;
    for(int i=1;i<=10000;i++)
        base[i]=base[i-1]*2%MOD;
    while(T--){
        scanf("%d", &n);
        memset(SZ,0,sizeof SZ);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        bool flag=check();
        if(flag)
            printf("Y\n");
        else
            printf("N\n");
    }
    system("pause");
    return 0;
}