/*
 * @tree[x]=sigma(i=x-lowbit(x)+1~x)a[i]
 * @key word:树状数组
 * @未测试‼
 * @Author: hgz
 * @Date: 2017-04-23 12:40:08
 * @Last Modified by: hgz
 * @Last Modified time: 2017-04-23 12:40:52
 */
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int size = 10005;
int tree[size];
typedef long long ll;
int lowbit(int x)
{
  // return x&(x^(x-1));
  return x & -x;
}
ll sum(int end)
{
  ll ans = 0;
  while (end > 0)
  {
    ans += tree[end];
    end -= lowbit(end);
  }
  return ans;
}
void update(int pos, int num)
{
  while (pos < size)
  {
    tree[pos] += num;
    pos += lowbit(pos);
  }
}
int main() { return 0; }
