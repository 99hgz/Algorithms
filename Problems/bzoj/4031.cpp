#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

ll mod=1000000000;
ll du[110][110];
int n,m,mp[20][20],cnt,id[20][20];
char st[110];
int cx[5]={0,1,0,0,-1};
int cy[5]={0,0,-1,1,0};

ll det(int n)
{
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            du[i][j]=(du[i][j]+mod)%mod;
    int f=1;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++){
            ll A=du[i][i],B=du[j][i];
            while(B)
            {
                ll t=A/B;A%=B;swap(A,B);
                for(int k=1;k<=n;k++)
                    du[i][k]=(du[i][k]-du[j][k]*t%mod+mod)%mod;
                for(int k=1;k<=n;k++)
                    swap(du[i][k],du[j][k]);
                f=-f; 
            }
        }
    ll ans=1;
    for(int i=1;i<=n;i++)
        ans=ans*du[i][i]%mod;
    if(f==-1)ans=(mod-ans)%mod;
    return ans;
}

int main() {
    scanf("%d%d", &n,&m);
    for (int i = 1; i <= n; i++){
        scanf("%s", st+1);
        for (int j = 1; j <= m; j++)
            if (st[j]=='.') id[i][j]=++cnt;
    }
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++)
            for (int fx = 1; fx <= 4; fx++){
                int tx=i+cx[fx],ty=j+cy[fx];
                int uid=id[i][j],tid=id[tx][ty];
                if (id[i][j]==0||id[tx][ty]==0) continue;
                du[uid][uid]++,du[uid][tid]--;
            }
    }
    
    printf("%lld\n", det(cnt-1));
    

    system("pause");
    return 0;
}