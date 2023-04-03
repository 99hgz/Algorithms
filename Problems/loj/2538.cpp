#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <set>
using namespace std;
typedef long long ll;
int n,m,k,uw[3010],aw[3010],af[11][1510][1510],as[11][1510][1510],us[11][1510][1510],T;
int MOD=998244353;
int bc[3010][3010];
ll fac[3010],inv[3010];
void init(){
    bc[0][1]=bc[1][1]=1;
    for(int i=2;i<=3000;i++){
        bc[0][i]=1;
        for(int j=1;j<=i;j++)
            bc[j][i]=(bc[j][i-1]+bc[j-1][i-1])%MOD;
    }
}

int C(int m,int n){
    return bc[m][n];
}


void add(int &a,ll b){
    a+=b;
    if(a>=MOD)a-=MOD;
}

int main() {
    scanf("%d", &T);
    init();
    while(T--){
        scanf("%d%d%d", &n,&m,&k);
        for (int i = 1; i <= n; i++) 
            scanf("%d", &uw[i]);
        for (int i = 1; i <= n; i++) 
            scanf("%d", &aw[i]);
        sort(uw+1,uw+1+n,greater<int>());
        sort(aw+1,aw+1+n,greater<int>());
        af[T][0][0]=1;
        for(int i=1;i<=n;i++){
            for(int j=0;j<=m;j++){
                add(af[T][i][j],af[T][i-1][j]);
                add(as[T][i][j],as[T][i-1][j]);
                add(af[T][i][j+1],af[T][i-1][j]);
                add(as[T][i][j+1],((ll)as[T][i-1][j]+(ll)af[T][i-1][j]*aw[i])%MOD);
            }
        }
        //printf("%d\n", as[T][5][4]);
        us[T][0][0]=1;
        for(int i=1;i<=n;i++){
            for(int j=0;j<=m;j++){
                add(us[T][i][j],us[T][i-1][j]);
                add(us[T][i][j+1],(ll)us[T][i-1][j]*uw[i]%MOD);
            }
        }
        int ans=0;
        for(int i=0;i<=m;i++){
            if(i>n||(m-i)>n)continue;
            if(i<=k-1){
                int tmp=0;
                for(int j=1;j<=n;j++)
                    add(tmp,(ll)(as[T][j][k-i]-as[T][j-1][k-i]+MOD)*C(m-k,n-j)%MOD);
                add(ans,(ll)us[T][n][i]*tmp%MOD);
            }
            else{
                int tmp=0;
                for(int j=1;j<=n;j++)
                    add(tmp,(ll)(us[T][j][k-1]-us[T][j-1][k-1]+MOD)*C(i-(k-1),n-j)%MOD);
                if(k==1)tmp=C(i,n);
                int tmp2=0;
                for(int j=1;j<=n;j++)
                    add(tmp2,(ll)aw[j]*C(m-i-1,n-j)%MOD);
                add(ans,(ll)tmp*tmp2%MOD);
            }
        }
        printf("%d\n", ans);
    }
    system("pause");
    return 0;
}