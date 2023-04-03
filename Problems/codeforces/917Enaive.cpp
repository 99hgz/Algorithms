#pragma GCC optimize (2)
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <assert.h>
#define fi first
#define se second
using namespace std;
typedef pair<int,int> pr;
vector<int>vq[300010];
struct Triple{
    int a,b,c;
};
struct QUERY{
    int u,v,z;
}qs[300010];
int n,m,q,u,v;
char ech[10],mst[300010];
int ans[300010];
int offline[300010][2],bg[300010],ed[300010],Slen,_ans[300010];
char S[300010];
vector<pr>ps[300010];
struct LinkedList{
    int tot,Head[300010],Next[300010];
    pr Val[300010];
    void add(int u,pr v){
        tot++;
        Next[tot]=Head[u];
        Head[u]=tot;
        Val[tot]=v;
    }
}ll;
struct Two{
    int fi,se;
};
bool operator <(Two const &a,Two const &b){
    if(a.fi==b.fi)return a.se<b.se;
    return a.fi>b.fi; 
}

priority_queue<Two>MatQ;
struct MATQ{
    int id,x,y;
};
vector<MATQ>Matq[100010];
struct MAT{
    int x1,x2,y1,y2;
}Mat[300010];
bool cmpforMat(MAT a,MAT b){
    if(a.x1==b.x1)return a.y1<b.y1;
    return a.x1<b.x1;
}
bool cmpforMatq(MATQ a,MATQ b){
    if(a.x==b.x) return a.y<b.y;
    return a.x<b.x;
}
struct Four{
    int a,b,c,d;
};

struct ST{
    int id;
    int a[300010][26],ts;
    Triple req[300010][26];
    void addedge(int u,int v,Triple r){
        int ch=0;
        if (id)
            ch=S[bg[r.a]+r.b-1]-'a';
        else
            ch=S[bg[r.a]+r.c-1]-'a';
        //printf("addedge:%d %d %d %d %d\n",u,v,r.a,r.b,r.c);
        a[u][ch]=v;
        req[u][ch]=r;
    }
    Four mt(Four sta,int ch){
        if(sta.d==0)
            return sta;
        if(sta.c==0){
            if(a[sta.a][ch]==0)
                return (Four){sta.a,0,0,0};
            else{
                if(req[sta.a][ch].c==req[sta.a][ch].b)
                    return(Four){a[sta.a][ch],0,0,1};
                else
                    return(Four){sta.a,ch,1,1};
            }
        }else{
            Triple rq=req[sta.a][sta.b];
            int pos;
            if(id)
                pos=bg[rq.a]+rq.b-1+sta.c;
            else
                pos=bg[rq.a]+rq.c-1-sta.c;
            if((S[pos]-'a')==ch){
                if(pos==bg[rq.a]+(id?rq.c:rq.b)-1)
                    return (Four){a[sta.a][sta.b],0,0,1};
                else
                    return (Four){sta.a,sta.b,sta.c+1,1};
            }else
                return(Four){sta.a,sta.b,sta.c,0};
        }
    }
    int in[300010],out[300010];
    void dfs(int x){
        in[x]=++ts;
        for(int i=0;i<26;i++)
            if(a[x][i])
                dfs(a[x][i]);
        out[x]=ts;
    }
}St[2];

struct SAM{
    int fa[300010], a[300010][26], cnt, len[300010], root, last, id;
    int sfx[300010],s2t[300010];

