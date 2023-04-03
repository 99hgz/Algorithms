#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

struct EDGE{
    int u,v,w;
}e[100100];
int tot,n,m,RT,u,v,w,tn;
int in[100010],belong[100010],vis[100010],pre[100010];

void addedge(int u,int v,int w){
    e[++tot]=(EDGE){u,v,w};
}

int zl(int rt){
    int res=0;
    while(1){
        for(int i=1;i<=n;i++)
            in[i]=0x3f3f3f3f,belong[i]=vis[i]=0;
        for(int i=1;i<=tot;i++)
            if(e[i].u!=e[i].v&&e[i].w<in[e[i].v])
                pre[e[i].v]=e[i].u,in[e[i].v]=e[i].w;
        for(int i=1;i<=n;i++)
            if(i!=rt&&in[i]==0x3f3f3f3f)
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
    scanf("%d%d%d",&n,&m,&RT);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&u,&v,&w);
        if(u!=v)addedge(u,v,w);
    }
    int ans=zl(RT);
    printf("%d\n", ans);
    system("pause");
    return 0;
}