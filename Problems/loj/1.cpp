#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int P,a1,a2,f[1010][1010],cnt;
pair<int,int>Q[1010*1010];
ll n;
int main() {
    scanf("%lld%d%d%d",&n,&P,&a1,&a2);
    while(f[a1][a2]==0){
        cnt++;
        Q[cnt]=make_pair(a1,a2);
        f[a1][a2]=1;
        int a3=(a1*a2)%P;
        a1=a2;
        a2=a3;
    }
    printf("%d\n", cnt);
    n=(n-1)%cnt+1;
    printf("%d\n", Q[n].first,Q[n].second);
    system("pause");
    return 0;
}