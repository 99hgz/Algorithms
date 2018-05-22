#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n,m,u,v;
int tot,Head[1010],Next[5010010],To[5010010],label[1010],q[1010];
bool mp[1010][1010],vis[1010];
int p[1010],rk[1010];
void addedge(int u, int v)
{
    tot++;
    Next[tot] = Head[u];
    Head[u] = tot;
    To[tot] = v;
    mp[u][v]=true;
}

bool cmp(int a,int b){
    return rk[a]<rk[b];
}

bool check(){
    for(int i=n;i;i--){
        int u=q[i],cnt=0;
        for(int it=Head[u];it;it=Next[it])
            if(rk[u]<rk[To[it]])p[++cnt]=To[it];
        sort(p+1,p+1+cnt,cmp);
        //printf("check %d %d\n",u,p[1] );
        for(int j=2;j<=cnt;j++)
            if(!mp[p[1]][p[j]]){
               // printf("edge:%d %d\n", p[1],p[j]);
                return false;
            }
    }
    return true;
}

int main() {
    freopen("D:/tmp/1242/net7.in","r",stdin);
    scanf("%d%d", &n,&m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &u,&v);
        addedge(u,v);
        addedge(v,u);
    }
    label[0]=-1;
    for (int i = n;i;i--) {
        int now=0;
        for(int j=1;j<=n;j++)
            if(label[j]>label[now]&&!vis[j])
                now=j;
        vis[now]=true;
        q[i]=now;
        for(int it=Head[now];it;it=Next[it])
            label[To[it]]++;
        rk[now]=i;
    }

    printf("%s\n", check()?"Perfect":"Imperfect");    
    system("pause");
    return 0;
}