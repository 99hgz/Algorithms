#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <map>
using namespace std;

int main()
{
  map<int,int>st;
  st[1]=1;
  st[11]=2;
  st[20]=3;
  auto it=st.lower_bound(12);
  printf("%d\n",(*it).second);
  system("pause");
}