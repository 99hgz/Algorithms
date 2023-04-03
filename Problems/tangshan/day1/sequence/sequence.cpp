#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n,a[100010],b[100010],ans[100010];

bool cp(){
    for(int j=1;j<n;j++){
        if(ans[j]>b[j])return 0;
        if(ans[j]<b[j])return 1;
    }
    return 0;
}

int main() {
    scanf("%d", &n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){
        int it=0;
        for(int j=1;j<=n;j++)
            if(j!=i)
                b[++it]=a[j];
        if(cp())
            for(int j=1;j<n;j++)
                ans[j]=b[j];
    }
    for(int i=1;i<n;i++)
        printf("%d ", ans[i]);
    //system("pause");
    return 0;
}