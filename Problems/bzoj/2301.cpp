#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int prime[50010], primesize;
bool isprime[50010];

void init(int listsize) {
  memset(isprime, 1, sizeof(isprime));
  isprime[1] = false;
  for (int i = 2; i <= listsize; i++) {
    if (isprime[i])
      prime[++primesize] = i;
    for (int j = 1; j <= primesize && i * prime[j] <= listsize; j++) {
      isprime[i * prime[j]] = false;
      if (i % prime[j] == 0)
        break;
    }
  }
}

int main() {
  scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
  if (b < d) {
    swap(a, c);
    swap(b, d);
  }
  init(50000);
  Q.push((Node){
      1,
  }) system("pause");
  return 0;
}