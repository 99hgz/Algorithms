#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
ll MOD=1000000007;
int fa[2000010],n,m,f[5000010],maxR,p,col[5000010],vis[5000010];
ll ans=1;
char S[5000010],a[5000010];

int cnt,Head[5000010],Next[5000010],To[5000010];

void addedge(int u,int v){
    if(!u||v>2*n||u&1||v&1) return;
    u>>=1,v>>=1;
    //printf("addedge:%d %d\n", u,v);
    cnt++;
    Next[cnt]=Head[u];
    Head[u]=cnt;
    To[cnt]=v;

    swap(u,v);
    cnt++;
    Next[cnt]=Head[u];
    Head[u]=cnt;
    To[cnt]=v;
}

int gf(int x){
    return fa[x]==0?x:fa[x]=gf(fa[x]);
}

void mg(int x,int y){
    if(x&1) return;
    x>>=1,y>>=1;
    int fx=gf(x),fy=gf(y);
    if(fx!=fy)
        fa[fx]=fy;
}

int main() {
    scanf("%s",S);
    int m=strlen(S);
    a[0]='@';
    for(int i=0;S[i];i++)
        a[++n]='#',a[++n]=S[i];
    a[++n]='#';
    a[n+1]='*';
    for(int i=1;i<=n;i++){
        f[i]=(i<maxR)?min(f[2*p-i],maxR-i+1):1;
        while(i-f[i]>0&&i+f[i]<=n&&a[i-f[i]]==a[i+f[i]]){mg(i-f[i],i+f[i]);f[i]++;}
        addedge((i-f[i]),(i+f[i]));
        if(i+f[i]-1>maxR) maxR=i+f[i]-1,p=i;
    }
    for(int i=1;i<=m;i++){
        int fl=gf(i);
        if(!col[fl]){
            int p=26;
            for(int it=Head[i];it;it=Next[it])
                if(col[gf(To[it])]&&vis[gf(To[it])]!=i){
                    vis[gf(To[it])]=i;
                    p--;
                }
            col[fl]=1;
            ans=ans*p%MOD;
        }
    }
    printf("%lld\n", ans);
    system("pause");
    return 0;
}