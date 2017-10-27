#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
typedef long long ll;

int total;

struct NODE {
  bool last;
  int son[26];
  int post;
} Node[1000000];
int n, m, f[110][60100], ans;
char A[110];
void add() {
  int cur = 0;
  int len = strlen(A);
  for (int i = 0; i < len; i++) {
    if (Node[cur].son[A[i] - 'A'] == 0)
      Node[cur].son[A[i] - 'A'] = ++total;
    cur = Node[cur].son[A[i] - 'A'];
  }
  Node[cur].last = true;
}

void addedge() {
  queue<int> Q;
  Q.push(0);
  while (!Q.empty()) {
    int cur = Q.front();
    Q.pop();
    for (int i = 0; i < 26; i++) {

      if (Node[cur].son[i] != 0) {
        Q.push(Node[cur].son[i]);
        if (cur != 0)
          Node[Node[cur].son[i]].post = Node[Node[cur].post].son[i];
      } else {
        Node[cur].son[i] = Node[Node[cur].post].son[i];
      }
    }
    Node[cur].last |= Node[Node[cur].post].last;
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%s", A);
    add();
  }
  addedge();
  f[0][0] = 1;
  int T = 1;
  for (int i = 1; i <= m; i++) {
    T = (T * 26) % 10007;
    for (int k = 0; k <= total; k++) {
      if (Node[k].last)
        continue;
      for (int j = 0; j < 26; j++) {
        f[i][Node[k].son[j]] = (f[i][Node[k].son[j]] + f[i - 1][k]) % 10007;
      }
    }
  }
  for (int i = 0; i <= total; i++) {
    if (Node[i].last)
      continue;
    ans += f[m][i];
    ans %= 10007;
  }
  printf("%d\n", ((((T - ans) % 10007) + 10007) % 10007));
  system("pause");
  return 0;
}