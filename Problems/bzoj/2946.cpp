#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n,last,root,cnt,len[100010],a[100010][26],fa[100010],size[100010],mn[100010],mx[100010],c[100010],pos[100100],ans;
char st[10010];

void init(){
    last=root=++cnt;
}

void extend(int ch){
    int p=last,np=last=++cnt;
    len[np]=len[p]+1;
    size[np]=1;
    while(p&&!a[p][ch]){
        a[p][ch]=np;
        p=fa[p];
    }
    if (!p) fa[np]=root;else{
        int q=a[p][ch];
        if (len[q]==len[p]+1)
            fa[np]=q;
        else{
            int nq=++cnt;
            len[nq]=len[p]+1;
            memcpy(a[nq],a[q],sizeof a[q]);
            fa[nq]=fa[q];
            fa[q]=fa[np]=nq;
            while(p&&a[p][ch]==q) a[p][ch]=nq,p=fa[p];
        }
    }
}

int main() {
    init();
    scanf("%d", &n);
    memset(mn,0x3f3f3f3f,sizeof mn);
    for (int i = 1; i <= n; i++) {
        scanf("%s", st+1);
        int slen=strlen(st+1);
        if (i==1){
            for(int j=1;j<=slen;j++)
                extend(st[j]-'a');
            for(int i=1;i<=cnt;i++) c[len[i]]++;
            for(int i=1;i<=2010;i++)c[i]+=c[i-1];
            for(int i=1;i<=cnt;i++)pos[c[len[i]]--]=i;
        }
        else{
            int now=root,tmp=0;
            memset(mx,0,sizeof mx);
            for(int j=1;j<=slen;j++){
                int ch=st[j]-'a';
                if (a[now][ch])
                    now=a[now][ch],tmp++;
                else{
                    while(now&&a[now][ch]==0) now=fa[now];
                    if (!now)
                        now=root,tmp=0;
                    else
                        tmp=len[now]+1,now=a[now][ch];
                }
                mx[now]=max(mx[now],tmp);
            }
            for(int i=cnt;i>=1;i--){
                mn[pos[i]]=min(mn[pos[i]],mx[pos[i]]);
                if (mn[pos[i]]&&fa[pos[i]])mx[fa[pos[i]]]=len[fa[pos[i]]];
            }
        }
    }
    if (n==1) ans=strlen(st+1);
    else
    for(int i=2;i<=cnt;i++)
        ans=max(ans,mn[i]);
    printf("%d\n", ans);
    system("pause");
    return 0;
}