#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n,a[1100][1100],vis[1100][1100];

bool hf(int x,int y){
    return (x>0&&x<=n&&y>0&&y<=n&&!vis[x][y]);
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&a[i][j]);
    int x=1,y=1;
    for(int i=1;i<=n*n;i++){
        printf("%d ",a[x][y]);
        vis[x][y]=1;
        if(hf(x+1,y-1))
            x++,y--;
        else if(hf(x-1,y+1))
            x--,y++;
        else if((x==1||x==n)&&y!=n)
            y++;
        else x++;
    }
    //system("pause");
}