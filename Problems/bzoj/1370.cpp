#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n,m,x,y,ans,flag[100010],fa[100010];
char op[10];

int getf(int x){
    return fa[x]==0?x:fa[x]=getf(fa[x]);
}

void merge(int x,int y){
    int a=getf(x),b=getf(y);
    if(a!=b)fa[a]=b;
}

int main() {
    scanf("%d%d", &n,&m);
    for(int i=1;i<=m;i++){
        scanf("%s%d%d", op,&x,&y);
        if(op[0]=='F')
            merge(x,y);
        else
            merge(x+n,y),merge(x,y+n);
    }
    for(int i=1;i<=n;i++) flag[getf(i)]=1;
    for(int i=1;i<=2*n;i++) ans+=flag[i];
    printf("%d\n", ans);
    system("pause");
    return 0;
}