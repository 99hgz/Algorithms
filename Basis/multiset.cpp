#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <set>
using namespace std;
typedef long long ll;

int main() {
  multiset<int> ms;

  ms.insert(10);
  ms.insert(13);
  ms.insert(12);
  ms.insert(11);
  ms.insert(19);
  ms.insert(13);
  ms.insert(16);
  ms.insert(17);
  ms.insert(13);
  for (int elem : ms) {
    printf("%d ", elem);
  }
  printf("\n");
  printf("%d\n", *--ms.lower_bound(13));
  system("pause");
  return 0;
}