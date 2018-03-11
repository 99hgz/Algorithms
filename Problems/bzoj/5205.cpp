#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

ll p=1e9 + 7;
int f[2][20][20][1<<17];
int mp[20][20],n,m;

void dp(int _){
    int mask=(1<<m)-1;
    f[_][0][0][mask]=1;
    f[_][0][0][mask-1]=(mp[0][0]==0);
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < m; j++) {
            if (i==0&&j==0) continue;
            int l=(j==0?i-1:i);
            int r=(j==0?m-1:j-1);
            for (int k =0; k <= mask; k++)
                if (f[_][l][r][k]!=0){
                    if (mp[i][j]){
                        if (k&(1<<(m-1)))
                            (f[_][i][j][((k<<1)&mask)|1]+=f[_][l][r][k])%=p;
                    }
                    else {
                        (f[_][i][j][((k<<1)&mask)|1]+=f[_][l][r][k])%=p;
                        if (k&(1<<(m-1))){
                            (f[_][i][j][(k<<1)&mask]+=f[_][l][r][k])%=p;
                            if (j&&!(k&1))
                                (f[_][i][j][((k<<1)&mask)|3]+=f[_][l][r][k])%=p;
                        }
                    }
                }
        }
}

int main() {
    scanf("%d%d", &n,&m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) 
            scanf("%d", &mp[i][j]);
    dp(0);
    
    for (int i = 0; i < n/2; i++) 
        for (int j = 0; j < m; j++) 
            swap(mp[i][j],mp[n-i-1][j]);
    
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < m/2; j++) 
            swap(mp[i][j],mp[i][m-j-1]);
        
    dp(1);

    //printf("%d\n", f[0][0][0][(1<<m)-2]);

    for (int i = 0; i < n; i++) 
        for (int j = 0; j < m; j++){ 
            ll ans=0;
            if (!mp[n-i-1][m-j-1]){
                for (int k = 0; k <(1<<m); k+=2){
                    int k2=0;
                    for(int p=k>>1,b=m-1;b;b--,p>>=1)
                        k2=(k2<<1)|(p&1);
                    k2<<=1;
                    (ans+=(ll)f[0][i][j][k]*f[1][n-i-1][m-j-1][k2])%=p;
                }
            }
            printf("%lld%c", ans,j==m-1?'\n':' ');
        }
    
    system("pause");
    return 0;
}