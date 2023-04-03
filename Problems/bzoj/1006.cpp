#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n,m,u,v;
int tot,Head[10100],Next[2010010],To[2010010],label[10100],q[10100];
bool vis[10100];
int p[10100];
void addedge(int u, int v)
{
    tot++;
    Next[tot] = Head[u];
    Head[u] = tot;
    To[tot] = v;
}
bool used[10010];
int c[10010];
int main() {
    scanf("%d%d", &n,&m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &u,&v);
        addedge(u,v);
        addedge(v,u);
    }
    for (int i = n;i;i--) {
        int now=0;
        for(int j=1;j<=n;j++)
            if(label[j]>=label[now]&&!vis[j])
                now=j;
        vis[now]=true;
        q[i]=now;
        for(int it=Head[now];it;it=Next[it])
            label[To[it]]++;
    }
    int ans=0;
    for(int i=n;i;i--){
        int u=q[i];
        for(int it=Head[u];it;it=Next[it]){
            int v=To[it];
            used[c[v]]=true;
        }
        int res=0;
        for(int i=1;i<=n;i++)
            if(!used[i]){
                res=i;
                break;
            }
        c[u]=res;
        ans=max(ans,res);
        for(int it=Head[u];it;it=Next[it])
            used[c[To[it]]]=false;
    }
    printf("%d\n", ans);
    system("pause");
    return 0;
}