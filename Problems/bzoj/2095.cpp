#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int idu[1010],odu[1010],n,m,u,v,_z,_f;
int cnt;
struct EDGE{
    int u,v,w;
}e[100100];
void addedge(int u,int v,int w){
    e[++cnt]=(EDGE){u,v,w};
}

/*namespace DINIC{
    int cnt,Head[2010],Next[200010],To[200010],Val[200010];
    int q[2010],cur[2010],dis[2010],S,T;

    void addedge(int u,int v,int w){
       // printf("addedge:%d %d %d\n", u,v,w);
        cnt++;
        Next[cnt]=Head[u];
        Head[u]=cnt;
        Val[cnt]=w;
        To[cnt]=v;
        swap(u,v);
        cnt++;
        Next[cnt]=Head[u];
        Head[u]=cnt;
        Val[cnt]=0;
        To[cnt]=v;
    }
    void init(){
        cnt=1;
        memset(Head,0,sizeof Head);
        memset(cur,0,sizeof cur);
    }
    bool bfs(int S){
        q[1]=S;
        memset(dis,0x3f3f3f3f,sizeof dis);
        dis[S]=1;
        int head=0,tail=1;
        while(head<tail){
            head++;
            int u=q[head];
            for(int it=Head[u];it;it=Next[it]){
                int v=To[it];
                if((Val[it])&&(dis[v]==0x3f3f3f3f)){
                    dis[v]=dis[u]+1;
                    q[++tail]=v;
                }
            }
        }
        return dis[T]!=0x3f3f3f3f;
    }
    int dinic(int x,int maxflow){
        if(x==T) return maxflow;
        int used=0;
        for(int it=cur[x];it;it=Next[it]){
            int v=To[it];
            if(dis[v]==dis[x]+1&&Val[it]){
                int tmp=dinic(v,min(Val[it],maxflow-used));
                used+=tmp;
                Val[it]-=tmp;
                Val[it^1]+=tmp;
                cur[x]=it;
                if(used==maxflow) break;
            }
        }
        if(used==0)
            dis[x]=-1;
        return used;
    }
    int work(){
        int res=0;
        while(bfs(S)){
            for(int i=1;i<=T;i++)
                cur[i]=Head[i];
            res+=dinic(S,0x3f3f3f3f);
            //printf("%d\n", res);
        }
        return res;
    }
}*/

namespace DINIC{
    int Q[1100], dep[1100];

    int tot, Head[1100], cur[1100], Next[21000];
    ll Val[21000], To[21000];
    int S, T;

    void init(){
        tot=1;
        memset(Head,0,sizeof Head);
        memset(cur,0,sizeof cur);
    }

    bool bfs()
    {
        memset(dep, -1, sizeof dep);
        int t = 0, w = 1;
        Q[w] = S;
        dep[S] = 0;
        while (t != w)
        {
            t++;
            int u = Q[t];
            for (int it = Head[u]; it; it = Next[it])
            {
                int v = To[it];
                if (Val[it] > 0 && dep[v] == -1)
                {
                    dep[v] = dep[u] + 1;
                    w++;
                    Q[w] = v;
                }
            }
        }
        return dep[T] != -1;
    }

    ll dfs(int x, ll flow)
    {
        if (x == T)
            return flow;
        ll used = 0;
        for (int it = cur[x]; it; it = Next[it])
        {
            int v = To[it];
            if (dep[v] == dep[x] + 1)
            {
                ll tmp = dfs(v, min(Val[it], flow - used));
                used += tmp;
                Val[it] -= tmp;
                Val[it ^ 1] += tmp;
                cur[x] = it;
                if (used == flow)
                    return flow;
            }
        }
        if (used == 0)
            dep[x] = -1;
        return used;
    }

    ll work()
    {
        ll ans = 0;
        while (bfs())
        {
            for (int i = 1; i <= T; i++)
                cur[i] = Head[i];
            ans += dfs(S, 1LL << 60);
        }
        return ans;
    }

    void addedge(int u, int v, ll flow)
    {
        //printf("%d->%d\n", u, v);
        tot++;
        Next[tot] = Head[u];
        Head[u] = tot;
        Val[tot] = flow;
        To[tot] = v;
        tot++;
        Next[tot] = Head[v];
        Head[v] = tot;
        Val[tot] = 0;
        To[tot] = u;
    }
}

bool check(){
    int sum=0;
    for(int i=1;i<=n;i++){
        if(idu[i]==0&&odu[i]==0) return false;
        if(abs(idu[i]-odu[i])&1)
            return false;
        else if(idu[i]>odu[i])
            DINIC::addedge(DINIC::S,i,(idu[i]-odu[i])>>1),sum+=((idu[i]-odu[i])>>1);
        else if(odu[i]>idu[i])
            DINIC::addedge(i,DINIC::T,(odu[i]-idu[i])>>1);
    }
    if(sum==DINIC::work()) return true;else return false;
}

int main() {
    scanf("%d%d", &n,&m);
    int L=1,R=1,ans=-1;
    cnt=1;
    for(int i=1;i<=m;i++){
        scanf("%d%d%d%d",&u,&v,&_z,&_f);
        addedge(u,v,_z);
        addedge(v,u,_f);
        R=max(R,max(_z,_f));
        L=max(L,min(_z,_f));
    }
    while(L<=R){
        int mid=(L+R)>>1;
        DINIC::init();
        DINIC::S=n+1;
        DINIC::T=n+2;
        memset(idu,0,sizeof idu);
        memset(odu,0,sizeof odu);
        for(int i=2;i<=2*m+1;i++)
            if(e[i].w<=mid){
                if(e[i^1].w<=mid){
                    DINIC::addedge(e[i].u,e[i].v,1);
                    if(i&1)idu[e[i].v]++,odu[e[i].u]++;
                }else
                    idu[e[i].v]++,odu[e[i].u]++;
            }
        //printf("check:%d %d %d\n", L,R,mid);
        if(check())
            R=mid-1,ans=mid;
        else
            L=mid+1;
    }
    if(ans==-1)
        printf("NIE\n");
    else
        printf("%d\n",ans);
    system("pause");
    return 0;
}