#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

struct TREE{
    int ans;
    double mx;
}Tree[400010];
int n,m,x,y;

int calc(int rt,int l,int r,double v){
    if(l==r)
        return Tree[rt].mx>v;
    int mid=(l+r)>>1;
    if(Tree[rt*2].mx<=v) return calc(rt*2+1,mid+1,r,v);
    else return Tree[rt].ans-Tree[rt*2].ans+calc(rt*2,l,mid,v);
}

void modify(int rt,int l,int r,int x,double y){
    if(l==r){
        Tree[rt].ans=1;
        Tree[rt].mx=y;
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid)
        modify(rt*2,l,mid,x,y);
    else
        modify(rt*2+1,mid+1,r,x,y);
    Tree[rt].mx=max(Tree[rt*2].mx,Tree[rt*2+1].mx);
    Tree[rt].ans=Tree[rt*2].ans+calc(rt*2+1,mid+1,r,Tree[rt*2].mx);
}

int main() {
    scanf("%d%d", &n,&m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &x,&y);
        modify(1,1,n,x,(double)y/x);
        printf("%d\n", Tree[1].ans);
    }
    
    system("pause");
    return 0;
}