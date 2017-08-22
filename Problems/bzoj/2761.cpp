#include <set>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
set<int> s;
int T, n;
int main() {
  cin >> T;
  for (int x, i = 1; i <= T; i++) {
    scanf("%d", &n);
    s.clear();
    for (int j = 1; j <= n; j++) {
      scanf("%d", &x);
      if (!s.count(x)) {
        if (j > 1)
          putchar(' ');
        printf("%d", x);
        s.insert(x);
      }
    }
    putchar('\n');
  }
}