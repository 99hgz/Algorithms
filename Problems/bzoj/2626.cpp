#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
#define cmin(a,b) a=min(a,b)
#define cmax(a,b) a=max(a,b)

inline ll sqr(ll x){return x*x;}
struct Tree{
    int ch[2];
    ll Min[2],Max[2],d[2];
    int id;
}tree[100010];
int n,cmp_d,root,k;
ll ans,x,y;
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


ll dis(ll x,ll y,Tree a){
    return sqr(a.d[0]-x)+sqr(a.d[1]-y);
}
ll gx(ll x,ll y,Tree a){
    return max(sqr(a.Min[0]-x),sqr(a.Max[0]-x))+max(sqr(a.Min[1]-y),sqr(a.Max[1]-y));
}

struct Node{
    int key;
    ll val;
};
bool operator <(Node a,Node b){
    return a.val>b.val||(a.val==b.val&&a.key<b.key);
}

priority_queue<Node>Q;
void query(int p,ll x,ll y){
    if(!p) return;
    ll _d=dis(x,y,tree[p]);
    if(_d>Q.top().val||(_d==Q.top().val&&tree[p].id<Q.top().key)){
        Q.pop();
        Q.push((Node){tree[p].id,_d});
    }
    int fx=(gx(x,y,tree[tree[p].ch[0]])<=gx(x,y,tree[tree[p].ch[1]]));
    if(gx(x,y,tree[tree[p].ch[fx]])>=Q.top().val)
        query(tree[p].ch[fx],x,y);
    fx^=1;
    if(gx(x,y,tree[tree[p].ch[fx]])>=Q.top().val)
        query(tree[p].ch[fx],x,y);
}

int main() {
    scanf("%d", &n);
    for(int i=1;i<=n;i++){
        scanf("%lld%lld", &tree[i].d[0],&tree[i].d[1]);
        tree[i].id=i;
    }
    root=build(1,n,0);
    int m;
    scanf("%d", &m);
    for(int i=1;i<=m;i++){
        scanf("%lld%lld%d", &x,&y,&k);
        while(!Q.empty())Q.pop();
        for(int j=1;j<=k;j++)
            Q.push((Node){1000000,-1});
        query(root,x,y);
        printf("%d\n",Q.top().key);
    }
    system("pause");
    return 0;
}