    void init(){
        root=++cnt;
    }
    void extend(int x,int tid,int ps)
    {
        int now=a[last][x],pre=last;
        if (now)
        {
            if (len[now]==len[pre]+1) last=now;  
            else
            {
                int nows=++cnt;
                sfx[nows]=ps;
                s2t[nows]=tid;
                len[nows]=len[pre]+1;
                memcpy(a[nows],a[now],sizeof(a[now]));
                fa[nows]=fa[now]; fa[now]=nows;
                for (;pre&&a[pre][x]==now;pre=fa[pre]) a[pre][x]=nows;
                last=nows;
            }
        }
        else
        {
            now=++cnt;
            len[now]=len[pre]+1; last=now;
            s2t[now]=tid;
            sfx[now]=ps;
            for (;pre&&!a[pre][x];pre=fa[pre]) a[pre][x]=now;
            if (!pre) fa[now]=root;
            else
            {
                int q=a[pre][x];
                if (len[q]==len[pre]+1) fa[now]=q;
                else
                {
                    int nows=++cnt;
                    len[nows]=len[pre]+1;
                    memcpy(a[nows],a[q],sizeof(a[q]));
                    s2t[nows]=s2t[q];
                    sfx[nows]=sfx[q];
                    fa[nows]=fa[q]; fa[q]=fa[now]=nows;
                    for (;pre&&a[pre][x]==q;pre=fa[pre]) a[pre][x]=nows;
                }
            }
        }
    }
    void buildst(){
        for(int i=2;i<=cnt;i++){
            if(id)
                St[id].addedge(fa[i],i,(Triple){s2t[i],sfx[i]+len[fa[i]],sfx[i]+len[i]-1});
            else
                St[id].addedge(fa[i],i,(Triple){s2t[i],sfx[i]-len[i]+1,sfx[i]-len[fa[i]]});
        }
    }
}Sam[2];

struct TRIE{
    int id,tot,ch[300010][26],pos[300010];
    int fail[300010],ts,in[300010],out[300010],bit[300010],t2s[300010];
    int Head[300010],Next[300010],To[300010],cnt;
    void addedge(int u,int v){
        cnt++;
        Next[cnt]=Head[u];
        Head[u]=cnt;
        To[cnt]=v;
    }

    void buildac(){
        queue<int>Q;
        Q.push(0);
        while(!Q.empty()){
            int u=Q.front();
            if(u!=fail[u])
                addedge(fail[u],u);
            Q.pop();
            for(int i=0;i<26;i++){
                int v=ch[u][i];
                if(v){
                    Q.push(v);
                    if(u)
                        fail[v]=ch[fail[u]][i];
                }else
                    ch[u][i]=ch[fail[u]][i];
            }
        }
    }
    void dfs(int u){
        in[u]=++ts;
        for(int it=Head[u];it;it=Next[it])
            dfs(To[it]);
        out[u]=ts;
    }
    void add(int x,int v){
        for(;x<=ts;x+=(x&-x))
            bit[x]+=v;
    }
    int sum(int x){
        int res=0;
        for(;x;x-=(x&-x))
            res+=bit[x];
        return res;
    }
}Trie[2];

namespace Tree{
    int cnt,Head[300010],Next[300010],To[300010],Val[300010],fa[300010];
    bool vis[300010];
    int ncnt,nHead[400010],nNext[400010],nTo[400010];
    void addnewedge(int u,int v){
        ncnt++;
        nNext[ncnt]=nHead[u];
        nTo[ncnt]=v;
        nHead[u]=ncnt;
    }
    void addedge(int u,int v,int val){
        cnt++;
        Next[cnt]=Head[u];
        To[cnt]=v;
        Head[u]=cnt;
        Val[cnt]=val;
    }
    int _rt,mn;

    int getroot(int treesize, int x, int fa)
    {
        int sz=1,mx=0;
        for (int i = Head[x]; i; i = Next[i])
        {
            int P = To[i];
            if ((P != fa) && (!vis[P]))
            {
                int tmp=getroot(treesize, P, x);
                sz+=tmp;
                mx=max(mx,tmp);
            }
        }
        mx=max(mx,treesize-sz);
        if (mx<mn) mn=mx,_rt=x;
        return sz;
    }
    int getroot(int u,int sz){
        _rt=0;
        mn=0x3f3f3f3f;
        getroot(sz,u,u);
        return _rt;
    }

