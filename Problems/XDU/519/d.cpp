#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int map[4][4];
int dep,ans,s,w,t;
char tmp[10];
int chk(){
    for(int i=1;i<=3;i++)
        if(map[i][1]==map[i][2]&&map[i][1]==map[i][3])  return map[i][1];
    for(int i=1;i<=3;i++)
        if(map[1][i]==map[2][i]&&map[1][i]==map[3][i])  return map[1][i];
    if(map[1][1]==map[2][2]&&map[1][1]==map[3][3])return map[1][1];
    if(map[1][3]==map[2][2]&&map[1][3]==map[3][1])return map[1][3];
    return 0;
}

void dfs(int deep,int ch){
    if(deep==dep){
        int status=chk();
        if(status == w)ans++;
        return;
    }
    int status=chk();
    if(status > 0)return;
    for(int i=1;i<=3;i++)
        for(int j=1;j<=3;j++){
            if(map[i][j]==0){
                map[i][j]=ch;
                dfs(deep+1,3-ch);
                map[i][j]=0;
            }
        }
}

int main() {
    scanf("%d", &t);
    while(t--){
        ans=0;
        dep=0;
        for(int i=1;i<=3;i++){
            scanf("%s",tmp);
            for(int j=0;j<3;j++)
                if(tmp[j]=='X')
                    map[i][j+1]=1;
                else if(tmp[j]=='O')
                    map[i][j+1]=2;
                else map[i][j+1]=0,dep++;
        }
        scanf("%d%d",&s,&w);
        dfs(0,(dep%2==1)?s:3-s);
        printf("%d\n", ans);
    }
    system("pause");
    return 0;
}