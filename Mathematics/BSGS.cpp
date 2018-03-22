#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <cmath>
using namespace std;
typedef long long ll;
map<ll,int>mp;
int main() {
    ll A,B,P,i,x,y,m;
    while(~scanf("%lld%lld%lld",&P,&A,&B)){
        mp.clear();
        m=ceil(sqrt(P));
        mp[B]=0;
        for(x=1,i=1;i<=m;i++)
            x=x*A%P,mp[x*B%P]=i;
        for(y=1,i=1;i<=m;i++){
            y=y*x%P;
            if(mp.find(y)!=mp.end()){
                printf("%lld\n", i*m-mp[y]);
                break;
            }
        }
        if(i==m+1)
            printf("no solution\n");
    }
    system("pause");
    return 0;
}