    int getsize(int x, int fa)
    {
        int res = 1;
        for (int i = Head[x]; i; i = Next[i])
        {
            int P = To[i];
            if ((P != fa) && (!vis[P]))
                res += getsize(P, x);
        }
        return res;
    }

    void df(int u){
        vis[u]=true;
        for(int it=Head[u];it;it=Next[it]){
            int v=To[it];
            if(!vis[v]){
                int tmp=getroot(v,getsize(v,u));
                addnewedge(u,tmp);
                fa[tmp]=u;
                df(tmp);
            }
        }
    }
    int lca(int u,int v){
        for(int x=u;x;x=fa[x])
            vis[x]=true;
        int res=0;
        for(int x=v;x;x=fa[x])
            if(vis[x]) {res=x;break;}
        for(int x=u;x;x=fa[x])
            vis[x]=false;
        return res;
    }

    void clearson(int u,int f){
        ll.Head[u]=0;
        for(int it=Head[u];it;it=Next[it]){
            int v=To[it];
            if(!vis[v]&&v!=f)
                clearson(v,u);
        }
    }

    void checkson(int u,int f,int p0,int p1,Four s0,Four s1){
        Trie[0].add(Trie[0].in[p0],1);
        Trie[1].add(Trie[1].in[p1],1);
        for(int it=ll.Head[u];it;it=ll.Next[it]){
            pr tmp=ll.Val[it];
            ans[tmp.se]+=Trie[tmp.fi].sum(Trie[tmp.fi].out[Trie[tmp.fi].pos[qs[tmp.se].z]])-Trie[tmp.fi].sum(Trie[tmp.fi].in[Trie[tmp.fi].pos[qs[tmp.se].z]]-1);
            offline[tmp.se][tmp.fi^1]=tmp.fi?s0.a:s1.a;
        }
        for(int it=Head[u];it;it=Next[it]){
            int v=To[it];
            if(v!=f&&!vis[v])
                checkson(v,u,Trie[0].ch[p0][Val[it]],Trie[1].ch[p1][Val[it]],St[0].mt(s0,Val[it]),St[1].mt(s1,Val[it]));
        }
        Trie[0].add(Trie[0].in[p0],-1);
        Trie[1].add(Trie[1].in[p1],-1);
    }

    void work(int u){
        vis[u]=true;

        ll.tot=0;
        clearson(u,u);
        for(int x:vq[u])
            ll.add(qs[x].u,make_pair(1,x)),ll.add(qs[x].v,make_pair(0,x));
        
        checkson(u,u,0,0,(Four){1,0,0,1},(Four){1,0,0,1});
        for(int it=nHead[u];it;it=nNext[it]){
            int v=nTo[it];
            if(!vis[v])
                work(v);
        }
    }
}

struct _BIT{
    int base[300010];
    void add(int x,int delta){
        for(;x<=300010;x+=(x&-x))base[x]+=delta;
    }
    int count(int x){
        int res=0;
        for(;x;x-=(x&-x))res+=base[x];
        return res;
    }
}BIT;

