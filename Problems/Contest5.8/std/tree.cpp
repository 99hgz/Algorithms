#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pr;
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define per(i,n,a) for(int i=n;i>=a;i--)
#define Rep(i,u) for(int i=head[u];i;i=Next[i])
#define clr(a) memset(a,0,sizeof a)
#define pb push_back
#define mp make_pair
#define fi first
#define sc second
ll pp=1000000007;
ll mo(ll a,ll pp){if(a>=0 && a<pp)return a;a%=pp;if(a<0)a+=pp;return a;}
ll powmod(ll a,ll b,ll pp){ll ans=1;for(;b;b>>=1,a=mo(a*a,pp))if(b&1)ans=mo(ans*a,pp);return ans;}
ll read(){
	ll ans=0;
	char last=' ',ch=getchar();
	while(ch<'0' || ch>'9')last=ch,ch=getchar();
	while(ch>='0' && ch<='9')ans=ans*10+ch-'0',ch=getchar();
	if(last=='-')ans=-ans;
	return ans;
}
//head
#define N 110000
int v[N*2],Next[N*2],head[N],cost[N*2],Q[N*2],q[N*2],b[N*4][3],num=0,n,m;
int pre[N*2][20],B[N*2],lab[N],fa[N],dep[N];
void add(int x,int y,int z){
	v[++num]=y;Next[num]=head[x];head[x]=num;cost[num]=z;
}
void bfs(){
	int top=1;
	q[1]=1;
	while(top){
		int u=q[top];
		Q[++Q[0]]=u;
		lab[u]=Q[0];
		if(head[u] && v[head[u]]==fa[u])head[u]=Next[head[u]];
		if(head[u]){
			dep[v[head[u]]]=dep[u]+cost[head[u]];
			fa[v[head[u]]]=u;
			q[++top]=v[head[u]];
			head[u]=Next[head[u]];
			}
		else --top;
	}
	rep(i,1,Q[0]){
		pre[i][0]=Q[i];
		for(int j=1;(1<<j)<=i;++j)
			if(dep[pre[i][j-1]]<dep[pre[i-(1<<(j-1))][j-1]])pre[i][j]=pre[i][j-1];
			else pre[i][j]=pre[i-(1<<(j-1))][j-1];
	}
	for(int j=0;(1<<j)<=Q[0];j++)B[1<<j]=j;
	rep(j,2,Q[0])
		if(!B[j])B[j]=B[j-1];
}
int calc(int x,int y){
	int tt=dep[x]+dep[y];
	x=lab[x],y=lab[y];
	if(x>y)swap(x,y);
	int z=B[y-x+1];
	int t1=pre[y][z],t2=pre[x+(1<<z)-1][z];
	if(dep[t1]<dep[t2])return tt-dep[t1]-dep[t1];
	else return tt-dep[t2]-dep[t2];
}
void build(int u,int l,int r){
	if(l==r){
		b[u][0]=1;
		b[u][1]=l;
		return ;
	}
	int mid=(l+r)>>1;
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
	q[0]=0;
	rep(i,1,b[u<<1][0])q[++q[0]]=b[u<<1][i];
	rep(i,1,b[u<<1|1][0])q[++q[0]]=b[u<<1|1][i];
	b[u][0]=2;
	b[u][1]=q[1];
	b[u][2]=q[2];
	int Max=calc(q[1],q[2]);
	rep(i,3,q[0])
		rep(j,1,i-1){
			int t=calc(q[i],q[j]);
			if(t>Max){
				Max=t;
				b[u][1]=q[i];
				b[u][2]=q[j];
			}
		}
}
void get(int u,int l,int r,int x,int y){
	if(x>r || y<l)return ;
	if(x<=l && y>=r){
		rep(i,1,b[u][0])q[++q[0]]=b[u][i];
		if(q[0]==1)return;
		int Max=0,ans1,ans2;
		rep(i,2,q[0])
		  rep(j,1,i-1){
			int t=calc(q[i],q[j]);
			if(t>Max){
				Max=t;
				ans1=q[i];
				ans2=q[j];
			}
		}
		q[0]=2;
		q[1]=ans1;
		q[2]=ans2;
		return;
	}
	int mid=(l+r)>>1;
	get(u<<1,l,mid,x,y);
	get(u<<1|1,mid+1,r,x,y);
}
int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	n=read();
	rep(i,1,n-1){
		int x=read(),y=read(),z=read();
		add(x,y,z);
		add(y,x,z);
	}
	bfs();
	build(1,1,n);
	m=read();
	while(m--){
		int l=read(),r=read();
		q[0]=0;
		get(1,1,n,l,r);
		int t1=q[1],t2=q[2];
		l=read(),r=read();
		q[0]=0;
		get(1,1,n,l,r);
		int ans=calc(q[1],t1);
		ans=max(ans,calc(q[1],t2));
		ans=max(ans,calc(q[2],t1));
		ans=max(ans,calc(q[2],t2));
		printf("%d\n",ans);
	}
	return 0;
}
