/*#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int ts[1010],q[1010],dv[1010],vis[1010],G[30][30],n,m,u,v,ans;

void dfs(int start,int u,int step){
    
    //printf("dfs:%d %d %d\n", start,u,step);
    if(u==start&&step!=1){
        for(int i=1;i<step;i++)
            ts[q[i]]++;
        return;
    }
    
    for(int i=1;i<=n;i++)
        if (!dv[i]&&!vis[i]&&G[u][i]){
            dv[i]=true;
            q[step]=(u-1)*n+i;
            dfs(start,i,step+1);
            dv[i]=false;
        }
}

int check(){
    memset(ts,0,sizeof ts);
    memset(vis,0,sizeof vis);
    for(int i=1;i<=n;i++){
        memset(dv,0,sizeof dv);
        dfs(i,i,1);
        vis[i]=true;
    }
    for (int i = 1; i <= n*n; i++)
        if (ts[i]>1) return false;
    return true;
}

void dfs1(int edgeid){
    if (edgeid==n*n+1){
        ans+=check();
        return;
    }
    int u=edgeid/n+1;
    int v=edgeid%n;
    if (u>=v) dfs1(edgeid+1);else
    if (G[u][v]) dfs1(edgeid+1);else{
        G[u][v]=G[v][u]=1;
        dfs1(edgeid+1);
        G[u][v]=G[v][u]=0;
        dfs1(edgeid+1);
    }
}

int main() {
    scanf("%d%d",&n,&m );
    for (int i = 1; i <= m; i++){
        scanf("%d%d", &u,&v);
        G[u][v]=G[v][u]=1;
    }
    dfs1(1);
    printf("%d\n", ans);
    system("pause");
    return 0;
}*/

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
ll MOD=998244353;
ll n,m,u,v;
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
int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++){
        scanf("%lld%lld",&n,&m );
        for (int i = 1; i <= m; i++)
            scanf("%lld%lld", &u,&v); 
        printf("%lld\n",pow(2,n-2));
    }
    system("pause");
    return 0;
}