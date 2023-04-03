#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

ll n;
int P,a1,a2,tot,cnt;
int f[1010][1010];
int g[1010*1010];
int a3;

int main() {
    scanf("%lld%d%d%d",&n,&P,&a1,&a2);
    g[1]=a1;
    g[2]=a2; //g 表示 已经计算出来的座位数字序列
    tot=2;  //tot 表示 已经计算出来的座位数字序列个数
    //f[a1][a2]=1;  //f 表示已经计算出来的相邻的两个座位
    //cnt=1;  //cnt 表示已经计算出来的相邻的两个座位个数

    while(f[a1][a2]==0){
        cnt++;
        f[a1][a2]=cnt;

        a3=a1*a2%P;
        a1=a2;
        a2=a3; //下一次运算的时候 a1 a2就是最后两个位置
        g[++tot]=a3;
    }
//a1=6 a2=2
    int circle=cnt-f[a1][a2]+1; //6
    int pre=f[a1][a2]-1; //2
    if(n<=tot){
        printf("%d\n",g[n]);
    }else{
        int x=((n-pre)-1)%circle+1;
        printf("%d\n",g[x+pre]);
    }

//system("pause");
    return 0;
}