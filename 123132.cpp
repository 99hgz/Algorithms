#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
typedef long long ll;
ll f[510],sz[510],nf[510],son[510],fac[510],pf[510][510],g[510][510],g2[510][510],g3[510][510],pf2[510][510],xs[510][510];
vector<int>vec[510];
int n,m,u,v;
const ll MOD =998244353;

ll pow(ll a,ll b){
    ll res=1;
    while(b){
        if (b&1) res=res*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return res;
}

void dfs(int x,int fa){
	f[x]=1;
	sz[x]=1;
	for(int v:vec[x])
		if(v!=fa){
			dfs(v,x);
			son[x]++;
			f[x]=(f[x]*f[v])%MOD;
			sz[x]+=sz[v];
		}
	f[x]=fac[son[x]]*f[x]%MOD;	
	nf[x]=pow(f[x],MOD-2);
}

void dfs2(int x,int fa){	
	memset(pf,0,sizeof pf);
	pf[0][0]=1;
	ll ff=1;
	for(int v:vec[x]){
		if(v!=fa){
			for(int i=son[x];i>=0;i--)
				for(int j=n;j>=0;j--)
					pf[i][j]=(pf[i][j]%MOD+((i>0&&j>=sz[v])?pf[i-1][j-sz[v]]:0)%MOD)%MOD;
			ff=ff*f[v]%MOD;
		}
	}

	for(int it=vec[x].size()-1;it>=0;it--){
		int v=vec[x][it];
		if(v!=fa){
			memset(pf2,0,sizeof pf2);
			for(int i=0;i<=son[x]-1;i++)
				for(int j=0;j<=n;j++){
					pf2[i][j]=(pf[i][j]%MOD-((i>0&&j>=sz[v])?pf2[i-1][j-sz[v]]:0)%MOD+MOD)%MOD;
					xs[v][j]=(xs[v][j]+pf2[i][j]*fac[i]%MOD*fac[son[x]-i-1]%MOD)%MOD;
				}
			
			for(int i=0;i<=n;i++)
				for(int j=0;j<=i;j++)
					g3[v][i+1]=(g3[v][i+1]+xs[v][j]*g3[x][i-j]%MOD*ff%MOD*nf[v]%MOD)%MOD;
		}
	}
	
	for(int v:vec[x])
		if(v!=fa)
			dfs2(v,x);
}

int main(){
	scanf("%d",&n);
	fac[0]=1LL;
	for(int i=1;i<=n;i++)
		fac[i]=fac[i-1]*i%MOD;
	for(int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		vec[u].push_back(v);
		vec[v].push_back(u);
	}
	
	dfs(1,1);
	g3[1][1]=1;
	dfs2(1,1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
			printf("%lld ",g3[i][j]*f[i]%MOD);
		printf("\n");
	}
}
