#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

struct EDGE{
    int u,v;
    double w;
}e[100100];
int tot,n,m,RT,u,v,tn,B[100010];
double w,A[100010],mn[100010];
int belong[100010],vis[100010],pre[100010];
double in[100010];
void addedge(int u,int v,double w){
    e[++tot]=(EDGE){u,v,w};
}
double INF=100000000;
double zl(int n,int rt){
    double res=0;
    while(1){
        for(int i=1;i<=n;i++)
            in[i]=INF,belong[i]=vis[i]=pre[i]=0;
        for(int i=1;i<=tot;i++)
            if(e[i].u!=e[i].v&&e[i].w<in[e[i].v])
                pre[e[i].v]=e[i].u,in[e[i].v]=e[i].w;
        for(int i=1;i<=n;i++)
            if(i!=rt&&!pre[i])
                return -1;
        tn=1;
        in[rt]=0;//!
        for(int i=1;i<=n;i++){
            res+=in[i];
            v=i;
            while(vis[v]!=i&&v!=rt&&!belong[v])
                vis[v]=i,v=pre[v];
            if(v!=rt&&!belong[v]){
                for(int u=pre[v];u!=v;u=pre[u])
                    belong[u]=tn;
                belong[v]=tn++;
            }
        }
        if(tn==1)break;
        for(int i=1;i<=n;i++)
            if(!belong[i])
                belong[i]=tn++;
        int cnt=0;
        for(int i=1;i<=tot;i++){
            int v=e[i].v;
            cnt++;
            e[cnt]=(EDGE){belong[e[i].u],belong[e[i].v],e[i].w};
            if(e[cnt].u==e[cnt].v)
                cnt--;
            else
                e[cnt].w-=in[v];
        }
        tot=cnt;
        n=tn-1;
        rt=belong[rt];
    }
    return res;

}

int main() {
    scanf("%d", &n);
    for(int i=1;i<=n;i++){
        scanf("%lf%d",&A[i],&B[i]);
        if(B[i]==0)A[i]=0;
        addedge(n+1,i,A[i]);
        mn[i]=A[i];
    }
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d%lf",&u,&v,&w);
        if(B[u]&&B[v])mn[v]=min(mn[v],w),addedge(u,v,w);
    }
    n++;
    double ans=zl(n,n);
    for(int i=1;i<=n-1;i++)
        if(B[i])ans+=mn[i]*(B[i]-1);
    printf("%.2lf\n", ans);
    //system("pause");
    return 0;
}