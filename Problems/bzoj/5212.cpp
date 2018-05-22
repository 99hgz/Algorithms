#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
ll siz[400010];//所有儿子次数和
ll sum[400010];//轻儿子次数和
int ch[400010][2],fa[400010];
int n,m,a[400010],u,v,x;
ll dp[400010],w,ans;
bool islf[400010];

int tot,Head[400010],Next[400010*2],To[400010*2];
void addedge(int u,int v){
    tot++;
    Next[tot]=Head[u];
    Head[u]=tot;
    To[tot]=v;
}

void dfs(int x,int f){
    bool flag=true;
    siz[x]=a[x];ll mx=a[x];
    for(int it=Head[x];it;it=Next[it]){
        int v=To[it];
        if(v!=f){
            fa[v]=x;
            flag=false;
            dfs(v,x);
            dp[x]+=dp[v];
            siz[x]+=siz[v];
            mx=max(mx,siz[v]);
        }
    }
    if(mx>(siz[x]+1)/2)
        dp[x]+=2*(siz[x]-mx);
    else
        dp[x]+=siz[x]-1;
    for(int it=Head[x];it;it=Next[it]){
        int v=To[it];
        if(v!=f){
            if(siz[v]>(siz[x]+1)/2)
                ch[x][1]=v;
            else
                sum[x]+=siz[v];
        }
    }
    if(flag)
        islf[x]=true;
}

ll get(ll tot,ll mx){
    return min(tot-1,2LL*(tot-mx));
}

bool isroot(int rt)
{
    return ch[fa[rt]][0] != rt && ch[fa[rt]][1] != rt;
}

int get(int x)
{
    return ch[fa[x]][1] == x;
}

void update(int x)
{
    siz[x]=sum[x]+a[x];
    if(ch[x][0]) siz[x]+=siz[ch[x][0]];
    if(ch[x][1]) siz[x]+=siz[ch[x][1]];
}

void rotate(int x)
{
    int old = fa[x], oldf = fa[old], which = get(x);
    if (!isroot(old))
        ch[oldf][ch[oldf][1] == old] = x;
    ch[old][which] = ch[x][which ^ 1];
    fa[ch[old][which]] = old;
    fa[old] = x;
    ch[x][which ^ 1] = old;
    fa[x] = oldf;
    update(old), update(x);
}
void splay(int x){
    while(!isroot(x)){
        int y=fa[x],z=fa[y];
        if(!isroot(y)){
            if(ch[y][0]==x ^ ch[z][0]==y)
                rotate(x);
            else
                rotate(y);
        }
        rotate(x);
    }
}

void access(int x,ll y){
    for(int t=0;x;){
        splay(x);
        ll now=siz[t],nxt=siz[x];
        if(ch[x][0])nxt-=siz[ch[x][0]];
        nxt+=y;
        if(!t){
            a[x]+=y;
            if(ch[x][1] && siz[ch[x][1]]<=(nxt+1)/2){
                ans+=get(nxt,a[x])-get(nxt-y,siz[ch[x][1]]);
                sum[x]+=siz[ch[x][1]];
                ch[x][1]=0;
            }else if(!islf[x]){
                if(ch[x][1])
                    ans+=y*2;
                else
                    ans+=get(nxt,a[x])-get(nxt-y,a[x]-y);
            }
        }else{
            sum[x]+=y;
            if(ch[x][1] && siz[ch[x][1]]<=(nxt+1)/2){
                ans+=get(nxt,a[x])-get(nxt-y,siz[ch[x][1]]);
                sum[x]+=siz[ch[x][1]];ch[x][1]=0;
            }else if(!islf[x]){
                if(ch[x][1])
                    ans+=y*2;
                else
                    ans+=get(nxt,a[x])-get(nxt-y,a[x]);
            }
            if(now>(nxt+1)/2){
                ans+=get(nxt,now)-get(nxt,a[x]);
                sum[x]+=siz[ch[x][1]];
                ch[x][1]=t;
                sum[x]-=siz[t];
            }
        }
        update(x);
        t=x;
        x=fa[x];
    }
}

int main() {
    scanf("%d%d", &n,&m);
    for (int i = 1; i <= n; i++) 
        scanf("%d", &a[i]);
    for (int i = 1; i <= n-1; i++) {
        scanf("%d%d", &u,&v);
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1,1);
    printf("%lld\n", dp[1]);
    ans=dp[1];
    for(int i=1;i<=m;i++){
        scanf("%d%lld", &x,&w);
        access(x,w);
        printf("%lld\n", ans);
    }
    system("pause");
    return 0;
}