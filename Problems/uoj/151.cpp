#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int f[60][60][60][60],a[20],b[10],x,n,ans,_;

int calc(int s,int t,int u,int v){
    if (!s && !t && !u && !v) return 0;
	if(f[s][t][u][v]) return f[s][t][u][v];
	int res=s+t+u+v;
	if(v) 
        res=min(res,min(calc(s+1,t,u+1,v-1),calc(s,t+2,u,v-1)));
	if(u) 
        res=min(res,calc(s+1,t+1,u-1,v));
	if(t) 
        res=min(res,calc(s+2,t-1,u,v));
	if(v && t>=2) 
        res=min(res,calc(s,t-2,u,v-1)+1);
	if(v && s>=2) 
        res=min(res,calc(s-2,t,u,v-1)+1);
	if(u && t) 
        res=min(res,calc(s,t-1,u-1,v)+1);
	if(u && s) 
        res=min(res,calc(s-1,t,u-1,v)+1);
	return f[s][t][u][v]=res;
}
void dfs(int used){
    if(used>ans)return;
    for(int i=3;i<=13;i++){
        bool flag=(min(a[i],a[i+1])>=3);
        for(int r=i+1;flag&&a[r]>=3;r++){
            for(int t=i;t<=r;t++)a[t]-=3;
            dfs(used+1);
            for(int t=i;t<=r;t++)a[t]+=3;
        }
    }
    for(int i=3;i<=12;i++){
        bool flag=(min(a[i],min(a[i+1],a[i+2]))>=2);
        for(int r=i+2;flag&&a[r]>=2;r++){
            for(int t=i;t<=r;t++)a[t]-=2;
            dfs(used+1);
            for(int t=i;t<=r;t++)a[t]+=2;
        }
    }
    for(int i=3;i<=10;i++){
        bool flag=(a[i]&&a[i+1]&&a[i+2]&&a[i+3]&&a[i+4]);
        for(int r=i+4;flag&&a[r];r++){
            for(int t=i;t<=r;t++)a[t]-=1;
            dfs(used+1);
            for(int t=i;t<=r;t++)a[t]+=1;
        }
    }
    memset(b,0,sizeof b);
    for(int i=2;i<=14;i++)
        b[a[i]]++;
    if(a[0]==2)
        ans=min(ans,used+calc(b[1],b[2],b[3],b[4])+1);
    b[1]+=a[0];
    ans=min(ans,used+calc(b[1],b[2],b[3],b[4]));
}

int main() {
    int t;
    scanf("%d%d", &t, &n);
    while(t--){
        memset(a,0,sizeof a);
        for(int i=1;i<=n;i++){
            scanf("%d%d", &x,&_);
            a[x]++;
        }
        ans=0x3f3f3f3f;
        a[14]=a[1];
        dfs(0);
        printf("%d\n", ans);
    }
    system("pause");
    return 0;
}