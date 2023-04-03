#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;
typedef long long ll;

int n,k,ans,MOD=1000000007;
double L[1000100];
int inv[1000100],fac[1000100];
struct C{
    int n,m;
    double v;
    C(int _n,int _m){n=_n,m=_m,v=L[n]-L[m]-L[n-m];}
    int calc(){
        return (ll)fac[n]*inv[m]%MOD*inv[n-m]%MOD;
    }
};
bool operator < (C a,C b){
    return a.v<b.v;
}
priority_queue<C>q;

int main() {
    scanf("%d%d", &n,&k);
    for(int i=1;i<=n;i++)
        L[i]=L[i-1]+log(i);
    fac[0]=inv[0]=inv[1]=1;
    for(int i=1;i<=n;i++)
        fac[i]=(ll)fac[i-1]*i%MOD;
    for(int i=2;i<=n;i++)
        inv[i]=(ll)(MOD-MOD/i)*inv[MOD%i]%MOD;
    for(int i=2;i<=n;i++)
        inv[i]=(ll)inv[i]*inv[i-1]%MOD;

    for(int i=0;i<=n;i++)
        q.push(C(n,i));
    for(int i=1;i<=k;i++){
        C tmp=q.top();
        ans=(ans+tmp.calc())%MOD;
        q.pop();
        tmp.n--;
        q.push(C(tmp.n,tmp.m));
    }
    printf("%d\n", ans);
    system("pause");
    return 0;
}