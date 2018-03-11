#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n,a[200010];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    a[n+1]=a[n+2]=0x3f3f3f3f;
    for (int i = 1; i <= n; i++){
        int f=i*2,s=i*2+1;
        if (f>n)  break;
        if (a[s]<a[i]&&a[f]>a[i]){
            swap(a[i],a[f]);
            swap(a[i],a[s]);
        }else if (a[i]>a[s]&&a[i]>a[f]){
            continue;
        }else{
            if (a[s]<a[f])
                swap(s,f);
            swap(a[i],a[f]);
        }
        for (int i = 1; i <= n; i++)
            printf("%d ",a[i] );
        printf("\n" );
    }
    
    system("pause");
    return 0;
}