#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int P,a1,a2,f[1010][1010],cnt,tot,g[1010*1010],pre;
pair<int,int>Q[1010*1010];
ll n;
int main() {
    scanf("%lld%d%d%d",&n,&P,&a1,&a2);
    if(P<1000){
        g[1]=a1;
        g[2]=a2;
        tot=2;
        while(f[a1][a2]==0){
            cnt++;
            Q[cnt]=make_pair(a1,a2);
            f[a1][a2]=cnt;
            int a3=(a1*a2)%P;
            g[++tot]=a3;
            a1=a2;
            a2=a3;
        }
        pre=f[a1][a2]-1;
        //printf("%lld %d\n", n,cnt);
        if(n>cnt){
            n=(n-cnt-1)%(cnt-f[a1][a2]+1)+1;
            //printf("%lld\n", n);
            printf("%d\n", g[n+pre]);
        }else{
            printf("%d\n",g[n]);
        }
    }else{
        
    }
    
    //system("pause");
    return 0;
}