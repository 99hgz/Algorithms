#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <assert.h>
using namespace std;
typedef long long ll;

int fail[2000010],ch[2000010][26],mxsonid[2000010],sz[2000010],deep[2000010],top[2000010],in[2000010],out[2000010],ts;
int Head[2000010],Next[2000010],To[2000010],_cnt;
int base[2000010],n,pos[2000010],cnt,tot,p,op,x,q,st[2000010];
char s[2000010];
void addedge(int u,int v){
    _cnt++;
    Next[_cnt]=Head[u];
    Head[u]=_cnt;
    To[_cnt]=v;
}

void build(){
    queue<int>Q;
    Q.push(0);
    while(!Q.empty()){
        int u=Q.front();
        Q.pop();
        if(u!=fail[u])addedge(fail[u],u);
        for(int i=0;i<26;i++){
            if(ch[u][i]){
                Q.push(ch[u][i]);
                if(u)
                    fail[ch[u][i]]=ch[fail[u]][i];
            }else
                ch[u][i]=ch[fail[u]][i];
        }
    }
}

void dfs(int u,int f){
    sz[u]++;
    int mxson=0;
    mxsonid[u]=0;
    for(int it=Head[u];it;it=Next[it]){
        int v=To[it];
        deep[v]=deep[u]+1;
        dfs(v,u);
        sz[u]+=sz[v];
        if(sz[v]>mxson)
            mxson=sz[v],mxsonid[u]=v;
    }
}

void dfsid(int u,int f,int anc){
    in[u]=++ts;
    top[u]=anc;
    if(mxsonid[u])
        dfsid(mxsonid[u],u,anc);
    for(int it=Head[u];it;it=Next[it]){
        int v=To[it];
        if(v!=mxsonid[u])
            dfsid(v,u,v);
    }
    out[u]=ts;
}

int lca(int u,int v){
    while(top[u]!=top[v]){
        if(deep[top[u]]<deep[top[v]])swap(u,v);
        u=fail[top[u]];
    }
    return deep[u]<deep[v]?u:v;
}

void add(int x,int v){
    assert(x>0);
    for(;x<=ts;x+=(x&-x))base[x]+=v;
}
ll query(int x){
    ll res=0;
    for(;x;x-=(x&-x))res+=base[x];
    return res;
}

bool cmp(int a,int b){
    return in[a]<in[b];
}

int main() {
    //freopen("D:/tmp/divljak/divljak.in.2", "r", stdin);
    //freopen("D:/tmp/divljak/3881.out", "w", stdout);
    
    scanf("%d", &n);
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);
        int len=strlen(s+1),cur=0;
        for(int j=1;j<=len;j++){
            if(!ch[cur][s[j]-'a']) ch[cur][s[j]-'a']=++tot;
            cur=ch[cur][s[j]-'a'];
        }
        pos[i]=cur;
    }
    build();
    dfs(0,0);
    dfsid(0,0,0);
    scanf("%d", &q);
    for(int i=1;i<=q;i++){
        scanf("%d", &op);
        if(op==1){
            scanf("%s", s+1);
            int len=strlen(s+1),cur=0,p=0;
            for(int j=1;j<=len;j++){
                cur=ch[cur][s[j]-'a'];
                st[++p]=cur;
            }
            sort(st+1,st+1+p);
            p=unique(st+1,st+1+p)-st-1;
            sort(st+1,st+1+p,cmp);
            for(int i=1;i<=p;i++){
                add(in[st[i]],1);
                if(i!=1)
                    add(in[lca(st[i],st[i-1])],-1);
            }
        }else{
            scanf("%d", &x);
            printf("%lld\n", query(out[pos[x]])-query(in[pos[x]]-1));
        }
    }
    //system("pause");
    return 0;
}