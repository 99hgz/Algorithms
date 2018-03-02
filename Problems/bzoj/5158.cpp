#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int n,a[100010],res;
ll ans;
int b[100010];
int query(int x){
    int res=0;
    for(;x;x-=x&(-x))
        res=max(res,b[x]);
    return res;
}
void add(int x,int v){
    for(;x<=n;x+=x&(-x))
        b[x]=max(b[x],v);
}

int tot,cnt,Head[100010],Next[100010],To[100010];

void addedge(int u,int v){
    tot++;
    Next[tot]=Head[u];
    Head[u]=tot;
    To[tot]=v;
}

void dfs(int rt){
    //printf("%d\n", rt);
    a[rt]=cnt++;
    for (int it=Head[rt];it;it=Next[it])
        dfs(To[it]);
}
int pos[100010];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) {
        res=pos[a[i]-1];
        addedge(res,i);
        pos[a[i]]=i;
    }
    dfs(0);
    for(int i=n;i;i--){
        res=query(a[i]-1)+1;
        ans+=res;
        add(a[i],res);
    }
    printf("%lld\n", ans);
    system("pause");
    return 0;
}

/*#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int a[10],f[10],n;

void check(){
    memset(f,0,sizeof f);
    printf("per=" );
    for (int i = 1; i <= n; i++)
        printf("%d ",a[i] );
    printf("\n" );
    for (int i = 1; i <= n; i++){
        int res=0;
        for (int j = 1; j <= i-1; j++)
            if (a[j]<a[i]&&f[j]>res)
                res=f[j];
        f[i]=res+1;
    }
    printf("ans=" );
    for (int i = 1; i <= n; i++)
        printf("%d ",f[i] );
    printf("\n" );
}

int main() {
    n=5;
    for (int i = 1; i <= n; i++)
        a[i]=i;
    do{
        check();
    }while(next_permutation(a+1,a+1+n));
    system("pause");
    return 0;
}*/