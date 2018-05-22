#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int f[(1<<20)+1000010],a[300010],n;

int main() {
    memset(f,0x3f3f3f3f,sizeof f);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        a[i]^=a[i-1];
        f[a[i]]=min(f[a[i]],i);
    }
    for(int j=19;~j;j--)
        for(int i=1;i<(1<<20);i++)
            if(!((i>>j)&1))
                f[i]=min(f[i],f[i|(1<<j)]);
    for(int i=1;i<=n;i++){
        int cur=0;
        for(int j=19;~j;j--)
            if(!((a[i]>>j)&1)&&f[cur|(1<<j)]<=i)
                cur|=(1<<j);
        printf("%d\n", (cur^a[i])+cur);
    }
    
    //system("pause");
    return 0;
}