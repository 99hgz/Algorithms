/*
 * @key word:RMQ，区间最值，ST算法
 * @未测试
 * @Author: http://blog.csdn.net/xuzengqiang/article/details/7350465
 * @Date: 2017-04-23 13:07:44
 * @Last Modified by: hgz
 * @Last Modified time: 2017-04-23 13:08:12
 */
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
const int MAX = 10010;
#define max(a, b) a > b ? a : b
#define min(a, b) a < b ? a : b
#define CLR(arr, val) memset(arr, val, sizeof(arr))
int n, m, low, high, a[MAX];

namespace RMQ{
    int Log[100007], Max[100007][20];
    inline void init(int *a, int n){
        Log[0] = -1;
        for (int i = 1; i <= n; ++i)
            Log[i] = Log[i >> 1] + 1; //预处理Log数组
        for (int i = 1; i <= n; ++i)
            Max[i][0] = a[i]; //DP初始化
        for (int j = 1; j <= Log[n]; ++j)
            for (int i = 1; i + (1 << j) - 1 <= n; ++i)
                Max[i][j] = max(Max[i][j - 1], Max[i + (1 << j - 1)][j - 1]); //DP转移倍增数组
    }

    inline int Query(int l, int r){
        int k =  31 - __builtin_clz(r - l+1); //计算适合的区间长度
        return max(Max[l][k], Max[r - (1 << k) + 1][k]);
    }
}

int main() {
  RMQ R;
  R.Init();
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i]);
  R.rmq();
  while (m--) {
    scanf("%d%d", &low, &high);
    printf("%d\n", R.Minimum(low, high));
  }
  return 0;
}