#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, int> STA;
map<STA, bool> save;
map<STA, int> pos;
int ans, J, O, I, n;
int main() {
  scanf("%d\n", &n);
  char ch;
  save[make_pair(0, 0)] = true;
  for (int i = 1; i <= n; i++) {
    scanf("%c", &ch);
    if (ch == 'J') {
      J++;
    } else if (ch == 'O') {
      O++;
    } else if (ch == 'I') {
      I++;
    }
    if (save[make_pair(O - J, I - O)]) {
      ans = max(ans, i - pos[make_pair(O - J, I - O)]);
    } else {
      save[make_pair(O - J, I - O)] = true;
      pos[make_pair(O - J, I - O)] = i;
    }
  }
  printf("%d\n", ans);
  system("pause");
  return 0;
}