int main() {
    //freopen("data.in", "r", stdin);
    //freopen("2.out", "w", stdout);
    
    scanf("%d%d%d", &n,&m,&q);
    for(int i=1;i<n;i++){
        scanf("%d%d%s",&u,&v,ech);
        Tree::addedge(u,v,ech[0]-'a');
        Tree::addedge(v,u,ech[0]-'a');
    }

    Sam[1].id=St[1].id=1;
    Sam[0].init(),Sam[1].init();

    for(int i=1;i<=m;i++){
        scanf("%s", mst);
        int len=strlen(mst);
        int cur=0;
        Sam[0].last=1;
        for(int j=0;j<len;j++){
            if(!Trie[0].ch[cur][mst[j]-'a'])
                Trie[0].ch[cur][mst[j]-'a']=++Trie[0].tot;
            cur=Trie[0].ch[cur][mst[j]-'a'];
            Sam[0].extend(mst[j]-'a',i,j+1);
        }
        Trie[0].pos[i]=cur;
        cur=0;
        Sam[1].last=1;
        for(int j=len-1;j>=0;j--){
            if(!Trie[1].ch[cur][mst[j]-'a'])
                Trie[1].ch[cur][mst[j]-'a']=++Trie[1].tot;
            cur=Trie[1].ch[cur][mst[j]-'a'];
            Sam[1].extend(mst[j]-'a',i,j+1);
        }
        Trie[1].pos[i]=cur;

        bg[i]=Slen+1;
        for(int j=0;j<len;j++)
            S[++Slen]=mst[j];
        ed[i]=Slen;
    }
    for(int x=0;x<=1;x++)
        Trie[x].id=x,Trie[x].buildac(),Trie[x].dfs(0),Sam[x].buildst(),St[x].dfs(1);

    for(int i=1;i<=m;i++){
        int cur0=Sam[0].root;
        int len=ed[i]-bg[i]+1;
        for(int j=bg[i];j<=ed[i];j++){
            cur0=Sam[0].a[cur0][S[j]-'a'];
            cur0=cur0;
            _ans[j-bg[i]+1]=cur0;
        }
        int cur1=Sam[1].root;
        for(int j=ed[i];j>=bg[i];j--){
            cur1=Sam[1].a[cur1][S[j]-'a'];
            cur1=cur1;
            if(j!=bg[i])
                ps[i].push_back(make_pair(_ans[len-(ed[i]-j+1)],cur1));
        }
    }
    /*for(int i=0;i<=1;i++){
        for(int j=2;j<=Sam[i].cnt;j++)
            printf("%d %d\n", Sam[i].len[j],Sam[i].len[Sam[i].fa[j]]);
    }*/
    
    Tree::df(1);
    memset(Tree::vis,0,sizeof Tree::vis);
    for(int i=1;i<=q;i++){
        scanf("%d%d%d",&qs[i].u,&qs[i].v,&qs[i].z);
        int l=Tree::lca(qs[i].u,qs[i].v);
        vq[l].push_back(i);
    }
    Tree::work(1);

    for(int i=1;i<=q;i++)
        if(offline[i][0]&&offline[i][1])
            Matq[qs[i].z].push_back((MATQ){i,St[0].in[offline[i][0]],St[1].in[offline[i][1]]});
    for(int i=1;i<=m;i++){
        int Matnum=0;
        for(auto p:ps[i])
            Mat[++Matnum]=(MAT){St[0].in[p.fi],St[0].out[p.fi],St[1].in[p.se],St[1].out[p.se]};
        sort(Mat+1,Mat+1+Matnum,cmpforMat);
        sort(Matq[i].begin(),Matq[i].end(),cmpforMatq);
        int head=1;
        for(auto q:Matq[i]){
            while(head<=Matnum&&Mat[head].x1<=q.x){
                BIT.add(Mat[head].y1,1);
                BIT.add(Mat[head].y2+1,-1);
                MatQ.push((Two){Mat[head].x2+1,head});
                head++;
            }
            while(!MatQ.empty()&&MatQ.top().fi<=q.x){
                Two tmp=MatQ.top();
                MatQ.pop();
                BIT.add(Mat[tmp.se].y1,-1);
                BIT.add(Mat[tmp.se].y2+1,1);
            }
            ans[q.id]+=BIT.count(q.y);
        }
        while(!MatQ.empty()){
            Two tmp=MatQ.top();
            MatQ.pop();
            BIT.add(Mat[tmp.se].y1,-1);
            BIT.add(Mat[tmp.se].y2+1,1);
        }
    }
    for(int i=1;i<=q;i++)
        printf("%d\n", ans[i]);

    //system("pause");
    return 0;
}