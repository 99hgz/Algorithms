#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int ans,n,a[1010];
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
            ans=max(ans,min(a[i],a[j])*(j-i)*5);
    printf("%d\n", ans);
    return 0;
}