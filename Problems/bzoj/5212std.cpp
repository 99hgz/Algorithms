#include<bits/stdc++.h>
#define rep(i,x,y) for (int i=(x); i<=(y); i++)
#define ll long long
#define N 400005
using namespace std;
ll read(){
	char ch=getchar(); ll x=0; int op=1;
	for (; !isdigit(ch); ch=getchar()) if (ch=='-') op=1;
	for (; isdigit(ch); ch=getchar()) x=(x<<1)+(x<<3)+ch-'0';
	return x*op;
}
void write(ll a){
	if (a<0) putchar('-'),a=-a;
	if (a>=10) write(a/10); putchar(a%10+'0');
}
int n,m,cnt,chk[N],head[N],fa[N],c[N][2];
ll dp[N],siz[N],sum[N],a[N],ans;
struct edge{ int to,nxt; }e[N<<1];
void adde(int x,int y){
	e[++cnt].to=y; e[cnt].nxt=head[x]; head[x]=cnt;
}
void ins(int x,int y){
	adde(x,y); adde(y,x);
}
ll get(ll x,ll y){
	return min(2*(x-y),x-1);
}
bool isrt(int x){
	return c[fa[x]][0]!=x && c[fa[x]][1]!=x;
}
void up(int x){
	siz[x]=sum[x]+a[x];
	if (c[x][0]) siz[x]+=siz[c[x][0]];
	if (c[x][1]) siz[x]+=siz[c[x][1]];
}
void rot(int x){
	int y=fa[x],z=fa[y],f=c[y][1]==x;
	c[y][f]=c[x][f^1]; if (c[x][f^1]) fa[c[x][f^1]]=y;
	fa[x]=z; if (!isrt(y)) c[z][c[z][1]==y]=x;
	fa[y]=x; c[x][f^1]=y; up(y); up(x);
}
void splay(int x){
	for (int y,z; !isrt(x); rot(x)){
		y=fa[x],z=fa[y];
		if (!isrt(y)) rot((c[y][0]==x)==(c[z][0]==y)?y:x);
	}
}
void change(int x,ll y){
	for (int t=0; x; t=x,x=fa[x]){//暴力跳每一条轻边，修改轻边答案以及x的重儿子
		splay(x); ll now=siz[t],nxt=siz[x];
		if (c[x][0]) nxt-=siz[c[x][0]];
		nxt+=y;
		if (!t){//第一轮
			a[x]+=y;//直接修改a的值
			if (c[x][1] && siz[c[x][1]]<=(nxt+1)/2){//原先的重儿子变成轻儿子
				ans+=get(nxt,a[x])-get(nxt-y,siz[c[x][1]]);//更改答案
				sum[x]+=siz[c[x][1]]; c[x][1]=0;//splay上修改
			} else if (!chk[x]){//非叶节点
				if (c[x][1]) ans+=2LL*y;//可以化简为2*y；同理别的也可以化简
				else ans+=get(nxt,a[x])-get(nxt-y,a[x]-y);//相应更改，维护
			}
		} else{
			sum[x]+=y;//此时t-x为一条轻边，更改轻儿子siz和
			if (c[x][1] && siz[c[x][1]]<=(nxt+1)/2){//同上
				ans+=get(nxt,a[x])-get(nxt-y,siz[c[x][1]]);
				sum[x]+=siz[c[x][1]]; c[x][1]=0;
			} else if (!chk[x]){
				if (c[x][1]) ans+=2LL*y;
				else ans+=get(nxt,a[x])-get(nxt-y,a[x]);//同上，注意此时a[x]不用-y
			}
			if (now>(nxt+1)/2){//看当前的轻儿子是否变成了重儿子，并修改
				ans+=get(nxt,now)-get(nxt,a[x]);
				sum[x]+=siz[c[x][1]];//修改轻儿子的siz和
				c[x][1]=t;//splay上修改
				sum[x]-=siz[c[x][1]];
			}
		}
		up(x);
	}
}
void dfs(int u){//dp[u]表示u为根的子树最多的轻重链切换次数
	siz[u]=a[u]; dp[u]=0; ll mx=a[u];
	for (int i=head[u],v; i; i=e[i].nxt) if ((v=e[i].to)!=fa[u]){
		fa[v]=u; dfs(v);
		dp[u]+=dp[v]; siz[u]+=siz[v];
		mx=max(mx,siz[v]);
	}
	if (mx>(siz[u]+1)/2) dp[u]+=2*(siz[u]-mx);//计算点u被计算的贡献次数
	else dp[u]+=siz[u]-1;
	for (int i=head[u],v; i; i=e[i].nxt) if ((v=e[i].to)!=fa[u]){
		if (siz[v]>(siz[u]+1)/2) c[u][1]=v;//挂到重链上，splay维护
		else sum[u]+=siz[v];//sum维护所有轻儿子的siz和
	}
}
int main(){
	n=read(),m=read();
	rep (i,1,n) a[i]=read();
	rep (i,1,n-1){
		int x=read(),y=read(); ins(x,y);
		chk[x]++; chk[y]++;
	}
	rep (i,1,n) if (chk[i]>1) chk[i]=0;//chk[i]=1表示i是叶子
	chk[1]=0;
	dfs(1); ans=dp[1];//一遍树形dp得到无修改的答案
	write(ans),puts("");
	while (m--){
		int x=read(),y=read(); change(x,y);
		write(ans),puts("");
	}
	return 0;
}