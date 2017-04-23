/*
 * @key word:堆排序,vector
 * @已测试
 * @Author: hgz
 * @Date: 2017-04-22 13:56:00
 * @Last Modified by: hgz
 * @Last Modified time: 2017-04-23 12:41:22
 */
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
//偷懒了😝
int main(void) {
  vector<int> v;
  v.push_back(3);
  v.push_back(9);
  v.push_back(6);
  v.push_back(3);
  v.push_back(12);
  v.push_back(17);
  v.push_back(20);
  make_heap(v.begin(), v.end());
  sort_heap(v.begin(), v.end());
  for (int i = 0; i < v.size(); i++)
    cout << ' ' << v[i];
  system("pause");
  return 0;
}
