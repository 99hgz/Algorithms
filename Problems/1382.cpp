#define N 100003
#define DB long double
#define fo(i, a, b) for (i = a; i <= b; i++)
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
using namespace std;
int n, m, k, i, r, c, t;
DB jc[N], C[N], Q[N], ans;
int main() {
  scanf("%d%d%d", &n, &m, &k);
  C[0] = Q[0] = 1;
  fo(i, 1, n) C[i] = C[i - 1] * ((DB)(n - i + 1) / i);
  fo(i, 1, k) Q[i] = Q[i - 1] * ((DB)(k - i + 1) / (m - i + 1));
  fo(r, 0, n) fo(c, 0, n) {
    t = n * (r + c) - r * c;
    if (t <= k)
      ans = ans + Q[t] * C[r] * C[c];
  }
  if (ans > 1e+99)
    ans = 1e+99;
  printf("%LF", ans);
}