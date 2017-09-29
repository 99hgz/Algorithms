#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
using namespace std;
#define ll long long
const ll INF=(ll)1<<60;
#define N 110000
int n,m,a[N],b[N],c[N],d[N],q[N];
ll ans=INF;
struct seg{
	ll Min[N*4],a[N];
	void build(int u,int l,int r){
		if(l==r){
			Min[u]=a[l];
			return;
		}
		int mid=(l+r)>>1;
		build(u*2,l,mid);
		build(u*2+1,mid+1,r);
		Min[u]=min(Min[u*2],Min[u*2+1]);
	}
	ll find(int u,int l,int r,int x,int y){
		if(x<=l && y>=r)return Min[u];
		if(x>r || y<l)return INF;
		int mid=(l+r)>>1;
		return min(find(u*2,l,mid,x,y),find(u*2+1,mid+1,r,x,y));
	}
	void change(int u,int l,int r,int x,ll w){
		if(l==r){
			Min[u]=min(w,Min[u]);
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid)change(u*2,l,mid,x,w);
		else change(u*2+1,mid+1,r,x,w);
		Min[u]=min(Min[u*2],Min[u*2+1]);
	}
}t1,t2;
int bin1(int k){
	int l=1,r=q[0];
	while(l<r){
		int mid=(l+r)/2;
		if(q[mid]>=k)r=mid;
		else l=mid+1;
	}
	return l;
}
int bin2(int k){
	int l=1,r=q[0];
	while(l<r){
		int mid=(l+r)/2+1;
		if(k>=q[mid])l=mid;
		else r=mid-1;
	}
	return l;
}
int main(){
	freopen("pinball.in","r",stdin);
	freopen("pinball.out","w",stdout);
	scanf("%d%d",&n,&m);
	q[++q[0]]=1;
	q[++q[0]]=m;
	for(int i=1;i<=n;i++)scanf("%d%d%d%d",&a[i],&b[i],&c[i],&d[i]),q[++q[0]]=c[i];
	sort(q+1,q+q[0]+1);
	q[0]=1;
	for(int i=2;i<=n+2;i++)
		if(q[i]!=q[q[0]])q[++q[0]]=q[i];
	m=q[0];
	for(int i=1;i<=q[0];i++){
		t1.a[i]=INF*(int)(i>1);
		t2.a[i]=INF*(int)(i<q[0]);
	}
	t1.build(1,1,q[0]);
	t2.build(1,1,q[0]);
	for(int i=1;i<=n;i++){
		a[i]=bin1(a[i]);
		b[i]=bin2(b[i]);
		c[i]=bin1(c[i]);
		ll f1=t1.find(1,1,q[0],a[i],b[i]),f2=t2.find(1,1,q[0],a[i],b[i]);
		ans=min(f1+f2+d[i],ans);
		t1.change(1,1,q[0],c[i],f1+d[i]);
		t2.change(1,1,q[0],c[i],f2+d[i]);
	}
	if(ans<INF)cout<<ans<<endl;
	else cout<<-1<<endl;
	return 0;
}
