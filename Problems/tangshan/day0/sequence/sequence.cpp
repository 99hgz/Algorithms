#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int n,a[100010],b[100010];
int pd(){
    for(int i=1;i<=n;i++){
        if(a[i]>b[i])
            return 1;
        if(a[i]<b[i])
            return 3;
    }
    return 2;
}

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
        scanf("%d",&b[i]);
    printf("%d\n", pd());
    //system("pause");
    return 0;
}