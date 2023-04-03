#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n;
char st[50][50];
int fa[50],size[50],id[50],tot,lg[(1<<23)+5],g[(1<<23)+5],cnt[(1<<23)+5],edge[50];

int getf(int x){
    return fa[x]==x?x:fa[x]=getf(fa[x]);
}

void merge(int a,int b){
    int x=getf(a),y=getf(b);
    if(x!=y)fa[x]=y,size[y]+=size[x];
}

int fpow(int a,int b){
    int res=1;
    while(b){
        if(b&1)res=res*a;
        a=a*a;
        b>>=1;
    }
    return res;
}

bool check(int k){
    int ans=0;
    for(int i=0;i<(1<<tot);i++)
        ans+=(((tot^cnt[i])&1)?-1:1)*fpow(g[i],k);
    return ans!=0;
}

void dfs(int rest,int sta){
    g[sta]=1;
    if(rest==0) return;
    int mn=0x3f3f3f3f,mnid=0,prest=rest;
    while(prest){
        int bit=prest&-prest;
        int id=lg[bit];
        prest^=bit;
        if(cnt[edge[id]&rest]<mn)
            mn=cnt[edge[id]&rest],mnid=id;
    }
    dfs(rest^(1<<mnid)^(edge[mnid]&rest),sta|(1<<mnid));
    int N=edge[mnid]&rest;
    while(N){
        int bit=N&-N;
        int id=lg[bit];
        N^=bit;
        dfs(rest^(1<<id)^(edge[id]&rest),sta|(1<<id));
    }
    return;
}

int main() {
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        scanf("%s", st[i]);
        fa[i]=i,size[i]=1;
        for(int j=0;j<i;j++)
            if(st[i][j]=='A')
                merge(i,j);
    }
    memset(id,-1,sizeof id);
    for(int i=0;i<n;i++)
        if(getf(i)==i&&size[i]>1)
            id[i]=tot++;
    if(!tot){
        printf("%d\n", n-1);
        return 0;
    }
    for(int i=0;i<n;i++)
        for(int j=0;j<i;j++)
            if(st[i][j]=='X'){
                int x=getf(i),y=getf(j);
                if(x==y){
                    printf("-1\n");
                    return 0;
                }
                if(id[x]!=-1&&id[y]!=-1)edge[id[x]]|=1<<id[y],edge[id[y]]|=1<<id[x];
            }
    for(int i=0;i<tot;i++)
        lg[1<<i]=i;
    dfs((1<<tot)-1,0);
    for(int i=0;i<tot;i++)
        for(int j=0;j<(1<<tot);j++)
            if((j>>i)&1)
                g[j]+=g[j^(1<<i)];
    for(int i=1;i<(1<<tot);i++)
        cnt[i]=cnt[i>>1]+(i&1);
    int l=1,r=tot,ans=1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid))
            r=mid-1,ans=mid;
        else
            l=mid+1;
    }
    printf("%d\n", n-1+ans);
    system("pause");
    return 0;
}