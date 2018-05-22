#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
#define cmin(a,b) a=min(a,b)
#define cmax(a,b) a=max(a,b)

struct Tree{
    int ch[2],Min[3],Max[3],d[3],val,cur;
}tree[100010];
int n,m,t,x,y,l,r,cmp_d,ans,root,val[100010],pre[100010];
bool cmp(const Tree &a,const Tree &b){
    return (a.d[cmp_d]<b.d[cmp_d])||(a.d[cmp_d]==b.d[cmp_d]&&a.d[(cmp_d+1)%3]<b.d[(cmp_d+1)%3])||(a.d[cmp_d]==b.d[cmp_d]&&a.d[(cmp_d+1)%3]==b.d[(cmp_d+1)%3]&&a.d[(cmp_d+2)%3]<b.d[(cmp_d+2)%3]);
}
void push_up(int rt,int s){
    cmin(tree[rt].Min[0],tree[s].Min[0]);
    cmin(tree[rt].Min[1],tree[s].Min[1]);
    cmin(tree[rt].Min[2],tree[s].Min[2]);
    cmax(tree[rt].Max[0],tree[s].Max[0]);
    cmax(tree[rt].Max[1],tree[s].Max[1]);
    cmax(tree[rt].Max[2],tree[s].Max[2]);
    cmax(tree[rt].val,tree[s].val);
}
int build(int l,int r,int D){
    int mid=(l+r)>>1;
    cmp_d=D;
    nth_element(tree+1+l,tree+1+mid,tree+1+r,cmp);
    for(int _=0;_<=2;_++)
        tree[mid].Max[_]=tree[mid].Min[_]=tree[mid].d[_];
    if(l!=mid)
        tree[mid].ch[0]=build(l,mid-1,(D+1)%3),push_up(mid,tree[mid].ch[0]);
    if(r!=mid)
        tree[mid].ch[1]=build(mid+1,r,(D+1)%3),push_up(mid,tree[mid].ch[1]);
    return mid;
}

int query(int p){
    if(p==0) return 0;
    if(tree[p].Min[0]>=l&&tree[p].Max[0]<=r&&tree[p].Max[1]<l&&tree[p].Min[2]>r) return tree[p].val;
    if(tree[p].Min[0]>r||tree[p].Max[0]<l||tree[p].Min[1]>=l||tree[p].Max[2]<=r) return 0;
    int ans=0;
    if(tree[p].d[0]>=l&&tree[p].d[0]<=r&&tree[p].d[1]<l&&tree[p].d[2]>r) ans=tree[p].cur;
    if(tree[p].ch[0]&&tree[tree[p].ch[0]].val>ans)
        ans=max(ans,query(tree[p].ch[0]));
    if(tree[p].ch[1]&&tree[tree[p].ch[1]].val>ans)
        ans=max(ans,query(tree[p].ch[1]));
    return ans;
}


int main() {
    scanf("%d%d", &n,&m);
    for (int i = 1; i <= n; i++){
        scanf("%d",&val[i]);
        tree[i].d[1]=pre[val[i]];
        pre[val[i]]=i;
        tree[i].d[0]=i;
        tree[i].val=tree[i].cur=val[i];
    }
    memset(pre,0,sizeof pre);
    for(int i=n;i>=1;i--){
        tree[i].d[2]=((pre[val[i]]==0)?n+1:pre[val[i]]);
        pre[val[i]]=i;
    }
    int lastans=0;
    root=build(1,n,0);
    for(int i=1;i<=m;i++){
        scanf("%d%d", &x,&y);
        l=min((x+lastans)%n+1,(y+lastans)%n+1);
        r=max((x+lastans)%n+1,(y+lastans)%n+1);
        lastans=query(root);
        printf("%d\n", lastans);
    }
    system("pause");
    return 0;
}