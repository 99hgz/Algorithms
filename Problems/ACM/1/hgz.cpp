#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int add(int l,int r,int value){
    for (i = l; i <= min(r,bl[l]*range); i++) {
        
    }
}

int main() {
    scanf("%d\n",&n);
    range=floor(sqrt(n));
    for (i = 1; i <= n; i++) {
        scanf("%d",&a[i]);
        bl[i]=(i-1)/range+1;
    }
    int kind,tmp;
    for (i = 1; i <= n; i++) {
        scanf("%d",&kind );
        if (kind==1){
            scanf("%d %d %d", &l,&r,&value);
            add(l,r,value);
        }else{
            scanf("%d %d %d", &l,&r,&value);
            tmp=query(l,r,value);
            printf("%d\n",tmp);
        }
    }
    system("pause");
    return 0;
}