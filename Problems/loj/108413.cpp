#include<stdio.h>
#include<set>
#include<algorithm>
#include<assert.h>
#include <ctime>
#define mp make_pair
#define fr first
#define se second
using namespace std;
typedef pair<int,int>pr;
pr rg[300010];
multiset<int>Tree[300010*4];
set<pr>ex[300010];
int n,k,qnum;
struct Shop{
    int x,t,a,b,id;
}s[300010];
struct PR{
    int id,val;
}ts[300010],te[300010];
struct Query{
    int l,y,id;
}q[300010];
multiset<int>::iterator rtit[300010][50];
int rts[300010][50],rtn[300010],_id;
int heads,heade;
int ans[300010];
bool cmpq(Query a,Query b){
    return a.y<b.y;
}
bool cmpt(PR a,PR b){
    return a.val<b.val;
}
 
void _insert(int rt,int l,int r,int L,int R,int val){
    if(l>R||r<L) return;
    if(L<=l&&r<=R){
        rtn[_id]++;
        rts[_id][rtn[_id]]=rt;
        rtit[_id][rtn[_id]]=Tree[rt].insert(val);
        return;
    }
    int mid=(l+r)>>1;
    _insert(rt*2,l,mid,L,R,val);
    _insert(rt*2+1,mid+1,r,L,R,val);
}
void _modify(int rt,int l,int r,int L,int R,int val){
    if(l>R||r<L) return;
    if(L<=l&&r<=R){
        Tree[rt].erase(Tree[rt].find(val));
        return;
    }
    int mid=(l+r)>>1;
    _modify(rt*2,l,mid,L,R,val);
    _modify(rt*2+1,mid+1,r,L,R,val);
}
int _query(int rt,int l,int r,int x,int v){
     
    if(l==r){
        if(Tree[rt].size()==0) return -2;
        auto it=Tree[rt].end();
        it--;
        return max(abs((*(Tree[rt].begin()))-v),abs((*it)-v));
    }
    int mid=(l+r)>>1;
    int res;
    if(Tree[rt].size()==0)
        res=-2;
    else{
        auto it=Tree[rt].end();
        it--;
        res=max(abs((*(Tree[rt].begin()))-v),abs((*it)-v));
    }
    if(x<=mid)
        return max(_query(rt*2,l,mid,x,v),res);
    else
        return max(_query(rt*2+1,mid+1,r,x,v),res);
}
 
 
namespace Hash{
    int cnt;
    int a[300010];
    void insert(int x){
        a[++cnt]=x;
    }
    void init(){
        sort(a+1,a+1+cnt);
        //cnt=100000;
        cnt=unique(a+1,a+1+cnt)-a-1;
    }
    int l(int x){
        int tmp=lower_bound(a+1,a+1+cnt,x)-a;
        return tmp;
    }
    int r(int x){
        int tmp=lower_bound(a+1,a+1+cnt,x)-a;
        if(tmp>cnt||a[tmp]>x)tmp--;
        return tmp;
    }
}
 
void insert(int val,int id){
    rtn[id]=0;
    _id=id;
    _insert(1,1,Hash::cnt,Hash::l(rg[id].fr),Hash::r(rg[id].se),val);
}
void del(pr p){
    int id=p.se;
    for(int i=1;i<=rtn[id];i++)
        Tree[rts[id][i]].erase(rtit[id][i]);
}
int query(int val){
    return _query(1,1,Hash::cnt,Hash::l(val),val);
}
int has;
 
int main(){
    freopen("d:/tmp/104", "r", stdin);
    freopen("d:/tmp/104t", "w", stdout);
    
    double dur;
    clock_t start,end;
    start = clock();
    scanf("%d%d%d",&n,&k,&qnum);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d%d",&s[i].x,&s[i].t,&s[i].a,&s[i].b);
        s[i].id=i;
        ts[i].id=i;
        ts[i].val=s[i].a;
        te[i].id=i;
        te[i].val=s[i].b;
    }
    for(int i=1;i<=qnum;i++){
        scanf("%d%d",&q[i].l,&q[i].y);
        Hash::insert(q[i].l);
        q[i].id=i;
    }
    Hash::init();
    sort(q+1,q+1+qnum,cmpq);
    sort(ts+1,ts+1+n,cmpt);
    sort(te+1,te+1+n,cmpt);
    heads=1;
    heade=1;
    for(int i=1;i<=qnum;i++){
        while(heads<=n&&ts[heads].val<=q[i].y){
            int id=ts[heads].id,lx=s[id].t;
            if(ex[lx].size()==0){
                has++;
                rg[id]=mp(1,1e8);
                insert(s[id].x,id);
                ex[lx].insert(mp(s[id].x,id));
            }else{
                auto it=ex[lx].insert(mp(s[id].x,id));
                auto suc=it.first,pre=it.first;
                suc++;
                if(suc==ex[lx].end()){
                    auto pre=it.first;
                    pre--;
                    del(*pre);
                     
                    int pid=(*pre).se;
                    rg[pid].se=(s[id].x+s[pid].x)/2;
                    rg[id].fr=(s[id].x+s[pid].x)/2+1;
                    rg[id].se=1e8;
                    insert(s[pid].x,pid);
                    insert(s[id].x,id);
                }else
                if(pre==ex[lx].begin()){
                    del(*suc);
                    int pid=(*suc).se;
                    rg[pid].fr=(s[id].x+s[pid].x)/2+1;
                    rg[id]=mp(1,(s[id].x+s[pid].x)/2);
                    insert(s[pid].x,pid),insert(s[id].x,id);
                }else{
                    pre--;
                    del(*pre);
                    del(*suc);
                    int sid=(*suc).se,pid=(*pre).se;
                    rg[id].se=(s[id].x+s[sid].x)/2;
                    rg[sid].fr=rg[id].se+1;
                    rg[pid].se=(s[id].x+s[pid].x)/2;
                    rg[id].fr=rg[pid].se+1;
                    insert(s[id].x,id),insert(s[pid].x,pid),insert(s[sid].x,sid);
                }
            }
            heads++;
        }
        while(heade<=n&&te[heade].val<q[i].y){
            int id=te[heade].id,lx=s[id].t;
            if(ex[lx].size()==1){
                has--;
                del(*ex[lx].begin());
                ex[lx].erase(*ex[lx].begin());
            }else{
                auto it=ex[lx].find(mp(s[id].x,id));
                auto suc=it,pre=it;
                suc++;
         
                if(suc==ex[lx].end()){
                    auto pre=it;
                    pre--;
                    del(*pre);
                     
                    int pid=(*pre).se;
                    rg[pid].se=1e8;
                    insert(s[pid].x,pid);
                    del(*it);
                }else
                if(pre==ex[lx].begin()){
                    del(*suc);
                    int pid=(*suc).se;
                    rg[pid].fr=1;
                    insert(s[pid].x,pid);
                    del(*it);
                }else{
                    pre--;
                    del(*pre),del(*suc);
                    int sid=(*suc).se,pid=(*pre).se;
                    rg[pid].se=(s[sid].x+s[pid].x)/2;
                    rg[sid].fr=rg[pid].se+1;
                    insert(s[sid].x,sid),insert(s[pid].x,pid),
                    del(*it);
                }
                ex[lx].erase(it);
            }
            rg[id]=mp(0,0);
            heade++;
        }
        ans[q[i].id]=(has==k)?query(q[i].l):-1;
    }
    for(int i=1;i<=qnum;i++)
        printf("%d\n",ans[i]);
    end = clock();
    dur = (double)(end - start);
    printf("Use Time:%f\n",(dur/CLOCKS_PER_SEC));
}