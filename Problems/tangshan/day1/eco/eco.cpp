#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;
 
int n,A,B,C;
struct node{
    int atk,cost,add;
}a[2010];
int goal[2010];
int f[2010][3005],bonus[2010];
 
int main() {
    //freopen("a.in","r",stdin);
    scanf("%d%d%d",&n,&A,&C);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&goal[i],&bonus[i]);
    for(int i=1;i<=A;i++)
        scanf("%d%d",&a[i].cost,&a[i].atk);
    memset(f,-1,sizeof f);
    f[0][0]=C;
    int mx=0;
    for(int i=1;i<=n;i++){
            for(int atk=mx;atk<=3000;atk++)
                f[i][atk]=f[i-1][atk]+(f[i-1][atk]!=-1?bonus[i-1]:0);
        if(mx<goal[i]){
                for(int atk=mx;atk<goal[i];atk++)
                    for(int j=1;j<=A;j++)
                        if(f[i][atk]>=a[j].cost)
                            f[i][min(3000,atk+a[j].atk)]=max(f[i][min(3000,atk+a[j].atk)],f[i][atk]-a[j].cost);
            
        }
        mx=max(mx,goal[i]);
        bool check=0;
            for(int atk=goal[i];atk<=3000;atk++)
                if(f[i][atk]>=0){
                    check=1;
                    break;
                }
        if(!check){
            printf("%d\n",i-1);
            return 0;
        }
    }
    printf("%d\n",n);
    //system("pause");
    return 0;
}