#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
bool vis[5010];
vector<int>vec[5010];
int dis[5010],n,fnum[5010];
ll ans;
ll check(int rt){
 memset(vis,0,sizeof vis);
 queue<int>q;
 q.push(rt);
 vis[rt]=true;
 dis[rt]=0;
 int used=1;
 ll sum=0;
 while(!q.empty()){
  int u=q.front();
  q.pop();
  for (int i=0;i<vec[u].size();i++){
   int v=vec[u][i];
   if (!vis[v]){
    dis[v]=dis[u]+1;
    sum+=dis[v];
    used++;
    vis[v]=true;
    q.push(v);
   }
  }
 }
 if (used!=n) return ans;else return sum;
}


int main(){
 scanf("%d",&n);
 for (int i=1;i<=n;i++){
  scanf("%d",&fnum[i]);
  for (int j=1;j<=fnum[i];j++){
   int x;
   scanf("%d",&x);
   vec[x].push_back(i);
  }
 }
 ans=0x3f3f3f3f3f3f3f3f;
 for(int i=1;i<=n;i++){
  ans=min(ans,check(i));
 }
 printf("%lld\n",ans+n);
}
