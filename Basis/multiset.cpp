#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <set>
using namespace std;
typedef long long ll;

int main()
{
  multiset<int> ms;
  ms.insert(5);
  ms.insert(9);
  /*for (int elem : ms) {
    printf("%d ", elem);
  }*/
  printf("\n");
  printf("%d\n", *--ms.end());
  printf("%d\n", *ms.lower_bound(6));
  system("pause");
  return 0;
}