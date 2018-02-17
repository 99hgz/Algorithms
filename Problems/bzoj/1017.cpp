#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
struct EDGE{
    int v,c;
};
vector<EDGE>vec[60];
int limit[60],cnt,f[60][110][2010],g[60][2010],price[60],force[60],n,m,h[60][2010],v,c,ind[60];
char cases[10];
void dfs(int u){
    if (!vec[u].size()){
        limit[u]=min(limit[u],m/price[u]);
        for(int i=0;i<=limit[u];i++)
            for(int j=i;j<=limit[u];j++)
                f[u][i][j*price[u]]=(j-i)*force[u];
        return;
    }
    limit[u]=0x3f3f3f3f;
    for(vector<EDGE>::iterator it=vec[u].begin();it!=vec[u].end();it++){
        int v=(*it).v;
        dfs(v);
        limit[u]=min(limit[u],limit[v]/(*it).c);
        price[u]+=price[v]*(*it).c;
    }
    memset(g,0xc0,sizeof g);
    g[0][0]=0;
    limit[u]=min(limit[u],m/price[u]);
    for(int lim=limit[u];~lim;--lim){
        int tot=0;
        for(vector<EDGE>::iterator it=vec[u].begin();it!=vec[u].end();it++){
            int v=(*it).v;
            ++tot;
            for(int j=0;j<=m;++j)
                for(int k=0;k<=j;++k)
                    g[tot][j]=max(g[tot][j],g[tot-1][j-k]+f[v][lim*(*it).c][k]);
        }
        for(int i=0;i<=lim;++i)
            for(int j=0;j<=m;++j)
                f[u][i][j]=max(f[u][i][j],g[tot][j]+force[u]*(lim-i));
    }
}

int main() {
    scanf("%d%d", &n,&m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &force[i]);
        scanf("%s", cases);
        if (cases[0]=='A'){
            int nn;
            scanf("%d", &nn);
            for (int j = 1; j <= nn; j++) {
                scanf("%d%d", &v,&c);
                vec[i].push_back((EDGE){v,c});
                ind[v]++;
            }
        }else
            scanf("%d%d", &price[i],&limit[i]);
    }
    memset(f,0xc0,sizeof f);
    cnt=0;
    for (int u = 1; u <= n; u++) {
        if (ind[u])continue;
        dfs(u);
        ++cnt;
        for (int i = 0; i <= m; i++) 
            for (int j = 0; j <= i; j++) 
                for (int k = 0; k <= limit[u]; k++) 
                    h[cnt][i]=max(h[cnt][i],h[cnt-1][j]+f[u][k][i-j]);
    }
    int ans=0;
    for (int i = 0; i <= m; i++) {
        ans=max(ans,h[cnt][i]);
    }
    printf("%d\n", ans);
    system("pause");
    return 0;
}