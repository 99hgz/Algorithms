#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
 
int n,m,u,v,a[100010],d[100010];
struct Node{
    int u,v;
};
int q[100010];
ll ans[3];
bool flag[100010];
int bg[100010],bgtot;
int cnt,Head[100010],Next[500010],To[500010];
namespace Hashmap{
    int MOD=1000007;
    int cnt,Head[1000007],Next[500010];
    Node Val[500010];
    void add(int hsh,Node x){
        cnt++;
        Next[cnt]=Head[hsh];
        Head[hsh]=cnt;
        Val[cnt]=x;
    }
    void insert(int u,int v){
        if(u>v) swap(u,v);
        int hsh=(u*2333+v)%MOD;
        add(hsh,(Node){u,v});
    }
    bool query(int u,int v){
        if(u>v) swap(u,v);
        int hsh=(u*2333+v)%MOD;
        for(int it=Head[hsh];it;it=Next[it])
            if(Val[it].u==u&&Val[it].v==v) return true;
        return false;
    }
}
 
void addedge(int u,int v){
    cnt++;
    Next[cnt]=Head[u];
    Head[u]=cnt;
    To[cnt]=v;
}
 
int main() {
    scanf("%d%d", &n,&m);
    for (int i = 1; i <= n; i++) 
        scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++){
        scanf("%d%d", &u,&v);
        addedge(u,v);
        addedge(v,u);
        d[u]++,d[v]++;
        Hashmap::insert(u,v);
    }
    int rg=sqrt(m);
    for(int i=1;i<=n;i++)
        if(d[i]>rg)
            flag[i]=true,bg[++bgtot]=i;
    for(int i=1;i<=n;i++)
        if(!flag[i])
            for(int it=Head[i];it;it=Next[it])
                for(int it2=Next[it];it2;it2=Next[it2])
                    if(Hashmap::query(To[it],To[it2]))
                        ans[flag[i]+flag[To[it]]+flag[To[it2]]]+=max(a[i],max(a[To[it]],a[To[it2]]));
    for(int i=1;i<=bgtot;i++)
        for(int j=i+1;j<=bgtot;j++)
            for(int k=j+1;k<=bgtot;k++)
                if(Hashmap::query(bg[i],bg[j])&&Hashmap::query(bg[i],bg[k])&&Hashmap::query(bg[k],bg[j]))
                    ans[2]+=max(a[bg[i]],max(a[bg[j]],a[bg[k]]));
    printf("%lld\n", ans[0]/3+ans[1]/2+ans[2]);
    system("pause");
    return 0;
}