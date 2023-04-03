#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int,int> pr;
#define fi first
#define se second

vector<pr> ans[200010];
struct Node
{
  int d, id;
};
struct cmp
{
  bool operator()(Node a, Node b) { return a.d > b.d; }
};
priority_queue<Node, vector<Node>, cmp> Q;
int cnt,Head[200010],Next[800010],To[800010],Val[800010],dis[200010],vis[200010];
int n,m;

struct EDGE
{
    int u,v,l,a;
}edge[800010];
bool cmp1(EDGE a,EDGE b){
    return a.a>b.a;
}

void addedge(int u,int v,int l){
    cnt++;
    Next[cnt]=Head[u];
    Head[u]=cnt;
    To[cnt]=v;
    Val[cnt]=l;
}

void dij(){
    Q.push((Node){0,1});
    memset(dis,0x3f3f3f3f,sizeof dis);
    dis[1]=0;
    while(!Q.empty()){
        Node tmp=Q.top();
        int u=tmp.id;
        Q.pop();
        if(vis[u])
            continue;
        vis[u]=1;
        for(int it=Head[u];it;it=Next[it]){
            int v=To[it];
            if(!vis[v]&&dis[v]>dis[u]+Val[it]){
                dis[v]=dis[u]+Val[it];
                Q.push((Node){dis[v],v});
            }
        }
    }
}

int rk[200010],mn[200010],path[200010],root[200010],fa[200010],q,k,s,v,p;

int getf(int x){
    int cur=x;
    while(fa[cur])
        cur=fa[cur];
    return cur;
}
int main() {
    int t;
    scanf("%d", &t);
    while(t--){
        memset(rk,0,sizeof rk);
        memset(mn,0,sizeof mn);
        memset(path,0,sizeof path);
        memset(root,0,sizeof root);
        memset(fa,0,sizeof fa);
        memset(Head,0,sizeof Head);
        memset(vis,0,sizeof vis);
        while(!Q.empty())Q.pop();
        cnt=0;

        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++){
            scanf("%d%d%d%d", &edge[i].u,&edge[i].v,&edge[i].l,&edge[i].a);
            addedge(edge[i].u,edge[i].v,edge[i].l);
            addedge(edge[i].v,edge[i].u,edge[i].l);
        }
        dij();
        for(int i=1;i<=n;i++)
            ans[i].clear(),ans[i].push_back(make_pair(0x3f3f3f3f,dis[i])),mn[i]=dis[i];
            
        sort(edge+1,edge+1+m,cmp1);
        for(int i=1;i<=m;i++){ 
            int x=getf(edge[i].u),y=getf(edge[i].v);
            if(x!=y){
                if (rk[x] <= rk[y])
                {
                    fa[x] = y;
                    path[x] = edge[i].a;
                    if(mn[x]<mn[y]){
                        mn[y]=mn[x];
                        vector<pr>::iterator it=ans[y].end();
                        it--;
                        if((*it).fi==edge[i].a) ans[y].pop_back();
                        ans[y].push_back(make_pair(edge[i].a,mn[y]));
                    }
                    if (rk[x] == rk[y])
                        rk[y]++;
                }
                else{
                    fa[y]=x,path[y]=edge[i].a;
                    if(mn[y]<mn[x]){
                        mn[x]=mn[y];
                        vector<pr>::iterator it=ans[x].end();
                        it--;
                        if((*it).fi==edge[i].a) ans[x].pop_back();
                        ans[x].push_back(make_pair(edge[i].a,mn[x]));
                    }
                }
            }
        }
        scanf("%d%d%d", &q,&k,&s);
        int lastans=0;
        for(int i=1;i<=q;i++){
            scanf("%d%d", &v,&p);
            v=(v+k*lastans-1)%n+1;
            p=(p+k*lastans)%(s+1);

            int cur=v;
            while(path[cur]>p)
                cur=fa[cur];
            int l=0,r=ans[cur].size()-1,res=0;
            while(l<=r){
                int mid=(l+r)>>1;
                if(ans[cur][mid].fi>p)
                    res=mid,l=mid+1;
                else 
                    r=mid-1;
            }
            printf("%d\n", lastans=ans[cur][res].se);
        }
    }
    system("pause");
    return 0;
}