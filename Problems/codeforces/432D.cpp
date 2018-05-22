#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

int fail[200010];
char s1[200010];
vector<int>ans;
int p[200010],len[200010],fa[200010],rk[200010],sz[200010],last,tot,root;
int a[200010][26],a2[200010];

void init(){
    last=tot=root=1;
    int len=strlen(s1+1);
    fail[1]=0;
    for(int i=2;i<=len;i++){
        int j=fail[i-1];
        while(j&&s1[j+1]!=s1[i])j=fail[j];
        if(s1[j+1]==s1[i])fail[i]=j+1;
        else fail[i]=0;
    }
}

void extend(int ch){
    int p=last;
    int np=last=++tot;
    len[np]=len[p]+1;
    sz[np]=1;
    while(p&&a[p][ch]==0)a[p][ch]=np,p=fa[p];
    if(!p)
        fa[np]=root;
    else{
        int q=a[p][ch];
        if(len[q]==len[p]+1)
            fa[np]=q;
        else{
            int nq=++tot;
            fa[nq]=fa[q];
            fa[q]=fa[np]=nq;
            len[nq]=len[p]+1;
            memcpy(a[nq],a[q],sizeof a[q]);
            while(p&&a[p][ch]==q)a[p][ch]=nq,p=fa[p];
        }
    }
}

int main() {
    scanf("%s", s1+1);
    init();
    int stlen=strlen(s1+1);
    for(int i=1;i<=stlen;i++)
        extend(s1[i]-'A');
    
    int cur=stlen;
    while(cur){
        ans.push_back(cur);
        cur=fail[cur];
    }
    sort(ans.begin(),ans.end());
    for(int i=1;i<=tot;i++)
        p[len[i]]++;
    for(int i=1;i<=stlen;i++)
        p[i]+=p[i-1];
    for(int i=1;i<=tot;i++)
        rk[p[len[i]]--]=i;
    for(int i=tot;i>=1;i--)
        sz[fa[rk[i]]] += sz[rk[i]];
    
    cur=root;
    for(int i=1;i<=stlen;i++){
        cur=a[cur][s1[i]-'A'];
        a2[i]=sz[cur];
    }
    printf("%d\n", ans.size());
    for(int v:ans)
        printf("%d %d\n",v,a2[v]);
    
    //system("pause");
    return 0;
}