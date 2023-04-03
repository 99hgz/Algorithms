#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
#define fi first
#define se second
struct TREE{
    int ls,rs,mn,mx;
}tree[100010*30];
int tot,cnt,n,m,rt,a[100010],fa[100010],ans;
typedef pair<int,int> pr;
pr mx[100010];
pr max(pr a,pr b){
    if(b.fi>a.fi)
        a=b;
    return a;
}

int newnode(){
    tot++;
    tree[tot].mn=0x3f3f3f3f;
    tree[tot].mx=tree[tot].ls=tree[tot].rs=0;
    return tot;
}

void insert(int &rt,int id,int val,int bitpos){
    //printf("insert:%d %d %d %d\n", rt,id,val,bitpos);
    if(bitpos<0){
        tree[rt].mx=tree[rt].mn=id;
        return;
    }
    tree[rt].mx=max(tree[rt].mx,id);
    tree[rt].mn=min(tree[rt].mn,id);
    if((val>>bitpos)&1)
        insert(tree[rt].rs,id,val,bitpos-1);
    else
        insert(tree[rt].ls,id,val,bitpos-1);
}

int merge(int l,int r){
    if(!r)return l;
    if(!l)l=newnode();
    tree[l].mx=max(tree[l].mx,tree[r].mx);
    tree[l].mn=min(tree[l].mn,tree[r].mn);
    tree[l].ls=merge(tree[l].ls,tree[r].ls);
    tree[l].rs=merge(tree[l].rs,tree[r].rs);
    return l;
}

void dfs(int rt,int bitpos){
    if(bitpos<0)return;
    if(!rt)return;
    dfs(tree[rt].ls,bitpos-1);
    dfs(tree[rt].rs,bitpos-1);
    tree[rt].ls=merge(tree[rt].ls,tree[rt].rs);
}

int getf(int x){
    return fa[x]==0?x:fa[x]=getf(fa[x]);
}
void fmerge(int a,int b){
    //printf("%d %d\n", a,b);
    int fx=getf(a),fy=getf(b);
    if(fx!=fy)
        fa[fx]=fy;
}

void build(){
    tot=0;
    rt=newnode();
    for(int i=1;i<=n;i++)
        insert(rt,getf(i),a[i],m-1);
    dfs(rt,m-1);
}

pr query(int fx,int x){
    int cur=rt;
    pr res=make_pair(0,0);
    for(int bitpos=m-1;bitpos>=0;bitpos--){
        if(((x>>bitpos)&1)){
            if((fx!=tree[tree[cur].rs].mn||fx!=tree[tree[cur].rs].mx))
                cur=tree[cur].rs,res.fi+=(1<<bitpos);
            else
                cur=tree[cur].ls;
        }else
            cur=tree[cur].ls;
    }
    res.se=tree[cur].mn;
    return res;
}

int main() {
    scanf("%d%d", &n,&m);
    cnt=n;
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    while(cnt>1){
        build();
        for(int i=1;i<=n;i++)
            mx[i]=make_pair(0,0);
        for(int i=1;i<=n;i++)
            mx[getf(i)]=max(mx[getf(i)],query(getf(i),a[i]));
         for(int i=1;i<=n;i++)
            if(!fa[i])
                ans+=mx[i].fi,cnt--,fmerge(mx[i].se,i);
    }
    printf("%d\n", ans);
    system("pause");
    return 0;
}