#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

char s[500010];
int cnt,Head[500010],Next[500010],To[500010],L[500010],R[500010],mx,fail[500010],son[500010];

void addedge(int u,int v){
    cnt++;
    To[cnt]=v;
    Next[cnt]=Head[u];
    Head[u]=cnt;
}

void dfs(int x){
    L[R[x]]=L[x];
    R[L[x]]=R[x];
    if(L[x]&&R[x])
        mx=max(mx,R[x]-L[x]);
    for(int it=Head[x];it;it=Next[it])
        dfs(To[it]);
}

int main() {
    scanf("%s", s+1);
    int len=strlen(s+1);
    for(int i=2,j=0;i<=len;i++){
        while(j&&s[j+1]!=s[i]) j=fail[j];
        if(s[j+1]==s[i])j++;
        fail[i]=j;
    }
    for(int i=1;i<=len;i++)
        addedge(fail[i],i);
    for(int i=len;i;i=fail[i])
        son[fail[i]]=i;
    for(int i=1;i<=len;i++)
        L[i]=i-1,R[i]=i+1;
    R[len]=0;
    for(int i=0;son[i];i=son[i]){
        for(int j=Head[i];j;j=Next[j])
            if(To[j]!=son[i])
                dfs(To[j]);
        if(mx<=son[i]){
            printf("%d\n",son[i]);
            break;
        }
    }
    system("pause");
    return 0;
}