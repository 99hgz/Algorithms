#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int n;
bool fib(int x) {
  int a = 0, b = 1, c = 1;
  while (c < x) {
    c = a + b;
    b = a;
    a = c;
  }
  if (c == x)
    return true;
  else
    return false;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    if (fib(n))
      printf("B\n");
    else
      printf("A\n");
  }
  system("pause");
  return 0;
}