/*
 * @YY了一个Trie树 已测试BZOJ w1213
 * @Author: hgz
 * @Date: 2017-07-30 19:51:59
 * @Last Modified by: hgz
 * @Last Modified time: 2017-07-30 19:52:30
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, m, ans, length, pointnum;
int tree[100000][26];
bool f[(1 << 20) + 10], isend[100000];
char A[(1 << 20) + 10];

void add() {
  int length = strlen(A);
  int cur = 0;
  for (int i = 0; i < length; i++) {
    if (tree[cur][A[i] - 'a'] == 0) {
      tree[cur][A[i] - 'a'] = ++pointnum;
    }
    cur = tree[cur][A[i] - 'a'];
  }
  isend[cur] = true;
}

void work(int j) {
  int cur = 0;
  for (int i = j; i < length; i++) {
    if (tree[cur][A[i] - 'a'] == 0) {
      return;
    }
    cur = tree[cur][A[i] - 'a'];
    if (isend[cur])
      f[i] = true, ans = max(i, ans);
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%s", A);
    add();
  }
  for (int i = 1; i <= m; i++) {
    scanf("%s", A);
    ans = -1;
    memset(f, 0, sizeof f);
    length = strlen(A);
    for (int j = 0; j < length; j++) {
      if ((j == 0) || (f[j - 1])) {
        work(j);
      }
    }
    printf("%d\n", ans + 1);
  }
  system("pause");
  return 0;
}