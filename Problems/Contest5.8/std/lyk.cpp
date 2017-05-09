#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pr;
const double pi=acos(-1);
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define per(i,n,a) for(int i=n;i>=a;i--)
#define Rep(i,u) for(int i=head[u];i;i=Next[i])
#define clr(a) memset(a,0,sizeof a)
#define pb push_back
#define mp make_pair
#define fi first
#define sc second
ld eps=1e-9;
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
int n,a[N],c[N];
int lowbit(int x){
	return x&(-x);
}
void add(int x){
	for(;x<=n;x+=lowbit(x))c[x]++;
}
int find(int x){
	int ans=0;
	for(;x;x-=lowbit(x))ans+=c[x];
	return ans;
}
int main(){
	freopen("lyk.in","r",stdin);
	freopen("lyk.out","w",stdout);
	n=read();
	rep(i,1,n)a[i]=read();
	ll tot=0;
	per(i,n,1){
		tot+=find(a[i]);
		add(a[i]);
	}
	int ans=tot&1;
	int m=read();
	while(m--){
		int x=read(),y=read();
		if(x!=y)ans^=1;
		printf("%d\n",ans);
	}
	return 0;
}
