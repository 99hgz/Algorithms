#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n,m,u,v,a[100010],d[100010];
struct Node{
    int u,v;
};
int q[100010];
ll ans;
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
    for(int i=1;i<=n;i++){
        int pnt=0;
        for(int it=Head[i];it;it=Next[it])
            if(d[i]<d[To[it]]||(d[i]==d[To[it]]&&i<To[it]))
                q[++pnt]=To[it];
        for(int j=1;j<=pnt;j++)
            for(int k=1;k<j;k++)
                if(Hashmap::query(q[j],q[k]))
                    ans+=max(a[i],max(a[q[j]],a[q[k]]));
    }
    printf("%lld\n", ans);
    system("pause");
    return 0;
}