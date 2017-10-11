#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

void insert(int x){
    int now=1;
    for (int i = 32; i >=1 ; i--) {
        int dit=x&(1<<i-1);
        if (!son[now][dit])
            now=son[now][dit]=tot++；
        else
            now=son[now][dit];
    }
}

void 

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sum+=a[i];
        insert(sum);
    }
    system("pause");
    return 0;
}