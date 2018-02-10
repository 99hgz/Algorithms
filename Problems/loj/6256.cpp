#include<cstdio>
#include<cstdlib>
using namespace std;

int n,m,T,a[510][510],presum[510][510],x,y,k;

bool check(int x,int y){
    return a[x][y]+a[x+1][y+1]==a[x+1][y]+a[x][y+1];
}

int getsum(int x,int tx,int y,int ty){
    return presum[tx][ty]-presum[tx][y-1]-presum[x-1][ty]+presum[x-1][y-1];
}

int main(){
    scanf("%d%d%d",&n,&m,&T);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&a[i][j]);
    for(int i=1;i<=n-1;i++){
        int pre=0;
        for(int j=1;j<=m-1;j++){
            presum[i][j]=presum[i-1][j];
            if (check(i,j))
                pre+=1;
            presum[i][j]+=pre;
        }
    }
    for(int i=1;i<=T;i++){
        scanf("%d%d%d",&x,&y,&k);
        if (getsum(x,x+k-2,y,y+k-2)==(k-1)*(k-1))
            printf("Y\n");
        else
            printf("N\n");
    }
    //system("pause");
}