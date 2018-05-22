#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
//typedef complex<double> E;
typedef long long ll;
#define pi acos(-1)

struct E{
    double x,y;
    E(double x=0,double y=0):x(x),y(y){};
};
E operator -(E a,E b){return (E){a.x-b.x,a.y-b.y};}
E operator +(E a,E b){return (E){a.x+b.x,a.y+b.y};}
E operator *(E a,E b){return (E){a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x};}

E d[400010],e[400010];
int n,m,q,x,a[400010],b[400010],mx,c,rk[400010];
ll ans[200010];

void fft(E *u,int v,int n){
    for (int i = 0; i < n; i++) 
        if (rk[i]>i)
            swap(u[rk[i]],u[i]);
    for(int i=1;i<n;i<<=1){
        E wn(cos(pi/i),v*sin(pi/i));
        for(int j=0;j<n;j+=(i<<1)){
            E w(1,0);
            for(int k=0;k<i;k++,w=w*wn){
                E x=u[j+k],y=w*u[i+j+k];
                u[j+k]=x+y;
                u[i+j+k]=x-y;
            }
        }
    }
    if (v==-1)
        for (int i = 0; i < n; i++) 
            u[i]=u[i]*(1.0/(double)n);
}

void solve(int l,int r){
    if (l==r){
        ans[0]+=(ll)a[l]*b[l];
        return;
    }
    int mid=(l+r)>>1;
    int len,ll=0;
    for(len=1;len<=(r-l+1);len<<=1)ll++;
    rk[0]=0;
    for(int i=0;i<len;i++)
        rk[i]=(rk[i>>1]>>1)|((i&1)<<(ll-1));
    memset(d,0,sizeof(d[0])*len),memset(e,0,sizeof(e[0])*len);
    for(int i=l;i<=mid;i++)
        d[i-l]=a[i];
    for(int i=mid+1;i<=r;i++)
        e[i-mid-1]=b[i];
    fft(d,1,len);fft(e,1,len);
    for(int i=0;i<len;i++)
        d[i]=d[i]*e[i];
    fft(d,-1,len);
    for(int i=0;i<len;i++)
        ans[i+l+mid+1]+=(long long)(d[i].x+0.5);

    memset(d,0,sizeof(d[0])*len),memset(e,0,sizeof(e[0])*len);
    for(int i=mid+1;i<=r;i++)
        d[i-mid-1]=a[i];
    for(int i=l;i<=mid;i++)
        e[mid-i]=b[i];
    fft(d,1,len);fft(e,1,len);
    for(int i=0;i<len;i++)
        d[i]=d[i]*e[i];
    fft(d,-1,len);
    for(int i=0;i<len;i++)
        ans[i+1]+=(long long)(d[i].x+0.5);

    solve(l,mid);
    solve(mid+1,r);
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--){
        memset(ans,0,sizeof ans);
        memset(a,0,sizeof a);
        memset(b,0,sizeof b);
        mx=0;
        scanf("%d%d%d", &n,&m,&q);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &x);
            a[x]++;
            mx=max(mx,x);
        }
        for(int i=1;i<=m;i++){
            scanf("%d", &x);
            b[x]++;
            mx=max(mx,x);
        }
        
        solve(0,mx);
        
        for (int i = 1; i <= q; i++) {
            scanf("%d", &c);
            printf("%lld\n", ans[c]);
        }
    }
    system("pause");
    return 0;
}