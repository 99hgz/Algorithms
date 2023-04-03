#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int k,n;
ll s[155][155],fac[155],c[50010][155],u[50010][155];
int MOD=10007;
int cnt,Head[50010],Next[100010],To[100010];
void addedge(int u,int v){
    cnt++;
    Next[cnt]=Head[u];
    Head[u]=cnt;
    To[cnt]=v;
    swap(u,v);
    cnt++;
    Next[cnt]=Head[u];
    Head[u]=cnt;
    To[cnt]=v;
}

void dfs1(int x,int fa){
    c[x][0]=1;
    for(int i=Head[x];i;i=Next[i]){
        int v=To[i];
        if(v!=fa){
            dfs1(v,x);
            c[x][0]+=c[v][0];
            for(int i=1;i<=k;i++)
                c[x][i]=(c[x][i]+c[v][i]+c[v][i-1])%MOD;
        }
    }
}

void dfs2(int x,int fa){
    if(fa){
        u[x][0]=n-c[x][0];
        for(int i=1;i<=k;i++)
            u[x][i]=(((c[fa][i]+c[fa][i-1]+u[fa][i]+u[fa][i-1]-c[x][i]-c[x][i-1]-c[x][i-1]-(i>1?c[x][i-2]:0))%MOD)+MOD)%MOD;
    }
    for(int i=Head[x];i;i=Next[i]){
        int v=To[i];
        if(v!=fa)
            dfs2(v,x);
    }
}

int main() {
    int N, L, i, now, A, B, Q, tmp; 
    scanf("%d%d%d", &N, &k, &L); 
    scanf("%d%d%d%d", &now, &A, &B, &Q); 
    n=N;
    //scanf("%d%d", &n,&k);
    s[0][0]=fac[0]=1;
    for(int i=1;i<=k;i++){
        fac[i]=fac[i-1]*i%MOD;
        for(int j=1;j<=i;j++)
            s[i][j]=(s[i-1][j]*j%MOD+s[i-1][j-1])%MOD;
    }
    for (i = 1; i < n; i ++) { 
        now = (now * A + B) % Q; 
        tmp = (i < L) ? i : L; 
        addedge(i - now % tmp, i + 1); 
        //scanf("%d%d", &now,&tmp);
        //addedge(now,tmp);
    } 
    dfs1(1,1);
    dfs2(1,0);
    for(int i=1;i<=n;i++){
        ll ans=0;
        for(int j=1;j<=k;j++)
            ans=(ans+s[k][j]*fac[j]%MOD*(u[i][j]+c[i][j])%MOD)%MOD;
        printf("%lld\n", ans);
    }
    
    //system("pause");
    return 0;
}