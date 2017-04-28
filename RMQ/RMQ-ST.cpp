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
class RMQ {
public:
  void rmq() {
    int temp = (int)(log((double)n) / log(2.0));
    for (int i = 0; i < n; i++)
      DP[i][0] = a[i];
    for (int j = 1; j <= temp; j++)
      for (int i = 0; i < n; i++)
        if (i + (1 << j) < n)
          DP[i][j] = min(DP[i][j - 1], DP[i + (1 << (j - 1))][j - 1]);
  }
  int Minimum(int L, int H) {
    int k = (int)(log((double)H - L + 1) / log(2.0));
    return min(DP[L][k], DP[H - (1 << k) + 1][k]);
  }
  void Init() { CLR(DP, 0); }

private:
  int DP[MAX][20];
};
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