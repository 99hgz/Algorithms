#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int n,a[1000100],pre[1000100],sum,mx[1000100],mn[1000100],ans,mx2[1000100],mx3[1000100],mx11;
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    mx11=-1000000;
    for(int l1=1;l1<=n;l1++)
        for(int r1=l1-1;r1<=n;r1++)
            for(int l2=r1+1;l2<=n;l2++)
                for(int r2=l2-1;r2<=n;r2++){
                    ans=0;
                    for(int k=1;k<=n;k++)
                        if((k>=l1&&k<=r1)||(k>=l2&&k<=r2))
                            ans+=2*a[k];
                        else
                            ans+=a[k];
                    mx11=max(ans,mx11);
                }

    printf("%d\n", mx11);
    //system("pause");
    return 0;
}