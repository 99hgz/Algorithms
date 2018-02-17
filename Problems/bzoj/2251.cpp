#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MAXN=200010;
char st[MAXN];
int stlen,c[MAXN],pos[MAXN];

    int p,q,np,nq;
    int cnt=1,last=1;
    int a[MAXN][2],len[MAXN],fa[MAXN],size[MAXN];
    void extend(int ch){
        p=last,np=last=++cnt;len[np]=len[p]+1;
        size[np]=1;
        while(!a[p][ch]&&p)a[p][ch]=np,p=fa[p];
        if (!p)fa[np]=1;
        else {
            q=a[p][ch];
            if (len[q]==len[p]+1) fa[np]=q;
            else{
                nq=++cnt,len[nq]=len[p]+1;
                memcpy(a[nq],a[q],sizeof a[q]);
                fa[nq]=fa[q];
                fa[np]=fa[q]=nq;
                while(p&&a[p][ch]==q) a[p][ch]=nq,p=fa[p];
            }
        }
    }

    void dfs(int cur){
        if (cur!=1&&size[cur]>1)printf("%d\n", size[cur]);
        if (a[cur][0])dfs(a[cur][0]);
        if (a[cur][1])dfs(a[cur][1]);
    }

int main() {
    scanf("%d", &stlen);
    scanf("%s", st+1);
    for (int i = 1; i <= stlen; i++) 
        extend(st[i]-'0');
    for(int i=1;i<=cnt;i++) c[len[i]]++;
    for(int i=1;i<=stlen;i++)c[i]+=c[i-1];
    for(int i=1;i<=cnt;i++)pos[c[len[i]]--]=i;
    for (int i = cnt; i >=1; i--) {
        int cur=pos[i];
        size[fa[cur]]+=size[cur];
    }
    dfs(1);
    system("pause");
    return 0;
}