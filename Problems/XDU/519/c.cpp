#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
ll ans;
int n,x,y;
ll A[2000010],p=998244353;

int main() {
    scanf("%d",&n);
    A[1]=1;
	for(int i=2;i<=2000000;i++)
			A[i]=(p-(p/i))*A[p%i]%p;
    for(int i=1;i<=n;i++){
        scanf("%d%d",&x,&y);
        ll p1=A[(y-x+1)];
        if(x>n){
            ans=(ans+p1*n%p*(y-x+1)%p*A[n]%p)%p;
        }else if(y>n){
            ans=(ans+p1*(x+n)%p*(n-x+1)%p*A[2]%p*A[n]%p)%p;
            ans=(ans+p1*n%p*(y-n)%p*A[n]%p)%p;
        }else{
            ans=(ans+(x+y)%p*A[2]%p*A[n]%p)%p;
        }
    }
    printf("%lld\n",ans);
    system("pause");
    return 0;
}