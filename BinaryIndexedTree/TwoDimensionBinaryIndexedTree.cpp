/*
 * @key word:树状数组，二维树状数组
 * @未测试‼
 * @Author: hgz
 * @Date: 2017-04-23 12:48:16
 * @Last Modified by: hgz
 * @Last Modified time: 2017-04-23 12:48:48
 */
#include <iostream>
#include <cstdio>
#include <memory.h>
using namespace std;

int a[1005][1005], n;

int lowbit(int i) { return i & (-i); }

void update(int i, int j, int x) {
  int tj;
  while (i <= n) {
    tj = j;
    while (tj <= n) {
      a[i][tj] += x;
      tj += lowbit(tj);
    }
    i += lowbit(i);
  }
}

int sum(int i, int j) {
  int tj, sum = 0;
  while (i > 0) {
    tj = j;
    while (tj > 0) {
      sum += a[i][tj];
      tj -= lowbit(tj);
    }
    i -= lowbit(i);
  }
  return sum;
}

int main() { return 0; }
