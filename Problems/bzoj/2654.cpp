#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n,m,u,v,w,cnt;
struct Edge{
    int u,v,w;
}edge[2000100];
int fa[1000010];
bool cmp(Edge a,Edge b){
    return a.w<b.w;
}
namespace MST{
    int gf(int x){
        return (fa[x]==x)?x:fa[x]=gf(fa[x]);
    }
    void addedge(int u,int v,int w){
        edge[++cnt]=(Edge){u,v,w};
    }
    int mst(){
        int res=0;
        for(int i=1;i<=n+1;i++)
            fa[i]=i;
        sort(edge+1,edge+1+cnt,cmp);
        for(int i=1;i<=cnt;i++){
            int fu=gf(edge[i].u),fv=gf(edge[i].v);
            if(fu!=fv){
                res+=edge[i].w;
                fa[fu]=fv;
            }
        }
        return res;

    }
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&w);
        MST::addedge(n+1,i,w);
    }
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&u,&v,&w);
        MST::addedge(u,v,w);
    }
    printf("%d\n", MST::mst());
    system("pause");
    return 0;
}