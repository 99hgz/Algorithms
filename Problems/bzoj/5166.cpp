#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
int n,m,f[110][110],ans;
struct C{
    int x,y;
}c[110];
int lst;
bool cmp(C a,C b){
    return a.x<b.x;
}
bool v[110];
bool check(C f,int s){
    double x=sqrt(m*m-f.y*f.y)+f.x;
    return (c[s].x-x)*(c[s].x-x)+(c[s].y*c[s].y)<=(double)m*m;
}

int main() {
    scanf("%d%d", &n,&m);
    for (int i = 1; i <= n;i++)
        scanf("%d%d", &c[i].x,&c[i].y);
    sort(c+1,c+1+n,cmp);
    for (int i = 1; i <= n; i++)
        if (i==1||!check(c[lst],i)){
            lst=i;
            v[i]=1;
            ans++;
            for(int j=i-1;j>=1;j--)
                if (check(c[lst],j))
                    ans-=v[j],v[j]=0;
            
        }
    printf("%d\n", ans);
    system("pause");
    return 0;
}