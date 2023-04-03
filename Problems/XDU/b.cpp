#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int n,a[100010],ans;
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    int l=1,r=n;
    while(l!=r){
        ans=max(ans,min(a[l],a[r])*(r-l)*5);
        if(a[l]>a[r])r--; else l++;
    }
    printf("%d\n", ans);
    return 0;
}