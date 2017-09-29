#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
vector<int>vec[1000010];
int n,a[1000010],ans,in[1000010],fa[1000010],size[1000010],in0[1000010];
bool iscir[1000010],glo_vis[1000010],killed[1000010];
int ans1;
int _in[1000010];
void dfs(int x,int blocks){
    glo_vis[x]=true;
    size[blocks]++;
    iscir[blocks]&=(in[x]!=0);
    if (in[x]==0) in0[blocks]++;
    for(int i=0;i<vec[x].size();i++){
        int v=vec[x][i];
        if (!glo_vis[v]){
            dfs(v,blocks);
        }
    }
}

int get_father(int x){
    return fa[x]==0?x:fa[x]=get_father(fa[x]);
}

void addedge(int u,int v){
    vec[u].push_back(v);
    in[v]++;
    int fax=get_father(u);
    int fay=get_father(v);
    if (fax!=fay)
    fa[fax]=fay;
}

int bfs(){
    queue<int>Q;
    int res=0;
    for(int i=1;i<=n;i++){
        _in[i]=in[i];
        if (in[i]==0){
            Q.push(i);
        }
    }
    while(!Q.empty()){
        int u=Q.front();
        Q.pop();
        if (killed[a[u]]) continue;
        killed[a[u]]=true;
        res++;
        
        for (int i=0;i<vec[a[u]].size();i++){
            int v=vec[a[u]][i];
            _in[v]--;
            if (_in[v]==0){
                Q.push(v);
            }
        }
    }
    return res;
}

int main(){
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        addedge(i,a[i]);
        iscir[i]=true;
    }
    int ans1=0;
    
    ans1+=bfs();
    for(int i=1;i<=n;i++){
        if (!glo_vis[i]) dfs(i,get_father(i));
    }
    for (int i=1;i<=n;i++){
        if (size[i]==0) continue;
        if (iscir[i]){
            if (size[i]&1)
            ans1+=(size[i]/2)+1;else ans1+=size[i]/2;
        }
    }
    for (int i=1;i<=n;i++){
        if (size[i]==0) continue;
        if (iscir[i]) {
            ans+=size[i]-1;
        }else{
            ans+=size[i]-in0[i];
        }
    }
    printf("%d %d\n",ans1,ans);
}
