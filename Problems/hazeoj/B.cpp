#include <cstdio>  
#include <cstring>  
#include <algorithm>  
using namespace std;  
int dp[500010],len[500010];
struct Node{
    int s,t;
}line[500010];
int n;
bool cmp(Node a,Node b){
    return a.s<b.s;
}
#define lson i*2,l,m  
#define rson i*2+1,m+1,r  
int minv[500010*4];  
  
void PushUp(int i)  
{  
    minv[i]=min(minv[i*2],minv[i*2+1]);  
}  
  
void build(int i,int l,int r)  
{  
    if(l==r){  
        minv[i]=0x3f3f3f3f;  
        return ;  
    }  
    int m=(r+l)/2;  
    build(lson);  
    build(rson);  
    PushUp(i);  
}  
  
int query(int ql,int qr,int i,int l,int r)  
{  
    if(ql<=l&&qr>=r)  
        return minv[i];  
    int m=(r+l)/2;  
    int min_val=0x3f3f3f3f;  
    if(ql<=m)  
        min_val=min(min_val,query(ql,qr,lson));  
    if(qr>m)  
        min_val=min(min_val,query(ql,qr,rson));  
    return min_val;   
}  
  
void update(int pos,int val,int i,int l,int r)  
{  
    if(l==r){  
        minv[i]=min(minv[i],val);  
        return ;  
    }  
    int m=(l+r)/2;  
    if(pos<=m)  
        update(pos,val,lson);  
    else  
        update(pos,val,rson);  
    PushUp(i);  
}  
  
int main()  
{  
    scanf("%d", &n);
        for(int i=1;i<=n;++i){ 
            scanf("%d",&len[i]);
            line[i].s=max(1,i-len[i]);
            line[i].t=min(n,i+len[i]);
        }  
        sort(line+1,line+1+n,cmp);
        dp[1]=0;  
        for(int i=2;i<=n;++i)  
            dp[i]=0x3f3f3f3f;  
        build(1,1,n);  
        update(1,0,1,1,n);  
        for(int i=1;i<=n;++i)  
        {  
            int cnt=query(line[i].s,line[i].t,1,1,n);  
            if(cnt!=0x3f3f3f3f)  
            {  
                dp[line[i].t]=min(dp[line[i].t],cnt+1);  
                update(line[i].t,dp[line[i].t],1,1,n);  
            }  
        }  
        printf("%d\n",dp[n]);  
        system("pause");
    return 0;  
}   
