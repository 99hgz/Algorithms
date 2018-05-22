#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
#define cmin(a,b) a=min(a,b)
#define cmax(a,b) a=max(a,b)

struct Tree{
    int ch[2],Min[2],Max[2],d[2];
}tree[1000010];
int n,m,t,x,y,cmp_d,ans,root;
bool cmp(const Tree &a,const Tree &b){
    return (a.d[cmp_d]<b.d[cmp_d])||(a.d[cmp_d]==b.d[cmp_d]&&a.d[cmp_d^1]<b.d[cmp_d^1]);
}
void push_up(int rt,int s){
    cmin(tree[rt].Min[0],tree[s].Min[0]);
    cmin(tree[rt].Min[1],tree[s].Min[1]);
    cmax(tree[rt].Max[0],tree[s].Max[0]);
    cmax(tree[rt].Max[1],tree[s].Max[1]);
}
int build(int l,int r,int D){
    int mid=(l+r)>>1;
    cmp_d=D;
    nth_element(tree+1+l,tree+1+mid,tree+1+r,cmp);
    
    tree[mid].Max[0]=tree[mid].Min[0]=tree[mid].d[0];
    tree[mid].Max[1]=tree[mid].Min[1]=tree[mid].d[1];
    if(l!=mid)
        tree[mid].ch[0]=build(l,mid-1,D^1),push_up(mid,tree[mid].ch[0]);
    if(r!=mid)
        tree[mid].ch[1]=build(mid+1,r,D^1),push_up(mid,tree[mid].ch[1]);
    return mid;
}

int dis(int p,int x,int y){
    int ans=0;
    if(x<tree[p].Min[0])
        ans+=abs(x-tree[p].Min[0]);
    if(y<tree[p].Min[1])
        ans+=abs(y-tree[p].Min[1]);
    if(x>tree[p].Max[0])
        ans+=abs(x-tree[p].Max[0]);
    if(y>tree[p].Max[1])
        ans+=abs(y-tree[p].Max[1]);
    return ans;
}
void insert(int cur){
    int D=0,p=root;
    while(1){
        push_up(p,cur);
        int _=(tree[cur].d[D]>=tree[p].d[D]);
        if(!tree[p].ch[_]){
            tree[p].ch[_]=cur;
            return;
        }else p=tree[p].ch[_];
        D^=1;
    }
}

void query(int p){
    cmin(ans,abs(tree[p].d[0]-x)+abs(tree[p].d[1]-y));
    int d[2];
    d[0]=d[1]=0x7f7f7f7f;
    for(int fx=0;fx<=1;fx++)
        if(tree[p].ch[fx])
            d[fx]=dis(tree[p].ch[fx],x,y);
    int fx=(d[0]>=d[1]);
    if(d[fx]<ans)query(tree[p].ch[fx]);
    fx^=1;
    if(d[fx]<ans)query(tree[p].ch[fx]);
}


int main() {
    scanf("%d%d", &n,&m);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &tree[i].d[0],&tree[i].d[1]);
    root=build(1,n,0);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d", &t,&x,&y);
        if(t==1){
            n++;
            tree[n]=(Tree){0,0,x,y,x,y,x,y};
            insert(n);
        }else{
            ans=0x7f7f7f7f;
            query(root);
            printf("%d\n", ans);
        }
    }
    system("pause");
    return 0;
}