#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

struct EDGE{
    int u,v,w;
}edge[1010];
int MOD=31011;
int fa[110],vis[110],num,n,m,a,b,c;
ll cnt;
struct G{
    int fa[110],vis[110],l,r,tot;
}group[1010];

bool cmp(EDGE a,EDGE b){
    return a.w<b.w;
}

int gf(int x){
    return fa[x]==0?x:gf(fa[x]);
}

bool kruskal(){
    edge[0].w=edge[1].w;
    int used=0,tot=0;
    group[1].l=1;
    for(int i=1;i<=m+1;i++){
        if (edge[i].w!=edge[i-1].w){
            num++;
            group[num].tot=tot;
            group[num].r=i-1;
            memcpy(group[num].vis,vis,sizeof vis);
            memcpy(group[num+1].fa,fa,sizeof fa);
            group[num+1].l=i;
            tot=0;
        }
        if (i==m+1)break;
        int fx=gf(edge[i].u),fy=gf(edge[i].v);
        if (fx!=fy){
            tot++;
            used++;
            fa[fx]=fy;
            vis[edge[i].u]=vis[edge[i].v]=true;
        }
    }
    if (used<n-1) return false;else return true;
}

void dfs(int x,int r,int rest){
    //printf("%d %d %d\n", x,r,rest);
    if (rest==0) {cnt++;cnt%=MOD;return;}
    if (x>r)return;
    dfs(x+1,r,rest);
    int fx=gf(edge[x].u),fy=gf(edge[x].v);
    if (vis[edge[x].u]&&vis[edge[x].v]&&fx!=fy){
        fa[fx]=fy;
        dfs(x+1,r,rest-1);
        fa[fx]=0;
    }
}

int main() {
    //freopen("bzoj_1016.in", "r", stdin);
    //freopen("bzoj_1016.out", "w", stdout);
    
    scanf("%d%d", &n,&m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &a,&b,&c);
        edge[i]=(EDGE){a,b,c};
    }
    sort(edge+1,edge+1+m,cmp);
    if (!kruskal()) {
        printf("0\n");
        return 0;
    }
    ll ans=1;
    for(int i=1;i<=num;i++){
        if (!group[i].tot)continue;
        printf("%d %d %d\n", group[i].l,group[i].r,group[i].tot);
        memcpy(fa,group[i].fa,sizeof fa);
        memcpy(vis,group[i].vis,sizeof vis);
        cnt=0;
        dfs(group[i].l,group[i].r,group[i].tot);
        ans=ans*cnt%MOD;
    }
    printf("%lld\n", ans);
    system("pause");
    return 0;
}