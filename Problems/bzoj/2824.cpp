#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int a[60],n,mid;
struct Node{
    int id,x;
}A[60];
bool cmp(Node a,Node b){
    return a.x<b.x;
}

bool check(){
    for(int i=1;i<=n;i++)
        if(a[i]!=i)
            return false;
    return true;
}

int calc(){
    int res=0;
    for(int i=2;i<=n;i++)
        res+=(abs(a[i]-a[i-1])!=1);
    return res;
}

int dfs(int used){
    if(used+calc()>mid)return 0;
    if(check())
        return 1;
    for(int i=2;i<=n;i++){
        reverse(a+1,a+1+i);
        if(dfs(used+1)) return 1;
        reverse(a+1,a+1+i);
    }
    return 0;
}

int main() {
    scanf("%d", &n);
    for(int i=1;i<=n;i++){
        scanf("%d", &A[i].x);
        A[i].id=i;
    }
    sort(A+1,A+1+n,cmp);
    for (int i = 1; i <= n; i++)
        a[A[i].id]=i;
    for(mid=0;mid<=n*2;mid++)
        if(dfs(0)){
            printf("%d\n", mid);
            break;
        }
    system("pause");
    return 0;
}