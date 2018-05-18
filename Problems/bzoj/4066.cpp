#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
#define cmin(a,b) a=min(a,b)
#define cmax(a,b) a=max(a,b)

struct Tree{
    int ch[2],Min[2],Max[2],d[2],cur,tot;
}tree[200010];
int limnum=2000;
struct Triple{
    int a,b,c;
}stored[2010];
int n,m,t,x,y,cmp_d,ans,root,tmpnum,x1,y1,x2,y2,A;
bool cmp(const Tree &a,const Tree &b){
    return (a.d[cmp_d]<b.d[cmp_d])||(a.d[cmp_d]==b.d[cmp_d]&&a.d[cmp_d^1]<b.d[cmp_d^1]);
}
void push_up(int rt,int s){
    cmin(tree[rt].Min[0],tree[s].Min[0]);
    cmin(tree[rt].Min[1],tree[s].Min[1]);
    cmax(tree[rt].Max[0],tree[s].Max[0]);
    cmax(tree[rt].Max[1],tree[s].Max[1]);
    tree[rt].tot+=tree[s].tot;
}
int build(int l,int r,int D){
    int mid=(l+r)>>1;
    cmp_d=D;
    nth_element(tree+1+l,tree+1+mid,tree+1+r,cmp);
    tree[mid].tot=tree[mid].cur;
    tree[mid].ch[0]=tree[mid].ch[1]=0;
    tree[mid].Max[0]=tree[mid].Min[0]=tree[mid].d[0];
    tree[mid].Max[1]=tree[mid].Min[1]=tree[mid].d[1];
    if(l!=mid)
        tree[mid].ch[0]=build(l,mid-1,D^1),push_up(mid,tree[mid].ch[0]);
    if(r!=mid)
        tree[mid].ch[1]=build(mid+1,r,D^1),push_up(mid,tree[mid].ch[1]);
    return mid;
}

int query(int p){
    if(p==0) return 0;
    if(tree[p].Min[0]>=x1&&tree[p].Max[0]<=x2&&tree[p].Min[1]>=y1&&tree[p].Max[1]<=y2) return tree[p].tot;
    if(tree[p].Min[0]>x2||tree[p].Max[0]<x1||tree[p].Min[1]>y2||tree[p].Max[1]<y1) return 0;
    int ans=query(tree[p].ch[0])+query(tree[p].ch[1]);
    if(tree[p].d[0]>=x1&&tree[p].d[0]<=x2&&tree[p].d[1]>=y1&&tree[p].d[1]<=y2)ans+=tree[p].cur;
    return ans;
}

int main() {
    
    scanf("%d", &m);
    int lastans=0;
    while(1){
        scanf("%d", &t);
        if(t==3) break;
        if(t==1){
            scanf("%d%d%d", &x,&y,&A);
            x^=lastans,y^=lastans,A^=lastans;
            stored[++tmpnum]=(Triple){x,y,A};
            if(tmpnum==limnum){
                for(int j=1;j<=tmpnum;j++){
                    n++;
                    tree[n]=(Tree){0,0,stored[j].a,stored[j].b,stored[j].a,stored[j].b,stored[j].a,stored[j].b,stored[j].c,stored[j].c};
                }
                tmpnum=0;
                root=build(1,n,0);
            }
        }else{
            ans=0;
            scanf("%d%d%d%d", &x1,&y1,&x2,&y2);
            x1^=lastans,x2^=lastans,y1^=lastans,y2^=lastans;
            for(int i=1;i<=tmpnum;i++)
                if(stored[i].a>=x1&&stored[i].a<=x2&&stored[i].b>=y1&&stored[i].b<=y2)
                    ans+=stored[i].c;
            ans+=query(root);
            lastans=ans;
            printf("%d\n", ans);
        }
    }
    system("pause");
    return 0;
}