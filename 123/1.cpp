#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#define ull unsigned long long
using namespace std;
const int fx[] = {0, -2, -1, 1, 2, 2, 1, -1, -2};
const int fy[] = {0, 1, 2, 2, 1, -1, -2, -2, -1};
//马可以走到的位置
int bx,by,mx,my;
ull f[40][40];//f[i][j]代表从A点到(i,j)会经过的线路数
bool s[40][40];//判断这个点有没有马盯着
int main(){
    scanf("%d%d%d%d", &bx, &by, &mx, &my);
    bx += 2; by += 2; mx += 2; my += 2;
    //坐标+2以防越界
    f[2][2] = 1;//初始化
    s[mx][my] = 1;//标记马的位置
    for(int i = 1; i <= 8; i++)
        s[ mx + fx[i] ][ my + fy[i] ] = 1;
    for(int i = 2; i <= bx; i++){
        for(int j = 2; j <= by; j++){
            if(s[i][j])continue;
            f[i][j] = max( f[i][j] , f[i - 1][j] + f[i][j - 1] ); 
            //状态转移方程
        }
    }
    printf("%llu\n", f[bx][by]);
    return 0;
} 