#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int last,tot,root,len[600010],mark[600010],cnt,Head[600010],Next[600010],To[600010],n,v[600010];
char st[600010];
int a[600010][26],fa[600010],vv[600010],sz[600010];
ll mn[600010],mx[600010],ans[600010],ans2[600010];


void init(){
    last=tot=root=1;
}

void extend(int ch,int val){
    int p=last,np=last=++tot;
    len[np]=len[p]+1;
    mark[np]=val;
    for(;p&&!a[p][ch];p=fa[p])a[p][ch]=np;
    if (!p)
        fa[np]=root;
    else{
        int q=a[p][ch];
        if (len[q]==len[p]+1)
            fa[np]=q;
        else{
            int nq=++tot;
            len[nq]=len[p]+1;
            memcpy(a[nq],a[q],sizeof a[q]);
            fa[nq]=fa[q];
            fa[np]=fa[q]=nq;
            for(;p&&a[p][ch]==q;p=fa[p]) a[p][ch]=nq;
        }
    }
}

void addedge(int u,int v){
    cnt++;
    Next[cnt]=Head[u];
    Head[u]=cnt;
    To[cnt]=v;
}

void dfs(int rt){
    if (mark[rt]){
        sz[rt]=1;
        mn[rt]=mx[rt]=vv[mark[rt]];
    }else
        mn[rt]=0x3f3f3f3f3f3f3f3f,mx[rt]=-0x3f3f3f3f3f3f3f3f;
    for(int it=Head[rt];it;it=Next[it]){
        int t=To[it];
        dfs(t);
        ans[len[rt]]+=(ll)sz[rt]*sz[t];
        if (sz[rt]&&sz[t]){
            //printf("check %lld %lld %lld\n",mn[rt],mn[t],len[rt] );
            ans2[len[rt]]=max(ans2[len[rt]],mn[rt]*mn[t]);
            ans2[len[rt]]=max(ans2[len[rt]],mx[rt]*mx[t]);
        }
        sz[rt]+=sz[t];
        mn[rt]=min(mn[rt],mn[t]);
        mx[rt]=max(mx[rt],mx[t]);
    }
}



int main() {
    scanf("%d", &n);
    scanf("%s", st+1);
    init();
    for (int i = 1; i <= n; i++)
        scanf("%d", &vv[i]);
    for (int i = n; i >=1; i--){
        extend(st[i]-'a',i);
        ans2[i-1]=-0x3f3f3f3f3f3f3f3f;
    }
    for (int i = 2; i <= tot; i++)
        addedge(fa[i],i);
    dfs(root);
    ll suf=0,mx=-0x3f3f3f3f3f3f3f3f;
    for (int i=n-1;i>=0;i--)
        suf+=ans[i],ans[i]=suf,mx=max(mx,ans2[i]),ans2[i]=mx;
    for (int i = 0; i < n; i++)
        printf("%lld %lld\n", ans[i],ans[i]?ans2[i]:0);
    system("pause");
    return 0;
}