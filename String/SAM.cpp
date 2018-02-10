#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MAXN=1000010;
int size[MAXN],c[MAXN],pos[MAXN],sum[MAXN];
char st[MAXN];
int stlen,T,K;

    int p,q,np,nq;
    int cnt=1,last=1;
    int a[MAXN][26],len[MAXN],fa[MAXN];
    void insert(int ch){
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

void work(){
    for (int i = 1; i <= cnt; i++) c[len[i]]++;
    for(int i=1;i<=stlen;i++)c[i]+=c[i-1];
    for(int i=1;i<=cnt;i++)pos[c[len[i]]--]=i;
    if (T)
        for(int i=cnt;i>=2;i--)
            size[fa[pos[i]]]+=size[pos[i]];
        else
        for (int i = 1; i <= cnt; i++) 
            size[i]=1;
        
    for(int i=cnt;i>=1;i--){
        sum[pos[i]]=size[pos[i]];
        for(int j=0;j<26;j++)
            if (a[pos[i]][j])
                sum[pos[i]]+=sum[a[pos[i]][j]];
    }
}

int main() {
    freopen("C:\\Users\\22528\\Downloads\\string3.in", "r", stdin);
    freopen("C:\\Users\\22528\\Downloads\\string3.ans", "w", stdout);
    
    scanf("%s", st+1);
    stlen=strlen(st+1);
    for(int i=1;i<=stlen;i++)
        insert(st[i]-'a');
    scanf("%d%d", &T,&K);
    work();
    for(int p=1;K;){
        for(int i=0;i<26;i++)
            if (a[p][i]){
                if (sum[a[p][i]]>=K){
                    printf("%c",'a'+i );
                    K-=size[a[p][i]];
                    p=a[p][i];
                    break;
                }else
                    K-=sum[a[p][i]];
            }
    }
    //system("pause");
    return 0;
}