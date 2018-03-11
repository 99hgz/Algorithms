#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int pre[20],q[100100],base[20],mp[110][110],nmp[110][110],tot,n,m,f[110][200010],i;
char st[110];
void dfs(int x,int l,int b,int sta){
    if (x==m+1){
        if (l==0)
            q[++tot]=b;
        return;
    }
    int t=sta%base[x]/base[x-1];

    if (mp[i][x]){
        if (l!=0||t!=0) return;
        dfs(x+1,0,b,sta);
        return;
    }
    if (l==0){
        if (t==0){
            dfs(x+1,2,b,sta);
            dfs(x+1,0,b+2*base[x-1],sta);
            dfs(x+1,1,b+1*base[x-1],sta);
        }else if (t==1){
            dfs(x+1,0,b,sta);
            dfs(x+1,0,b+1*base[x-1],sta);
        }else if (t==2){
            dfs(x+1,0,b+2*base[x-1],sta);
            dfs(x+1,1,b,sta);
        }
    }else if (l==1){
        if (t==0){
            dfs(x+1,1,b,sta);
            dfs(x+1,0,b,sta);
        }
    }else if (l==2){
        if (t==0){
            dfs(x+1,2,b,sta);
            dfs(x+1,0,b+1*base[x-1],sta);
        }else if (t==1){
            return;
        }else if (t==2){
            dfs(x+1,0,b,sta);
        }
    }
}


int main() {
    scanf("%d%d", &n,&m);
    for (int i = 1; i <= n; i++){
        scanf("%s", st+1);
        for (int j = 1; j <= m; j++)
            mp[i][j]=(st[j]=='*');
    }
    if (m>=10){
        swap(n,m);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                nmp[i][j]=mp[j][i];
        memcpy(mp,nmp,sizeof mp);
    }
    f[0][0]=1;
    
    base[0]=1;
    for (int i = 1; i <= 11; i++)
        base[i]=base[i-1]*3;
    
    for (i = 1; i <= n; i++){
        for (int sta = 0; sta < base[m]; sta++){
            tot=0;
            dfs(1,0,0,sta);
            for (int j = 1; j <= tot; j++)
                f[i][q[j]]=(f[i][q[j]]+f[i-1][sta])%20110520;
        }
    }
    printf("%d\n", f[n][0]);
    system("pause");
    return 0;
}