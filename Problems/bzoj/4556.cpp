#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <assert.h>
#include <algorithm>
#include <set>
using namespace std;
typedef long long ll;
typedef pair<int,int> pr;
char st[1000010],newst[1000010];
int n,stlen[1000010],ed[1000010],pos[1000010*2];
int root[1500100],stp2samp[1000010];
//multiset<int>S[10010];
pr max(pr a,pr b){
    if(a.first==b.first)
        return make_pair(a.first,min(b.second,a.second));
    if(a.first>b.first)
        return a;
    else
        return b;
}

namespace SGT{
    struct TREE{
        int lson,rson;
        int val;
    }Tree[1000100*25];
    int cnt;
    void insert(int &rt,int l,int r,int v){
        if(!rt)
            rt=++cnt;
        Tree[rt].val++;
        if(l==r)
            return ;
        int mid=(l+r)>>1;
        if(v<=mid)
            insert(Tree[rt].lson,l,mid,v);
        else
            insert(Tree[rt].rson,mid+1,r,v);
    }
    int merge(int rt1,int rt2,int l,int r){
        int newrt=++cnt;
        if(!rt1||!rt2){
            Tree[newrt]=Tree[rt1+rt2];
            return newrt;
        }
        Tree[newrt]=Tree[rt1];
        int mid=(l+r)>>1;
        if(l==r){
            Tree[newrt].val=Tree[rt1].val+Tree[rt2].val;
            return newrt;
        }
        Tree[newrt].lson=merge(Tree[rt1].lson,Tree[rt2].lson,l,mid);
        Tree[newrt].rson=merge(Tree[rt1].rson,Tree[rt2].rson,mid+1,r);
        Tree[newrt].val=Tree[Tree[newrt].lson].val+Tree[Tree[newrt].rson].val;
        return newrt;
    }
    int query(int rt,int l,int r,int L,int R){
        if(L<=l&&r<=R)
            return Tree[rt].val;
        if(!rt||l>R||r<L)
            return 0;
        int mid=(l+r)>>1;
        int res=query(Tree[rt].lson,l,mid,L,R)+query(Tree[rt].rson,mid+1,r,L,R);
        return res;
    }
}

namespace SAM{
    int len[1500100],fa[1500100],_root,last,cnt,a[1500100][27];
    int c[1500100],pos[1500100],_st[1500100][23];
    void init(){
        last=_root=++cnt;
    }
    int extend(int ch,int pp){
        int p=last;
        int np=last=++cnt;
        if(pp) {SGT::insert(root[np],1,n,pp);//printf("inserted:%d %d\n", np,pp);//S[np].insert(pp);
        }
        len[np]=len[p]+1;
        for(;!a[p][ch];p=fa[p])a[p][ch]=np;
        if(!p)
            fa[np]=_root;
        else{
            int q=a[p][ch];
            if(len[q]==len[p]+1)
                fa[np]=q;
            else{
                int nq=++cnt;
                len[nq]=len[p]+1;
                fa[nq]=fa[q];
                fa[q]=fa[np]=nq;
                memcpy(a[nq],a[q],sizeof a[nq]);
                for(;a[p][ch]==q;p=fa[p])a[p][ch]=nq;
            }
        }
        return np;
    }
    void build(){
        for ( int i = 1; i <= cnt; i++ )
            c[len[i]]++;
        for ( int i = 1; i <= cnt; i++ )
            c[i] += c[i - 1];
        for ( int i = 1; i <= cnt; i++ )
            pos[c[len[i]]--] = i;
        for ( int i = cnt; i >= 1; i-- ){
            int p=pos[i];
            //printf("merge:%d %d\n", fa[p],p);
            root[fa[p]]=SGT::merge(root[fa[p]],root[p],1,n);
            //for(int v:S[p])
            //    S[fa[p]].insert(v);
        }
    }
    void init_st(){
        for(int i=1;i<=cnt;i++)
            _st[i][0]=fa[i];
        for(int i=1;i<=22;i++)
            for(int j=1;j<=cnt;j++)
                _st[j][i]=_st[_st[j][i-1]][i-1];
    }
    int query(int p,int stlen){
        for(int i=22;i>=0;i--){
            if(_st[p][i]==0) continue;
            if(len[_st[p][i]]>=stlen)
                p=_st[p][i];
        }
        return p;
    }
    int work(int l,int r){
        int cur=_root;
        for(int i=l;i<=r;i++)
            cur=a[cur][st[i]-'a'];
        return cur;
    }
}

int l,r,pl,pr1,q;

int main() {

    SAM::init();
    scanf("%d%d", &n,&q);
    scanf("%s", st+1);
    int l=strlen(st+1);
    for (int i = 1; i <= l; i++)
        SAM::extend(st[i]-'a',i);
    SAM::build();
    SAM::init_st();
    
    int cur=SAM::_root;
    for(int i=1;i<=l;i++){
        cur=SAM::a[cur][st[i]-'a'];
        stp2samp[i]=cur;
    }
    for (int i = 1; i <= q; i++){
        scanf("%d%d%d%d", &l,&r,&pl,&pr1);
        int L=1,R=pr1-pl+1,ans=0;
        while(L<=R){
            int mid=(L+R)>>1;
            int p=SAM::query(stp2samp[pl+mid-1],mid);
            int tmp=SGT::query(root[p],1,n,l+mid-1,r);
            if(tmp)
                ans=mid,L=mid+1;
            else
                R=mid-1;
        }
        printf("%d\n", ans);
    }
    //system("pause");
    return 0;
}