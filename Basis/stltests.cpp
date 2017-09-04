#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

int main()
{
  vector<int> Numbers;
  vector<int>::iterator start, end, it, location;
  Numbers.push_back(10);
  Numbers.push_back(4);
  Numbers.push_back(11);
  Numbers.push_back(11);
  Numbers.push_back(30);
  Numbers.push_back(69);
  Numbers.push_back(100);
  Numbers.push_back(96);
  Numbers.push_back(70);
  start = Numbers.begin();
  end = Numbers.end();
  sort(start, end);
  cout << "Numbers { ";
  for (it = start; it != end; it++)
    cout << *it << " ";
  cout << " }\n"
       << endl;
  location = upper_bound(start, end, 11);
  cout << location - start << endl;
  system("pause");
}